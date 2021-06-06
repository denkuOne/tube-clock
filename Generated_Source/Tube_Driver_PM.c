/*******************************************************************************
* File Name: Tube_Driver_PM.c
* Version 1.10
*
* Description:
*  This file provides the power management source code to API for the
*  LED_Driver component.
*
* Note:
*  None
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Tube_Driver.h"
static Tube_Driver_backupStruct Tube_Driver_backup;


/*******************************************************************************
* Function Name: Tube_Driver_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Tube_Driver_Sleep(void) 
{
    uint8 i;
    
    /* Store the component enable state */
    Tube_Driver_backup.ledEnableState = Tube_Driver_enableVar;
    
    /* Save the segment buffers */
    for(i = 0u; i < Tube_Driver_NUM_COM; i++)
    {
        Tube_Driver_backup.segLBackup[i] = Tube_Driver_segLBuffer[i];
        #if (Tube_Driver_NUM_SEG > 8u) 
            Tube_Driver_backup.segMBackup[i] = Tube_Driver_segMBuffer[i];
        #endif /* (Tube_Driver_NUM_SEG > 8u) */
        #if (Tube_Driver_NUM_SEG > 16u) 
            Tube_Driver_backup.segHBackup[i] = Tube_Driver_segHBuffer[i];
        #endif /* (Tube_Driver_NUM_SEG > 16u) */
    }
    
    Tube_Driver_Stop();
}


/*******************************************************************************
* Function Name: Tube_Driver_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Tube_Driver_Wakeup(void) 
{
    uint8 i;
    
    /* Restore the segment buffers */
    for(i = 0u; i < Tube_Driver_NUM_COM; i++)
    {
        Tube_Driver_segLBuffer[i] = Tube_Driver_backup.segLBackup[i];
        #if (Tube_Driver_NUM_SEG > 8u) 
            Tube_Driver_segMBuffer[i] = Tube_Driver_backup.segMBackup[i];
        #endif /* (Tube_Driver_NUM_SEG > 8u) */
        #if (Tube_Driver_NUM_SEG > 16u) 
            Tube_Driver_segHBuffer[i] = Tube_Driver_backup.segHBackup[i];
        #endif /* (Tube_Driver_NUM_SEG > 16u) */
    }
    
    if(Tube_Driver_backup.ledEnableState == Tube_Driver_ENABLED)
    {
        /* Enable the component */
        Tube_Driver_Enable();
    }
}


/* [] END OF FILE */

