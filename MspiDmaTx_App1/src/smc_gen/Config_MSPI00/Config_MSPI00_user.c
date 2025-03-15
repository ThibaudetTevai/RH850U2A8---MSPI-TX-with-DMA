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
* File Name        : Config_MSPI00_user.c
* Component Version: 1.3.1
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_MSPI00.
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
#include "Config_MSPI00.h"
/* Start user code for include. Do not edit comment generated here */
#include "Config_SDMAC00.h"
extern uint8_t EndSending;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t  g_mspi00_tx_num;                        /* mspi0 transmit data number */
extern volatile uint32_t  g_mspi00_rx_num;                        /* mspi0 receive data number */
extern volatile uint32_t  g_mspi00_rx_total_num;                  /* mspi0 receive data total times */
extern volatile uint16_t * gp_mspi00_tx_address;                  /* mspi0 transmit buffer address */
extern volatile uint16_t * gp_mspi00_rx_address;                  /* mspi0 receive buffer address */
void r_Config_MSPI00_callback_sendend(void);
void r_Config_MSPI00_callback_receiveend(void);
void r_Config_MSPI00_callback_error(uint32_t err_type);
/* Start user code for global. Do not edit comment generated here */
volatile uint32_t *ptr = (volatile uint32_t *)_DMAC00_DESTINATION_ADDRESS; // Création du pointeur
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Create_UserInit
* Description  : This function adds user code after initializing MSPI module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Callback_Interrupt_Send
* Description  : This function is MSPI0 send interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Callback_Interrupt_Send(void)
{
    uint32_t temp_intmsk = 0U;

    temp_intmsk = MSPI0_INTF.MSPI0INTMSK0.UINT32;
    MSPI0_INTF.MSPI0INTMSK0.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI0_INTF.MSPI0INTF0.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI0_INTF.MSPI0INTFC0.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;

        if (g_mspi00_tx_num > 0U)
        {
            /* Set transmit data */
            MSPI0.TXDA00.UINT32 = *gp_mspi00_tx_address;
            gp_mspi00_tx_address++;
            g_mspi00_tx_num--;
        }
        else
        {
            r_Config_MSPI00_callback_sendend();
        }
    }
    MSPI0_INTF.MSPI0INTMSK0.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Callback_Interrupt_Receive
* Description  : This function is MSPI0 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Callback_Interrupt_Receive(void)
{
    uint8_t err_type = 0U;
    uint32_t temp_intmsk = 0U;
    uint32_t temp = 0U;

    temp_intmsk = MSPI0_INTF.MSPI0INTMSK1.UINT32;
    MSPI0_INTF.MSPI0INTMSK1.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI0_INTF.MSPI0INTF1.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI0_INTF.MSPI0INTFC1.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        err_type = (MSPI0.FRERST0.UINT8 & (_MSPI_CRC_ERROR_DETECTED | _MSPI_PARITY_ERROR_DETECTED));
        MSPI0.FRERSTC0.UINT8 |= (_MSPI_CONSISTENCY_ERROR_CLEAR | _MSPI_CRC_ERROR_CLEAR | _MSPI_PARITY_ERROR_CLEAR);
        if (err_type == 0U)
        {
            temp = g_mspi00_rx_total_num;
            if (g_mspi00_rx_num < temp)
            {
                *gp_mspi00_rx_address = MSPI0.RXDA00.UINT32;
                gp_mspi00_rx_address++;
                g_mspi00_rx_num++;
            }
            if (g_mspi00_rx_num >= temp)
            {
                r_Config_MSPI00_callback_receiveend();
            }
        }
    }
    MSPI0_INTF.MSPI0INTMSK1.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_channel00_interrupt_send
* Description  : This function is MSPI00 send interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI00_channel00_interrupt_send(enable=false, channel=244, fpu=true, callt=false)
void r_Config_MSPI00_channel00_interrupt_send(void)
{
    /* Start user code for r_Config_MSPI00_channel00_interrupt_send. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_channel00_interrupt_receive
* Description  : This function is MSPI000 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI00_channel00_interrupt_receive(enable=false, channel=245, fpu=true, callt=false)
void r_Config_MSPI00_channel00_interrupt_receive(void)
{
    /* Start user code for r_Config_MSPI00_channel00_interrupt_receive. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Callback_Interrupt_Error
* Description  : This function is MSPI0 error interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Callback_Interrupt_Error(void)
{
    uint8_t err_type = 0U;
    uint32_t temp_intmsk = 0U;

    temp_intmsk = MSPI0_INTF.MSPI0INTMSK3.UINT32;
    MSPI0_INTF.MSPI0INTMSK3.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI0_INTF.MSPI0INTF3.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI0_INTF.MSPI0INTFC3.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        err_type = (MSPI0.CEST0.UINT8 & (_MSPI_CHANNEL_CONSISTENCY_ERROR_DETECTED | _MSPI_CHANNEL_CRC_ERROR_DETECTED | 
                   _MSPI_CHANNEL_PARITY_ERROR_DETECTED | _MSPI_CHANNEL_OVER_READ_ERROR_DETECTED | 
                   _MSPI_CHANNEL_OVER_WRITE_ERROR_DETECTED | _MSPI_CHANNEL_OVER_RUN_ERROR_DETECTED));
        MSPI0.CESTC0.UINT8 |= (_MSPI_CHANNEL_CONSISTENCY_ERROR_CLEAR | _MSPI_CHANNEL_CRC_ERROR_CLEAR | 
                              _MSPI_CHANNEL_PARITY_ERROR_CLEAR | _MSPI_CHANNEL_OVER_READ_ERROR_CLEAR | 
                              _MSPI_CHANNEL_OVER_WRITE_ERROR_CLEAR | _MSPI_CHANNEL_OVER_RUN_ERROR_CLEAR);
        if (err_type != 0U)
        {
            r_Config_MSPI00_callback_error(err_type);
        }
    }
    MSPI0_INTF.MSPI0INTMSK3.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Callback_Interrupt_Frameend
* Description  : This function is MSPI0 frame end interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Callback_Interrupt_Frameend(void)
{
    uint32_t temp_intmsk = 0U;

    temp_intmsk = MSPI0_INTF.MSPI0INTMSK2.UINT32;
    MSPI0_INTF.MSPI0INTMSK2.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI0_INTF.MSPI0INTF2.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI0_INTF.MSPI0INTFC2.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        r_Config_MSPI00_callback_sendend();
        r_Config_MSPI00_callback_receiveend();
        /* Start user code for R_Config_MSPI00_Callback_Interrupt_Frameend. Do not edit comment generated here */
        EndSending = 1;
        /* End user code. Do not edit comment generated here */
    }
    MSPI0_INTF.MSPI0INTMSK2.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_callback_sendend
* Description  : This function is MSPI0 sendend callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI00_callback_sendend(void)
{
    /* Start user code for r_Config_MSPI00_callback_sendend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_callback_receiveend
* Description  : This function is MSPI0 receiveend callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI00_callback_receiveend(void)
{
    /* Start user code for r_Config_MSPI00_callback_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_callback_error
* Description  : This function is MSPI0 error callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI00_callback_error(uint32_t err_type)
{
    /* Start user code for r_Config_MSPI00_callback_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

