/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  DMA_programs.c
 *  module:  DMA Module
 *  @details:  program  file for DMA Driver
*********************************************************************************************************************/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "DMA_config.h"
#include "DMA_private.h"
#include "DMA_interface.h"

#include "../RCC/RCC_interface.h"
#include "../AFIO/AFIO_interface.h"
#include "../GPIO/GPIO_interface.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  Global Variables
---------------------------------------------------------------------------------------------------------------------*/
/*******************************Interrupt callback function ************************/
void (*pTransmissionCompleteCallback[7])()={NULL};
void (*pTransmissionHalfCompleteCallback[7])()={NULL};
void (*pTransmissionErrorCallback[7])()={NULL};


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/


/******************************************************************************
* @brief           : initialize DMA  channel according to the request required
* @param       :   pInitConfig  pointer to DMA initalization configurations @ref DMA_InitTypeDef                                                                        
* @retval          : void
*******************************************************************************/
void MDMA_VoidChannelInit(const DMA_InitTypeDef* pInitConfig)
{
    uint8 Local_u8ChannelNummber=0;
    /*get the channel number according to the request*/
    if(pInitConfig->Peripheral<=DMA_PERIPHERAL_TIM4_CH1)
    {
        Local_u8ChannelNummber = 0;//ch1
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_TIM4_CH1 && pInitConfig->Peripheral<=DMA_PERIPHERAL_SPI1_RX)
    {
        Local_u8ChannelNummber = 1;//ch2
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_SPI1_RX && pInitConfig->Peripheral<=DMA_PERIPHERAL_SPI1_TX)
    {
        Local_u8ChannelNummber = 2;//ch3
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_SPI1_TX && pInitConfig->Peripheral<=DMA_PERIPHERAL_I2C2_TX)
    {
        Local_u8ChannelNummber = 3;//ch4
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_I2C2_TX && pInitConfig->Peripheral<=DMA_PERIPHERAL_I2C2_RX)
    {
        Local_u8ChannelNummber = 4;//ch5
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_I2C2_RX && pInitConfig->Peripheral<=DMA_PERIPHERAL_I2C1_TX)
    {
        Local_u8ChannelNummber = 5;//ch6
    }
    else if(pInitConfig->Peripheral>DMA_PERIPHERAL_I2C1_TX && pInitConfig->Peripheral<=DMA_PERIPHERAL_I2C1_RX)
    {
        Local_u8ChannelNummber = 6;//ch7
    }
    else{}
    
    /*set the peripheral address(initial address in case of pointer increament)*/
    DMA->CHx[Local_u8ChannelNummber].CPARx = (uint32)pInitConfig->DMA_Peripheral_address;
    
    /*set the memory address(initial address in case of pointer increament)*/
    DMA->CHx[Local_u8ChannelNummber].CMARx = (uint32)pInitConfig->DMA_Memory_address;

    /*set number of transactions*/
    DMA->CHx[Local_u8ChannelNummber].CNDTRx.B.NDT = pInitConfig->DMA_Data_Number;

    /*set channel priority*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.PL = pInitConfig->DMA_Channel_Priority;
    
    /*transfer Direction*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.DIR = pInitConfig->DMA_Direction;

    /*set mem2mem mode*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.MEM2MEM = pInitConfig->DMA_Mem2MemMode;
    
    /*circular mode*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.CIRC = pInitConfig->DMA_CircularMode;
    
    /*set peripheral pointer inrement*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.PINC = pInitConfig->DMA_PERIPHERAL_PTR_INC;
    
    /*set memory pointer inrement*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.MINC = pInitConfig->DMA_MEMORY_PTR_INC;
    
    /*set peripheral data size*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.PSIZE = pInitConfig->DMA_PERIPHERAL_Data_Size;
    
    /*set memory data size*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.MSIZE = pInitConfig->DMA_MEMORY_Data_Size;

    /*Activate the channel request*/
    DMA->CHx[Local_u8ChannelNummber].CCRx.B.EN=DMA_ENABLE;
}

