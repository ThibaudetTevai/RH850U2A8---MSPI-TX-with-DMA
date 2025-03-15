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
* File Name        : r_cg_mspi_common.c
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
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI0TX
* Description  : This function This function enable MSPI0 transmit interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI0TX(void)
{
    /* Clear MSPI0 transmit interrupt request and enable operation */
    INTC2.EIC250.BIT.EIRF250 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC250.BIT.EIMK250 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI0TX
* Description  : This function This function disable MSPI0 transmit interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI0TX(void)
{
    /* Disable MSPI0 transmit interrupt operation and clear request */
    INTC2.EIC250.BIT.EIMK250 = _INT_PROCESSING_DISABLED;
    INTC2.EIC250.BIT.EIRF250 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI0RX
* Description  : This function This function enable MSPI0 receive interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI0RX(void)
{
    /* Clear MSPI0 receive interrupt request and enable operation */
    INTC2.EIC251.BIT.EIRF251 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC251.BIT.EIMK251 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI0RX
* Description  : This function This function disable MSPI0 receive interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI0RX(void)
{
    /* Disable MSPI0 receive interrupt operation and clear request */
    INTC2.EIC251.BIT.EIMK251 = _INT_PROCESSING_DISABLED;
    INTC2.EIC251.BIT.EIRF251 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI0FE
* Description  : This function This function enable MSPI0 frame end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI0FE(void)
{
    /* Clear MSPI0 frame end interrupt request and enable operation */
    INTC2.EIC252.BIT.EIRF252 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC252.BIT.EIMK252 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI0FE
* Description  : This function This function disable MSPI0 frame end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI0FE(void)
{
    /* Disable MSPI0 frame end interrupt operation and clear request */
    INTC2.EIC252.BIT.EIMK252 = _INT_PROCESSING_DISABLED;
    INTC2.EIC252.BIT.EIRF252 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI0ERR
* Description  : This function This function enable MSPI0 error interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI0ERR(void)
{
    /* Clear MSPI0 error interrupt request and enable operation */
    INTC2.EIC253.BIT.EIRF253 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC253.BIT.EIMK253 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI0ERR
* Description  : This function This function disable MSPI0 error interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI0ERR(void)
{
    /* Disable MSPI0 error interrupt operation and clear request */
    INTC2.EIC253.BIT.EIMK253 = _INT_PROCESSING_DISABLED;
    INTC2.EIC253.BIT.EIRF253 = _INT_REQUEST_NOT_OCCUR;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
