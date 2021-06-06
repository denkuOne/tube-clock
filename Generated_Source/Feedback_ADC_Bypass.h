/*******************************************************************************
* File Name: Feedback_ADC_Bypass.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Feedback_ADC_Bypass_H) /* Pins Feedback_ADC_Bypass_H */
#define CY_PINS_Feedback_ADC_Bypass_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Feedback_ADC_Bypass_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Feedback_ADC_Bypass__PORT == 15 && ((Feedback_ADC_Bypass__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Feedback_ADC_Bypass_Write(uint8 value);
void    Feedback_ADC_Bypass_SetDriveMode(uint8 mode);
uint8   Feedback_ADC_Bypass_ReadDataReg(void);
uint8   Feedback_ADC_Bypass_Read(void);
void    Feedback_ADC_Bypass_SetInterruptMode(uint16 position, uint16 mode);
uint8   Feedback_ADC_Bypass_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Feedback_ADC_Bypass_SetDriveMode() function.
     *  @{
     */
        #define Feedback_ADC_Bypass_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Feedback_ADC_Bypass_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Feedback_ADC_Bypass_DM_RES_UP          PIN_DM_RES_UP
        #define Feedback_ADC_Bypass_DM_RES_DWN         PIN_DM_RES_DWN
        #define Feedback_ADC_Bypass_DM_OD_LO           PIN_DM_OD_LO
        #define Feedback_ADC_Bypass_DM_OD_HI           PIN_DM_OD_HI
        #define Feedback_ADC_Bypass_DM_STRONG          PIN_DM_STRONG
        #define Feedback_ADC_Bypass_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Feedback_ADC_Bypass_MASK               Feedback_ADC_Bypass__MASK
#define Feedback_ADC_Bypass_SHIFT              Feedback_ADC_Bypass__SHIFT
#define Feedback_ADC_Bypass_WIDTH              1u

/* Interrupt constants */
#if defined(Feedback_ADC_Bypass__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Feedback_ADC_Bypass_SetInterruptMode() function.
     *  @{
     */
        #define Feedback_ADC_Bypass_INTR_NONE      (uint16)(0x0000u)
        #define Feedback_ADC_Bypass_INTR_RISING    (uint16)(0x0001u)
        #define Feedback_ADC_Bypass_INTR_FALLING   (uint16)(0x0002u)
        #define Feedback_ADC_Bypass_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Feedback_ADC_Bypass_INTR_MASK      (0x01u) 
#endif /* (Feedback_ADC_Bypass__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Feedback_ADC_Bypass_PS                     (* (reg8 *) Feedback_ADC_Bypass__PS)
/* Data Register */
#define Feedback_ADC_Bypass_DR                     (* (reg8 *) Feedback_ADC_Bypass__DR)
/* Port Number */
#define Feedback_ADC_Bypass_PRT_NUM                (* (reg8 *) Feedback_ADC_Bypass__PRT) 
/* Connect to Analog Globals */                                                  
#define Feedback_ADC_Bypass_AG                     (* (reg8 *) Feedback_ADC_Bypass__AG)                       
/* Analog MUX bux enable */
#define Feedback_ADC_Bypass_AMUX                   (* (reg8 *) Feedback_ADC_Bypass__AMUX) 
/* Bidirectional Enable */                                                        
#define Feedback_ADC_Bypass_BIE                    (* (reg8 *) Feedback_ADC_Bypass__BIE)
/* Bit-mask for Aliased Register Access */
#define Feedback_ADC_Bypass_BIT_MASK               (* (reg8 *) Feedback_ADC_Bypass__BIT_MASK)
/* Bypass Enable */
#define Feedback_ADC_Bypass_BYP                    (* (reg8 *) Feedback_ADC_Bypass__BYP)
/* Port wide control signals */                                                   
#define Feedback_ADC_Bypass_CTL                    (* (reg8 *) Feedback_ADC_Bypass__CTL)
/* Drive Modes */
#define Feedback_ADC_Bypass_DM0                    (* (reg8 *) Feedback_ADC_Bypass__DM0) 
#define Feedback_ADC_Bypass_DM1                    (* (reg8 *) Feedback_ADC_Bypass__DM1)
#define Feedback_ADC_Bypass_DM2                    (* (reg8 *) Feedback_ADC_Bypass__DM2) 
/* Input Buffer Disable Override */
#define Feedback_ADC_Bypass_INP_DIS                (* (reg8 *) Feedback_ADC_Bypass__INP_DIS)
/* LCD Common or Segment Drive */
#define Feedback_ADC_Bypass_LCD_COM_SEG            (* (reg8 *) Feedback_ADC_Bypass__LCD_COM_SEG)
/* Enable Segment LCD */
#define Feedback_ADC_Bypass_LCD_EN                 (* (reg8 *) Feedback_ADC_Bypass__LCD_EN)
/* Slew Rate Control */
#define Feedback_ADC_Bypass_SLW                    (* (reg8 *) Feedback_ADC_Bypass__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Feedback_ADC_Bypass_PRTDSI__CAPS_SEL       (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Feedback_ADC_Bypass_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Feedback_ADC_Bypass_PRTDSI__OE_SEL0        (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__OE_SEL0) 
#define Feedback_ADC_Bypass_PRTDSI__OE_SEL1        (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Feedback_ADC_Bypass_PRTDSI__OUT_SEL0       (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__OUT_SEL0) 
#define Feedback_ADC_Bypass_PRTDSI__OUT_SEL1       (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Feedback_ADC_Bypass_PRTDSI__SYNC_OUT       (* (reg8 *) Feedback_ADC_Bypass__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Feedback_ADC_Bypass__SIO_CFG)
    #define Feedback_ADC_Bypass_SIO_HYST_EN        (* (reg8 *) Feedback_ADC_Bypass__SIO_HYST_EN)
    #define Feedback_ADC_Bypass_SIO_REG_HIFREQ     (* (reg8 *) Feedback_ADC_Bypass__SIO_REG_HIFREQ)
    #define Feedback_ADC_Bypass_SIO_CFG            (* (reg8 *) Feedback_ADC_Bypass__SIO_CFG)
    #define Feedback_ADC_Bypass_SIO_DIFF           (* (reg8 *) Feedback_ADC_Bypass__SIO_DIFF)
#endif /* (Feedback_ADC_Bypass__SIO_CFG) */

/* Interrupt Registers */
#if defined(Feedback_ADC_Bypass__INTSTAT)
    #define Feedback_ADC_Bypass_INTSTAT            (* (reg8 *) Feedback_ADC_Bypass__INTSTAT)
    #define Feedback_ADC_Bypass_SNAP               (* (reg8 *) Feedback_ADC_Bypass__SNAP)
    
	#define Feedback_ADC_Bypass_0_INTTYPE_REG 		(* (reg8 *) Feedback_ADC_Bypass__0__INTTYPE)
#endif /* (Feedback_ADC_Bypass__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Feedback_ADC_Bypass_H */


/* [] END OF FILE */
