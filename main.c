/* ========================================
 * Bryce Martin, 2021
 * 
 * Inspired by this github repository found here
 * https://github.com/ocxtal/vfdc
 * ========================================
*/

/*
    NOTES:
    The Vout of a boost converter
    Vout = (Vin / (1 - PWM_DUTY_CYCLE)) - Diode_Drop
    
    The input feedback voltage is
    Vfeed = Vout / 7
*/

#include "project.h"

//Constants
const uint8 TARGET_VOLTAGE = 20; //Varies from 12 ~ 24
const float32 PWM_TC_FREQUENCY = 0.00002133;

//Function Declaration
RTC_TIME_DATE Configure_Current_Time(const char* date, const char* time);

//Flags
volatile uint8 dma_done_flag;
volatile uint8 menu_state;

#define DMA_BYTES_PER_BURST 2
#define DMA_REQUEST_PER_BURST 0

//Globals
uint16 adc_reading = 0;
RTC_TIME_DATE time;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //DMA Variables
    uint8 DMA_Chan;
    uint8 DMA_TD[1];

    //Enable ADC to memory DMA
    DMA_Chan = ADC_GET_DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));
    DMA_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_TD[0], DMA_BYTES_PER_BURST, DMA_INVALID_TD, ADC_GET_DMA__TD_TERMOUT_EN); 
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)Feedback_ADC_SAR_WRK0_PTR), LO16((uint32)&adc_reading));
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);
    CyDmaClearPendingDrq(DMA_Chan);
    CyDmaChEnable(DMA_Chan, 1);
    
    //Setup the PID controller (NEW!)
    //float Kp = 0.1;

    //Activate ADC first
    Feedback_ADC_Start();
    Feedback_ADC_IRQ_Disable();
    CyDelayUs(10); //A delay is added here as recommended for the ADC to stabilize

    //ISR activate
    DMA_ISR_Start();
    
    RTC_Start();
    time = Configure_Current_Time(__DATE__, __TIME__);
    RTC_WriteTime(&time);
    RTC_WriteIntervalMask(RTC_INTERVAL_SEC_MASK | RTC_INTERVAL_MIN_MASK | RTC_INTERVAL_HOUR_MASK);
    
    //Enable tube display driver and display time set in memory
    Tube_Driver_Start();
    Tube_Driver_Write7SegNumberDec(RTC_ReadHour(), 0, 2, Tube_Driver_ZERO_PAD);
    Tube_Driver_Write7SegNumberDec(RTC_ReadMinute(), 2, 2, Tube_Driver_ZERO_PAD);
    Tube_Driver_Write7SegNumberDec(RTC_ReadSecond(), 4, 2, Tube_Driver_ZERO_PAD);

    //Setup user interface
    menu_state = 0;
    uint8 date_start = 0;
    Button_ISR_Start();    
    
    //Enable PWM timer
    Switcher_Start();

    for(;;)
    {
        if(dma_done_flag){
            int feedback_voltage = Feedback_ADC_CountsTo_Volts(adc_reading) * 6.6;
            
            //P Control implementation (NEW!)
            //Switcher_WriteCompare(Switcher_ReadPeriod() * (1 - (5 / (Kp * (TARGET_VOLTAGE - feedback_voltage)))));
            
            //DUMB IMPLEMENATION
            if(feedback_voltage < 6){
                //Indicate a fault if the voltage is too low
                Indicator_Write(1);
                Switcher_Stop();
            }else{
                if(feedback_voltage < TARGET_VOLTAGE)
                    Switcher_WriteCompare(Switcher_ReadCompare() + 1);
                else if(feedback_voltage > TARGET_VOLTAGE)
                    Switcher_WriteCompare(Switcher_ReadCompare() - 1);
            }
                
            dma_done_flag = 0;
            DMA_ISR_Enable();
        }
        
        switch(menu_state){
            case 0:{
                if(Nav_Button_Reg_Read()){
                    //Go into date display mode
                    menu_state = 8;
                    date_start = RTC_ReadSecond();

                    //Disable time based interrupts
                    RTC_WriteIntervalMask(0x00);                    
                    
                    //Display the date
                    Tube_Driver_ClearDisplayAll();
                    
                    Tube_Driver_Write7SegNumberDec(RTC_ReadYear() % 100, 0, 2, Tube_Driver_ZERO_PAD);
                    Tube_Driver_Write7SegNumberDec(RTC_ReadMonth(), 2, 2, Tube_Driver_ZERO_PAD);
                    Tube_Driver_Write7SegNumberDec(RTC_ReadDayOfMonth(), 4, 2, Tube_Driver_ZERO_PAD);                    
                }
                break;
            }
            case 1:{
                //Ready time set routine
                time.Hour = RTC_ReadHour();
                time.Min = RTC_ReadMinute();
                time.Sec = RTC_ReadSecond();
                
                //Disable time based interrupts
                RTC_WriteIntervalMask(0x00);
                
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.Hour, 0, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;
            }
            case 2:{
                //Set hour
                if(Nav_Button_Reg_Read()){
                    time.Hour = (time.Hour + 1) % 24;
                    Tube_Driver_Write7SegNumberDec(time.Hour, 0, 2, Tube_Driver_ZERO_PAD);
                }
                break;
            }
            case 3:{ 
                //Ready minute set routine
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.Min, 2, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;                
            }
            case 4:{
                //Set minute
                if(Nav_Button_Reg_Read()){
                    time.Min = (time.Min + 1) % 60;
                    Tube_Driver_Write7SegNumberDec(time.Min, 2, 2, Tube_Driver_ZERO_PAD);
                }
                break;                
            }
            case 5:{
                //Ready second set routine
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.Sec, 4, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;                
            }
            case 6:{
                //Set second
                if(Nav_Button_Reg_Read()){
                    time.Sec = (time.Sec + 1) % 60;
                    Tube_Driver_Write7SegNumberDec(time.Sec, 4, 2, Tube_Driver_ZERO_PAD);
                }

                break;                
            }
            case 7:{
                //Finish time set routine
                time.Year = RTC_ReadYear();
                time.Month = RTC_ReadMonth();
                time.DayOfMonth = RTC_ReadDayOfMonth();
                RTC_WriteTime(&time);
                
                //Re-enable time interrupts
                RTC_WriteIntervalMask(RTC_INTERVAL_SEC_MASK | RTC_INTERVAL_MIN_MASK | RTC_INTERVAL_HOUR_MASK);

                //Update display
                Tube_Driver_Write7SegNumberDec(RTC_ReadHour(), 0, 2, Tube_Driver_ZERO_PAD);
                Tube_Driver_Write7SegNumberDec(RTC_ReadMinute(), 2, 2, Tube_Driver_ZERO_PAD);
                Tube_Driver_Write7SegNumberDec(RTC_ReadSecond(), 4, 2, Tube_Driver_ZERO_PAD);
                
                menu_state = 0;
                break;
            }
            case 8:{
                //Date display mode
                //When 60 seconds pass return to time mode
                if(date_start == RTC_ReadSecond() + 1){
                    //Re-enable time interrupts
                    RTC_WriteIntervalMask(RTC_INTERVAL_SEC_MASK | RTC_INTERVAL_MIN_MASK | RTC_INTERVAL_HOUR_MASK);

                    //Update display
                    Tube_Driver_Write7SegNumberDec(RTC_ReadHour(), 0, 2, Tube_Driver_ZERO_PAD);
                    Tube_Driver_Write7SegNumberDec(RTC_ReadMinute(), 2, 2, Tube_Driver_ZERO_PAD);
                    Tube_Driver_Write7SegNumberDec(RTC_ReadSecond(), 4, 2, Tube_Driver_ZERO_PAD);
                    
                    menu_state = 0;   
                }
                break;
            }
            case 9:{
                //Ready date set routine
                time.Year = RTC_ReadYear();
                time.Month = RTC_ReadMonth();
                time.DayOfMonth = RTC_ReadDayOfMonth();
                
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.Year, 0, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;
            }
            case 10:{
                //Set Year
                if(Nav_Button_Reg_Read()){
                    time.Year = (time.Year + 1);
                    Tube_Driver_Write7SegNumberDec(time.Year, 0, 2, Tube_Driver_ZERO_PAD);
                }
                break;
            }
            case 11:{ 
                //Ready month set routine
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.Month, 2, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;                
            }
            case 12:{
                //Set month
                if(Nav_Button_Reg_Read()){
                    time.Month = (time.Month + 1) % 13;
                    time.Month == 0 ? time.Month = 1: time.Month;
                    Tube_Driver_Write7SegNumberDec(time.Month, 2, 2, Tube_Driver_ZERO_PAD);
                }
                break;                
            }
            case 13:{ 
                //Ready day of Month set routine
                //Clear display
                Tube_Driver_ClearDisplayAll();
                
                Tube_Driver_Write7SegNumberDec(time.DayOfMonth, 4, 2, Tube_Driver_ZERO_PAD);
                
                menu_state ++;                
            }
            case 14:{
                //Set day of Month
                if(Nav_Button_Reg_Read()){
                    time.DayOfMonth = (time.DayOfMonth + 1) % 32;
                    time.DayOfMonth == 0 ? time.DayOfMonth = 1: time.DayOfMonth;
                    Tube_Driver_Write7SegNumberDec(time.DayOfMonth, 4, 2, Tube_Driver_ZERO_PAD);
                }
                break;                
            }
            case 15:{
                //Finish date set routine
                time.Hour = RTC_ReadHour();
                time.Min = RTC_ReadMinute();
                time.Sec = RTC_ReadSecond();
                RTC_WriteTime(&time);

                //Update display
                Tube_Driver_ClearDisplayAll();
                    
                Tube_Driver_Write7SegNumberDec(RTC_ReadYear(), 0, 2, Tube_Driver_ZERO_PAD);
                Tube_Driver_Write7SegNumberDec(RTC_ReadMonth(), 2, 2, Tube_Driver_ZERO_PAD);
                Tube_Driver_Write7SegNumberDec(RTC_ReadDayOfMonth(), 4, 2, Tube_Driver_ZERO_PAD);                
                
                //Return to date display
                date_start = RTC_ReadSecond() - 1;
                menu_state = 8;
                break;
            }            
        }
    }
}

