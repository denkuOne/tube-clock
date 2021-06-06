/*******************************************************************************
* File Name: DMA_DONE.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_DMA_DONE_H)
#define CY_ISR_DMA_DONE_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DMA_DONE_Start(void);
void DMA_DONE_StartEx(cyisraddress address);
void DMA_DONE_Stop(void);

CY_ISR_PROTO(DMA_DONE_Interrupt);

void DMA_DONE_SetVector(cyisraddress address);
cyisraddress DMA_DONE_GetVector(void);

void DMA_DONE_SetPriority(uint8 priority);
uint8 DMA_DONE_GetPriority(void);

void DMA_DONE_Enable(void);
uint8 DMA_DONE_GetState(void);
void DMA_DONE_Disable(void);

void DMA_DONE_SetPending(void);
void DMA_DONE_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DMA_DONE ISR. */
#define DMA_DONE_INTC_VECTOR            ((reg32 *) DMA_DONE__INTC_VECT)

/* Address of the DMA_DONE ISR priority. */
#define DMA_DONE_INTC_PRIOR             ((reg8 *) DMA_DONE__INTC_PRIOR_REG)

/* Priority of the DMA_DONE interrupt. */
#define DMA_DONE_INTC_PRIOR_NUMBER      DMA_DONE__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DMA_DONE interrupt. */
#define DMA_DONE_INTC_SET_EN            ((reg32 *) DMA_DONE__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DMA_DONE interrupt. */
#define DMA_DONE_INTC_CLR_EN            ((reg32 *) DMA_DONE__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DMA_DONE interrupt state to pending. */
#define DMA_DONE_INTC_SET_PD            ((reg32 *) DMA_DONE__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DMA_DONE interrupt. */
#define DMA_DONE_INTC_CLR_PD            ((reg32 *) DMA_DONE__INTC_CLR_PD_REG)


#endif /* CY_ISR_DMA_DONE_H */


/* [] END OF FILE */
