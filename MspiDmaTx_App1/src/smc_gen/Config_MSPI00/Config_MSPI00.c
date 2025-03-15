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
* File Name        : Config_MSPI00.c
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
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
volatile uint32_t  g_mspi00_tx_num;                         /* mspi00 transmit data number */
volatile uint32_t  g_mspi00_rx_num;                         /* mspi00 receive data number */
volatile uint32_t  g_mspi00_rx_total_num;                   /* mspi00 receive data total times */
volatile uint32_t * gp_mspi00_tx_address;                   /* mspi00 transmit buffer address */
volatile uint32_t * gp_mspi00_rx_address;                   /* mspi00 receive buffer address */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Create
* Description  : This function initializes the Config_MSPI00 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Create(void)
{
    /* Set MSPI0 control setting */
    MSPI0.CTL1.UINT32 = _MSPI_SAMPLE_STANDARD | _MSPI_CLOCK_DEFAULT_LOW | _MSPI_MSPISOUT_ENABLE_LOW_END_HOLD | 
                        _MSPI_CS7_SIGNAL_ACTIVE_LOW | _MSPI_CS6_SIGNAL_ACTIVE_LOW | _MSPI_CS5_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS4_SIGNAL_ACTIVE_LOW | _MSPI_CS3_SIGNAL_ACTIVE_LOW | _MSPI_CS2_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS1_SIGNAL_ACTIVE_LOW | _MSPI_CS0_SIGNAL_ACTIVE_LOW | _MSPI_MASTER_MODE | 
                        _MSPI_CS_SIGNAL_IGNORED | _MSPI_SAMPLE_STANDARD;
    MSPI0.CTL2.UINT8 = _MSPI_CONSISTENCY_DISABLE | _MSPI_LOOPBACK_DISABLE;
    /* Enable MSPI0 operation */
    MSPI0.CTL0.UINT8 = _MSPI_FUNCTION_ENABLE;
    /* Set MSPI0 configuration setting */
    MSPI0.CFG00.UINT32 = _MSPI_TRANSMISSION_ENABLE | _MSPI_RECEPTION_ENABLE | _MSPI_DIRECT_MODE | 
                         _MSPI_CHANNEL_PRIORITY_LEVEL8 | _MSPI_CHANNEL_LOCK_OPERATION_DISABLE | 
                         _MSPI_CHANNEL_OPERATION_END | _MSPI_INTMSPITX_INTERRUPT_ENABLE | 
                         _MSPI_INTMSPIRX_INTERRUPT_ENABLE | _MSPI_INTMSPIFE_INTERRUPT_ENABLE | 
                         _MSPI_INTMSPIERR_INTERRUPT_ENABLE;
    MSPI0.CFG01.UINT32 = _MSPI_SPCK_IDLE_LOW | _MSPI_SCK_PHASE_SHIFT_ODD_EDGES | _MSPI_COMMUNICATION_MSB | 
                         _MSPI_HOLD_INACTIVE_LEVEL | _MSPI_IDLE_TIME_NOT_INSERTED | _MSPI_CS_IDLE_LEVEL_INACTIVE | 
                         _MSPI_NO_CHECK | _MSPI_SAFE_SPI_DISABLE;
    MSPI0.CFG02.UINT16 = _MSPI00_FRAME_LENGTH;
    MSPI0.CFG03.UINT16 = _MSPI_CLOCK_FREQUENCY_DIVISION_1 | _MSPI00_CLOCK_FREQUENCY_DIVISION;
    MSPI0.CFG04.UINT32 = _MSPI_FIFO_SIZE_8 | _MSPI00_HARDWARE_TRIGGER_DISABLE;
    MSPI0.RASTAD0.UINT16 = _MSPI00_RAMSTART_ADDRESS;
    MSPI0.SEUP0.UINT16 = _MSPI00_SETUP_TIME;
    MSPI0.HOLD0.UINT16 = _MSPI00_HOLD_TIME;
    MSPI0.IDLE0.UINT16 = _MSPI00_IDLE_TIME;
    MSPI0.INDA0.UINT16 = _MSPI00_INTER_DATA_TIME;
    MSPI0.CFSET0.UINT16 = _MSPI00_FRAME_COUNT;
    MSPI0.SSEL0.UINT16 = _MSPI_ACTIVATE_CS0 | _MSPI_DEACTIVATE_CS1 | _MSPI_DEACTIVATE_CS2 | _MSPI_DEACTIVATE_CS3 | 
                         _MSPI_DEACTIVATE_CS4 | _MSPI_DEACTIVATE_CS5 | _MSPI_DEACTIVATE_CS6 | _MSPI_DEACTIVATE_CS7;
    MSPITG.CTL0.UINT32 &= _MSPI_CHANNEL0_TRIGGER_SET_CLEAR;
    MSPITG.CTL0.UINT32 |= _MSPI_TRIGGER1_TX0_TRIGGER2_NONE;
    MSPITG.CTL0.UINT32 |= _MSPI_CHANNEL0_DMA_TRIGGER_ENABLE;
    MSPI0_INTF.MSPI0INTMSK0.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI0_INTF.MSPI0INTMSK1.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI0_INTF.MSPI0INTMSK3.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI0_INTF.MSPI0INTMSK2.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    /* Synchronization processing */
    g_cg_sync_read = MSPI0.CTL1.UINT32;
    __syncp();

    /* Set MSPI0SC pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(5U);
    PORT0.PCR4_6.UINT32 = (PORT0.PCR4_6.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR4_6.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR4_6.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR4_6.UINT32 |= _PCR_ALT_OUT2;
    PORT0.PCR4_6.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR4_6.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR4_6.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI0SO pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(5U);
    PORT0.PCR4_5.UINT32 = (PORT0.PCR4_5.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR4_5.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR4_5.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR4_5.UINT32 |= _PCR_DIRECT_ALT_MODE2;
    PORT0.PCR4_5.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR4_5.UINT32 &= _PCR_DIRECT_ALT_MODE_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI0SI pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(5U);
    PORT0.PCR4_7.UINT32 = (PORT0.PCR4_7.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR4_7.UINT32 |= _PCR_ALT_IN2;
    PORT0.PCR4_7.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI0CSS0 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(5U);
    PORT0.PCR4_4.UINT32 = (PORT0.PCR4_4.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR4_4.UINT32 |= _PCR_ALT_OUT2;
    PORT0.PCR4_4.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR4_4.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR4_4.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_Config_MSPI00_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_enable_interrupt
* Description  : This function enables interrupt operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI00_enable_interrupt(void)
{
    INTC2.EIC244.BIT.EIRF244 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC244.BIT.EIMK244 = _INT_PROCESSING_ENABLED;
    INTC2.EIC245.BIT.EIRF245 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC245.BIT.EIMK245 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI00_disable_interrupt
* Description  : This function disables interrupt operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI00_disable_interrupt(void)
{
    INTC2.EIC244.BIT.EIMK244 = _INT_PROCESSING_DISABLED;
    INTC2.EIC244.BIT.EIRF244 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC245.BIT.EIMK245 = _INT_PROCESSING_DISABLED;
    INTC2.EIC245.BIT.EIRF245 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Start
* Description  : This function starts the Config_MSPI00 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Start(void)
{
    /* Clear MSPI00 interrupt request and enable operation */
    r_Config_MSPI00_enable_interrupt();
    /* Enable MSPI0 channel 0 operation */
    MSPI0.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Stop
* Description  : This function stops the MSPI0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Stop(void)
{
    /* Disable MSPI0 channel 0 operation */
    MSPI0.CSTC0.UINT8 = _MSPI_CHANNEL_CLEAR_ENABLE_FLAG;
    /* Disable MSPI00 interrupt operation and clear request */
    r_Config_MSPI00_disable_interrupt();
    /* Synchronization processing */
    g_cg_sync_read = MSPI0.CTL0.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Send
* Description  : This function sends MSPI0 data.
* Arguments    : tx_buf -
*                    send buffer pointer
* Return Value : MD_STATUS -
*                    the status of sending
***********************************************************************************************************************/
MD_STATUS R_Config_MSPI00_Send(uint32_t* const tx_buf)
{
    /* Set transmit setting */
    gp_mspi00_tx_address = (uint32_t *)tx_buf;
    g_mspi00_tx_num = _MSPI00_FRAME_COUNT;

    return MD_OK;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Receive
* Description  : This function receives MSPI0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
* Return Value : MD_STATUS -
*                    the status of receiving
***********************************************************************************************************************/
MD_STATUS R_Config_MSPI00_Receive(uint32_t* rx_buf)
{
    /* Set receive setting */
    gp_mspi00_rx_address = rx_buf;
    g_mspi00_rx_total_num = _MSPI00_FRAME_COUNT;
    g_mspi00_rx_num = 0U;

    return MD_OK;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI00_Software_Trigger
* Description  : This function sets software trigger.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI00_Software_Trigger()
{
    MSPI0.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ACTIVE_FLAG | _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