//Function to set RTC time using compile time, repurposed from here:
//https://github.com/adafruit/RTClib/blob/master/RTClib.cpp

RTC_TIME_DATE Configure_Current_Time(const char* date, const char* time){
  RTC_TIME_DATE cmptime;
  
  cmptime.Year = (date[7] - 48) * 1000 + (date[8] - 48) * 100 + (date[9] - 48) * 10 + (date[10] - 48);

  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (date[0]) {
  case 'J':
    cmptime.Month = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7);
    break;
  case 'F':
    cmptime.Month = 2;
    break;
  case 'A':
    cmptime.Month = date[2] == 'r' ? 4 : 8;
    break;
  case 'M':
    cmptime.Month = date[2] == 'r' ? 3 : 5;
    break;
  case 'S':
    cmptime.Month = 9;
    break;
  case 'O':
    cmptime.Month = 10;
    break;
  case 'N':
    cmptime.Month = 11;
    break;
  case 'D':
    cmptime.Month = 12;
    break;
  }

  if(date[4]  - 32 == 0){
    cmptime.DayOfMonth = date[5] - 48;
  }else{
    cmptime.DayOfMonth = (date[4] - 48) * 10 + (date[5] - 48);  
  }

  cmptime.Hour = (time[0] - 48) * 10 + (time[1] - 48);
  cmptime.Min = (time[3] - 48) * 10 + (time[4] - 48);
  cmptime.Sec = (time[6] - 48) * 10 + (time[7] - 48);

  return cmptime;
}
/* [] END OF FILE */