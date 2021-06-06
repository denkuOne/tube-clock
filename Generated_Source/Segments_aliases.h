/*******************************************************************************
* File Name: Segments.h  
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

#if !defined(CY_PINS_Segments_ALIASES_H) /* Pins Segments_ALIASES_H */
#define CY_PINS_Segments_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Segments_0			(Segments__0__PC)
#define Segments_0_INTR	((uint16)((uint16)0x0001u << Segments__0__SHIFT))

#define Segments_1			(Segments__1__PC)
#define Segments_1_INTR	((uint16)((uint16)0x0001u << Segments__1__SHIFT))

#define Segments_2			(Segments__2__PC)
#define Segments_2_INTR	((uint16)((uint16)0x0001u << Segments__2__SHIFT))

#define Segments_3			(Segments__3__PC)
#define Segments_3_INTR	((uint16)((uint16)0x0001u << Segments__3__SHIFT))

#define Segments_4			(Segments__4__PC)
#define Segments_4_INTR	((uint16)((uint16)0x0001u << Segments__4__SHIFT))

#define Segments_5			(Segments__5__PC)
#define Segments_5_INTR	((uint16)((uint16)0x0001u << Segments__5__SHIFT))

#define Segments_6			(Segments__6__PC)
#define Segments_6_INTR	((uint16)((uint16)0x0001u << Segments__6__SHIFT))

#define Segments_INTR_ALL	 ((uint16)(Segments_0_INTR| Segments_1_INTR| Segments_2_INTR| Segments_3_INTR| Segments_4_INTR| Segments_5_INTR| Segments_6_INTR))

#endif /* End Pins Segments_ALIASES_H */


/* [] END OF FILE */
