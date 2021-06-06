/*******************************************************************************
* File Name: Menu_Button.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Menu_Button_ALIASES_H) /* Pins Menu_Button_ALIASES_H */
#define CY_PINS_Menu_Button_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Menu_Button_0			(Menu_Button__0__PC)
#define Menu_Button_0_INTR	((uint16)((uint16)0x0001u << Menu_Button__0__SHIFT))

#define Menu_Button_1			(Menu_Button__1__PC)
#define Menu_Button_1_INTR	((uint16)((uint16)0x0001u << Menu_Button__1__SHIFT))

#define Menu_Button_INTR_ALL	 ((uint16)(Menu_Button_0_INTR| Menu_Button_1_INTR))

#endif /* End Pins Menu_Button_ALIASES_H */


/* [] END OF FILE */
