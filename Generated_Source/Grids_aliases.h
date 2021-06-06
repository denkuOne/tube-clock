/*******************************************************************************
* File Name: Grids.h  
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

#if !defined(CY_PINS_Grids_ALIASES_H) /* Pins Grids_ALIASES_H */
#define CY_PINS_Grids_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Grids_0			(Grids__0__PC)
#define Grids_0_INTR	((uint16)((uint16)0x0001u << Grids__0__SHIFT))

#define Grids_1			(Grids__1__PC)
#define Grids_1_INTR	((uint16)((uint16)0x0001u << Grids__1__SHIFT))

#define Grids_2			(Grids__2__PC)
#define Grids_2_INTR	((uint16)((uint16)0x0001u << Grids__2__SHIFT))

#define Grids_3			(Grids__3__PC)
#define Grids_3_INTR	((uint16)((uint16)0x0001u << Grids__3__SHIFT))

#define Grids_4			(Grids__4__PC)
#define Grids_4_INTR	((uint16)((uint16)0x0001u << Grids__4__SHIFT))

#define Grids_5			(Grids__5__PC)
#define Grids_5_INTR	((uint16)((uint16)0x0001u << Grids__5__SHIFT))

#define Grids_INTR_ALL	 ((uint16)(Grids_0_INTR| Grids_1_INTR| Grids_2_INTR| Grids_3_INTR| Grids_4_INTR| Grids_5_INTR))

#endif /* End Pins Grids_ALIASES_H */


/* [] END OF FILE */
