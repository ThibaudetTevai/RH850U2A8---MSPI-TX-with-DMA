/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_intc_PE0.c
* Version          : 1.0.131
* Device(s)        : R7F702301BEBBA
* Description      : None
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_Interrupt_Initialize_ForPE(void)
{
    /* Set INTMSPI0ERR setting */
    INTC2.EIC253.BIT.EIMK253 = _INT_PROCESSING_DISABLED;
    INTC2.EIC253.BIT.EIRF253 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC253.BIT.EITB253 = _INT_TABLE_VECTOR;
    INTC2.EIC253.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD253.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI0FE setting */
    INTC2.EIC252.BIT.EIMK252 = _INT_PROCESSING_DISABLED;
    INTC2.EIC252.BIT.EIRF252 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC252.BIT.EITB252 = _INT_TABLE_VECTOR;
    INTC2.EIC252.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD252.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI0RX setting */
    INTC2.EIC251.BIT.EIMK251 = _INT_PROCESSING_DISABLED;
    INTC2.EIC251.BIT.EIRF251 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC251.BIT.EITB251 = _INT_TABLE_VECTOR;
    INTC2.EIC251.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD251.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI0RX0 setting */
    INTC2.EIC245.BIT.EIMK245 = _INT_PROCESSING_DISABLED;
    INTC2.EIC245.BIT.EIRF245 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC245.BIT.EITB245 = _INT_TABLE_VECTOR;
    INTC2.EIC245.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD245.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI0TX setting */
    INTC2.EIC250.BIT.EIMK250 = _INT_PROCESSING_DISABLED;
    INTC2.EIC250.BIT.EIRF250 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC250.BIT.EITB250 = _INT_TABLE_VECTOR;
    INTC2.EIC250.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD250.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI0TX0 setting */
    INTC2.EIC244.BIT.EIMK244 = _INT_PROCESSING_DISABLED;
    INTC2.EIC244.BIT.EIRF244 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC244.BIT.EITB244 = _INT_TABLE_VECTOR;
    INTC2.EIC244.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD244.BIT.PEID = _INT_CPU_PE0;
    /* Set INTSDMAC0CH0 setting */
    INTC2.EIC47.BIT.EIMK47 = _INT_PROCESSING_DISABLED;
    INTC2.EIC47.BIT.EIRF47 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC47.BIT.EITB47 = _INT_TABLE_VECTOR;
    INTC2.EIC47.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD47.BIT.PEID = _INT_CPU_PE0;
    /* Set INTSDMACERR setting */
    INTC1_PE0.EIC29.BIT.EIMK29 = _INT_PROCESSING_DISABLED;
    INTC1_PE0.EIC29.BIT.EIRF29 = _INT_REQUEST_NOT_OCCUR;
    INTC1_PE0.EIC29.BIT.EITB29 = _INT_TABLE_VECTOR;
    INTC1_PE0.EIC29.UINT16 &= _INT_PRIORITY_LOWEST;
}