/******************************************************************************
* @brief           : Enable the interrupt on channel and set the callback function  
* @param           :  channelNumber  interrupt channel to enable. 
* @param           :  interruptType  of interrupt channel to enable. @ref DMA_Interrupt_t
* @param           : pInterruptCallback pointer to function to assign it to interrupt
* @retval          : void
*******************************************************************************/
void MDMA_VoidEnableInterrupt(uint8 channelNumber,uint8 interruptType,void (*pInterruptCallback)())
{
    switch (interruptType)
    {
    case DMA_INTERRUPT_COMPLETE_TRANSMISSION:
        DMA->CHx[channelNumber].CCRx.B.TCIE=DMA_ENABLE;
        pTransmissionCompleteCallback[channelNumber]=pInterruptCallback;
        break;
    case DMA_INTERRUPT_HALF_TRANSMISSION:
        DMA->CHx[channelNumber].CCRx.B.HTIE=DMA_ENABLE;
        pTransmissionHalfCompleteCallback[channelNumber]=pInterruptCallback;
        break;
    case DMA_INTERRUPT_ERROR_TRANSMISSION:
        DMA->CHx[channelNumber].CCRx.B.TEIE=DMA_ENABLE;
        pTransmissionErrorCallback[channelNumber]=pInterruptCallback;
        break;
    default:
        break;
    }
}
/******************************************************************************
* @brief           : Disable the interrupt   
* @param           :  channelNumber  interrupt channel to disable.
* @param           :  interruptType  of interrupt channel to disable. @ref DMA_Interrupt_t
* @retval          : void
*******************************************************************************/
void MDMA_VoidDisableInterrupt(uint8 channelNumber)
{
    DMA->CHx[channelNumber].CCRx.B.TCIE=DMA_DISABLE;
    DMA->CHx[channelNumber].CCRx.B.TEIE=DMA_DISABLE;
    DMA->CHx[channelNumber].CCRx.B.HTIE=DMA_DISABLE;
}

/******************************************************************************
* @brief           : Polling on end of transmission of DMA data  
* @param           :  channelNumber  interrupt channel to wait on.                                                                         
* @retval          : void
*******************************************************************************/
void MDMA_VoidPollOnTransmission(uint8 channelNumber)
{
    /*wait on the transmission complete flag*/
    while (READ_BIT(DMA->ISR,4*channelNumber+1)==0);
}


/******************************interrupt handlers************************ */
void DMA1_Channel1_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[0].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*0+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[0]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*0+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[0].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*0+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[0]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*0+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[0].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*0+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[0]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*0+3);
    }
    else{}
}

void DMA1_Channel2_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[1].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*1+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[1]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*1+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[1].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*1+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[1]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*1+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[1].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*1+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[1]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*1+3);
    }
    else{}
}

void DMA1_Channel3_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[2].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*2+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[2]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*2+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[2].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*2+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[2]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*2+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[2].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*2+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[2]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*2+3);
    }
    else{}
}

void DMA1_Channel4_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[3].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*3+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[3]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*3+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[3].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*3+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[3]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*3+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[3].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*3+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[3]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*3+3);
    }
    else{}
}

void DMA1_Channel5_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[4].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*4+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[4]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*4+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[4].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*4+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[4]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*4+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[4].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*4+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[4]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*4+3);
    }
    else{}
}

void DMA1_Channel6_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[5].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*5+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[5]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*5+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[5].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*5+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[5]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*5+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[5].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*5+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[5]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*5+3);
    }
    else{}
}

void DMA1_Channel7_IRQHandler(void)
{
    /*complete transmission*/
    if(DMA->CHx[6].CCRx.B.TCIE==1 && READ_BIT(DMA->ISR,4*6+1)==1)
    {
        /*call interrupt callback*/
        pTransmissionCompleteCallback[6]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*6+1);
    }
    /*Half complete transmission*/
    else if(DMA->CHx[6].CCRx.B.HTIE==1 && READ_BIT(DMA->ISR,4*6+2)==1)
    {
        /*call interrupt callback*/
        pTransmissionHalfCompleteCallback[6]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*6+2);
    }
        /*Half complete transmission*/
    else if(DMA->CHx[6].CCRx.B.TEIE==1 && READ_BIT(DMA->ISR,4*6+3)==1)
    {
        /*call interrupt callback*/
        pTransmissionErrorCallback[6]();
        /*clear interrup flag*/
        SET_BIT(DMA->IFCR,4*6+3);
    }
    else{}
}

/******************************************************************************
* @brief           : initialize DMA  channel according to the request required
* @param           :  channelNumber   channel to disable.                                                                        
* @retval          : void
*******************************************************************************/
void MDMA_VoidDisableChannel(uint8 channel_Number)
{
    DMA->CHx[channel_Number].CCRx.B.EN=0;
}