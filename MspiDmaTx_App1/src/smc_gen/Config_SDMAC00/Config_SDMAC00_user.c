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
* File Name        : Config_SDMAC00_user.c
* Component Version: 1.5.0
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_SDMAC00.
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
#include "Config_SDMAC00.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern uint8_t EndSending;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SDMAC00_Create_UserInit
* Description  : This function adds user code after initializing DMAC00 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_SDMAC00_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_Config_SDMAC00_Callback_PE0_Address_Error
* Description  : This function handles the INTSDMACERR interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_SDMAC00_Callback_PE0_Address_Error(void)
{
    /* Start user code for R_Config_SDMAC00_Callback_PE0_Address_Error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SDMAC00_end_interrupt
* Description  : This function handles the INTSDMAC0CH0 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_SDMAC00_end_interrupt(enable=false, channel=47, fpu=true, callt=false)
void r_Config_SDMAC00_end_interrupt(void)
{
    /* Start user code for r_Config_SDMAC00_end_interrupt. Do not edit comment generated here */
      uint32_t var = SDMAC0.DMA0CHSTA_0.UINT32;
    
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;/* Enable writes to PWE register */
    PORT0.PWE = SETBIT(8U);         /* PWEP8:Enable Write Access for Port 8 */
    
    if(SDMAC0.DMA0CHSTA_0.BIT.DRQ) 
    {
        SDMAC0.DMA0CHFCR_0.BIT.DRQC = 1;
        D5 = 1;
    }
    
    if(SDMAC0.DMA0CHSTA_0.BIT.OVF) 
    {
        SDMAC0.DMA0CHFCR_0.BIT.OVFC = 1;
        
       D6 = 1;
    }
    
    if(SDMAC0.DMA0CHSTA_0.BIT.TE) 
    {
        SDMAC0.DMA0CHFCR_0.BIT.TEC = 1;
        //SDMAC0.DMA0SAR_0.UINT32 = _DMAC00_SOURCE_ADDRESS;
        D7 = 1;
    }
    
    if(SDMAC0.DMA0CHSTA_0.BIT.BUSY) 
    {
        //SDMAC0.DMA0CHFCR_0.BIT.TEC = 1; 
        D8 = 1;
    }
    

    D5 = 0;
    D6 = 0;
    D7 = 0;
    D8 = 0;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;/* Disable Write Access for all Ports */
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;/* Disable writes to PWE register */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
