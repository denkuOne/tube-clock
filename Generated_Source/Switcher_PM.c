/*******************************************************************************
* File Name: Switcher_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Switcher.h"

static Switcher_backupStruct Switcher_backup;


/*******************************************************************************
* Function Name: Switcher_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Switcher_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Switcher_SaveConfig(void) 
{

    #if(!Switcher_UsingFixedFunction)
        #if(!Switcher_PWMModeIsCenterAligned)
            Switcher_backup.PWMPeriod = Switcher_ReadPeriod();
        #endif /* (!Switcher_PWMModeIsCenterAligned) */
        Switcher_backup.PWMUdb = Switcher_ReadCounter();
        #if (Switcher_UseStatus)
            Switcher_backup.InterruptMaskValue = Switcher_STATUS_MASK;
        #endif /* (Switcher_UseStatus) */

        #if(Switcher_DeadBandMode == Switcher__B_PWM__DBM_256_CLOCKS || \
            Switcher_DeadBandMode == Switcher__B_PWM__DBM_2_4_CLOCKS)
            Switcher_backup.PWMdeadBandValue = Switcher_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Switcher_KillModeMinTime)
             Switcher_backup.PWMKillCounterPeriod = Switcher_ReadKillTime();
        #endif /* (Switcher_KillModeMinTime) */

        #if(Switcher_UseControl)
            Switcher_backup.PWMControlRegister = Switcher_ReadControlRegister();
        #endif /* (Switcher_UseControl) */
    #endif  /* (!Switcher_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Switcher_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Switcher_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Switcher_RestoreConfig(void) 
{
        #if(!Switcher_UsingFixedFunction)
            #if(!Switcher_PWMModeIsCenterAligned)
                Switcher_WritePeriod(Switcher_backup.PWMPeriod);
            #endif /* (!Switcher_PWMModeIsCenterAligned) */

            Switcher_WriteCounter(Switcher_backup.PWMUdb);

            #if (Switcher_UseStatus)
                Switcher_STATUS_MASK = Switcher_backup.InterruptMaskValue;
            #endif /* (Switcher_UseStatus) */

            #if(Switcher_DeadBandMode == Switcher__B_PWM__DBM_256_CLOCKS || \
                Switcher_DeadBandMode == Switcher__B_PWM__DBM_2_4_CLOCKS)
                Switcher_WriteDeadTime(Switcher_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Switcher_KillModeMinTime)
                Switcher_WriteKillTime(Switcher_backup.PWMKillCounterPeriod);
            #endif /* (Switcher_KillModeMinTime) */

            #if(Switcher_UseControl)
                Switcher_WriteControlRegister(Switcher_backup.PWMControlRegister);
            #endif /* (Switcher_UseControl) */
        #endif  /* (!Switcher_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Switcher_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Switcher_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Switcher_Sleep(void) 
{
    #if(Switcher_UseControl)
        if(Switcher_CTRL_ENABLE == (Switcher_CONTROL & Switcher_CTRL_ENABLE))
        {
            /*Component is enabled */
            Switcher_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Switcher_backup.PWMEnableState = 0u;
        }
    #endif /* (Switcher_UseControl) */

    /* Stop component */
    Switcher_Stop();

    /* Save registers configuration */
    Switcher_SaveConfig();
}


/*******************************************************************************
* Function Name: Switcher_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Switcher_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Switcher_Wakeup(void) 
{
     /* Restore registers values */
    Switcher_RestoreConfig();

    if(Switcher_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Switcher_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
