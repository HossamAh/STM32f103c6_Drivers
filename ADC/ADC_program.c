/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  ADC_programs.c
 *  module:  ADC Module
 *  @details:  program  file for ADC Driver
*********************************************************************************************************************/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

#include "../RCC/RCC_interface.h"
#include "../AFIO/AFIO_interface.h"
#include "../GPIO/GPIO_interface.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  Global Variables
---------------------------------------------------------------------------------------------------------------------*/
/*******************************Interrupt callback function ************************/
void (*pRegularGroupCompleteCallback)();
void (*pInjectedGroupCompleteCallback)();
void (*pWatchDogCallback)();

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* @brief           : initialize ADC  
* @param       :   pInitConfig  pointer to ADC initalization configurations @ref ADC_InitTypeDef                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidInit(const ADC_InitTypeDef* pInitConfig)
{
    /*ADC1 has channels from 0 to 9 at port A*/
    /*configure pins*/
    /*enable clock for */
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_IOPA);
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_ADC1);
    MRCC_VoidSetADCPrescaler(pInitConfig->prescaler);

    uint8 Local_u8I=0;
    for(Local_u8I=0;Local_u8I<9;Local_u8I++)
    {
        uint8 Local_u8Val = READ_BIT(pInitConfig->channels,Local_u8I);
        if(Local_u8Val!=0)
            /*config pins as analog*/
            MGPIO_VoidSetPinMode_TYPE(_GPIOA_PORT,pin0+Local_u8I,INPUT_ANALOG);
    }

    /*set Data Alignment*/
    if(pInitConfig->DataAlignment == ADC_LEFT)
    {
        ADC->CR2.B.ALIGN = 1;
    }
    else if(pInitConfig->DataAlignment == ADC_RIGHT)
    {
        ADC->CR2.B.ALIGN = 0;
    }
    else{}

    /*set the continous or single conversion mode*/
    if(pInitConfig->ADC_ContinousMode == ADC_ENABLE)
    {
        ADC->CR2.B.CONT=1;
    }
    if(pInitConfig->ADC_ContinousMode == ADC_DISABLE)
    {
        ADC->CR2.B.CONT=0;
    }
    else{}
    
    /*set the scan mode*/
    if(pInitConfig->ADC_ScanMode == ADC_ENABLE)
    {
        ADC->CR1.B.SCAN=1;
        ADC->SQR1.B.L = pInitConfig->ADC_ScanModeConversionsNum;
    }
    else if(pInitConfig->ADC_ScanMode == ADC_DISABLE)
    {
        ADC->CR1.B.SCAN=0;
    }

    /*set discontinous mode*/
    if(pInitConfig->ADC_ScanMode == ADC_ENABLE)
    {
        if(pInitConfig->ADC_DisContinousMode == ADC_ENABLE)
        {
            ADC->CR1.B.DISCEN=1;
            ADC->CR1.B.DISCNUM=pInitConfig->ADC_DiscontinousModeConversionsNum;
        }
        else if(pInitConfig->ADC_DisContinousMode == ADC_DISABLE)
        {
            ADC->CR1.B.DISCEN=0;
        }
    }
}


/******************************************************************************
* @brief           : Configure the conversion on the regular channel  
* @param (in)      : -@ref Channels_t u8ChannelNumber  channel number to configure and start conversion.
* @param (in)      : -@ref samplingTime_t u8sampplingTime  channel number to configure and start conversion.
* @param (in)      : u8Rank rank (order) of the channel conversion in regular group value from 0 -16
* @retval          : void
*******************************************************************************/
void MADC_VoidConfigureChannel(uint8 u8ChannelNumber,uint8 u8samplingTime,uint8 u8Rank)
{
    static uint8 local_u8Rank=0;/*to be used if rank is not provided*/
    uint8 local_u8UsedRank;
    /*set the ranking of channel*/
    if(u8Rank>=0)/*provided*/
    {
        local_u8UsedRank=u8Rank;
    }
    else
    {
        local_u8UsedRank=local_u8Rank;
        /*not provided*/
        local_u8Rank++;
    }
    /*set rank of channel (specify the order of conversion for this channel)*/
    if(local_u8UsedRank <=6)
    {
        ADC->SQR3.r &= ~((0b11111)<<(local_u8UsedRank*5));//clear the channel sample time section
        ADC->SQR3.r |= ((u8ChannelNumber)<<(local_u8UsedRank*3));//clear the channel sample time section
    }
    else if(local_u8UsedRank>6 &&local_u8UsedRank<=12)
    {
        local_u8UsedRank-=6;
        ADC->SQR2.r &= ~((0b11111)<<(local_u8UsedRank*5));//clear the channel sample time section
        ADC->SQR2.r |= ((u8ChannelNumber)<<(local_u8UsedRank*3));//clear the channel sample time section
    }
    else if(local_u8UsedRank>12 &&local_u8UsedRank<=16)
    {
        local_u8UsedRank-=12;
        ADC->SQR1.r &= ~((0b11111)<<(local_u8UsedRank*5));//clear the channel sample time section
        ADC->SQR1.r |= ((u8ChannelNumber)<<(local_u8UsedRank*3));//clear the channel sample time section
    }
    else{}

    /*set sampling time*/
    if(u8ChannelNumber<=9)
    {
        ADC->SMPR2 &= ~((0b111)<<(u8ChannelNumber*3));//clear the channel sample time section
        ADC->SMPR2 |= ((u8samplingTime)<<(u8ChannelNumber*3));//clear the channel sample time section
    }
    else if(u8ChannelNumber>9 &&u8ChannelNumber<16)
    {
        u8ChannelNumber-=9;
        ADC->SMPR1 &= ~((0b111)<<(u8ChannelNumber*3));//clear the channel sample time section
        ADC->SMPR1 |= ((u8samplingTime)<<(u8ChannelNumber*3));//clear the channel sample time section
    }
    else if(u8ChannelNumber==16)//internal tempsensor
    {
        u8ChannelNumber-=9;
        //set TSVREFE bit
        ADC->CR2.B.TSVREFE=1;
        /*sampling time 17.1 us , freq=4MHZ after prescaler then cycle time 1/4us 71.5 cycles = 17.8us close to 17.1us*/
        ADC->SMPR1 &= ~((0b111)<<(u8ChannelNumber*3));//clear the channel sample time section
        ADC->SMPR1 |= ((u8samplingTime)<<(u8ChannelNumber*3));//clear the channel sample time section
    }
    else{}
}

/******************************************************************************
* @brief           : Configure and start the conversion on the regular channels  
* @param (in)      : -@ref ADC_Triggertype  ADC_Triggertype Specifies the ADC trigger type.                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidStartConversion(ADC_Trigger_t ADC_Triggertype)
{
    /*Enable ADC*/
    ADC->CR2.B.ADON = 1;
    
    /*according to trigger option start conversion or select the external trigger*/
    /*select the ADC external trigger*/
    ADC->CR2.B.EXTSEL = ADC_Triggertype;
    if(ADC_Triggertype==SWSTART)
    {
        ADC->CR2.B.SWSTART=1;
    }
}
/******************************************************************************
* @brief           : Stop the conversion on the regular channels  
* @param (in)      : void                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidStopConversion(void){
    ADC->CR2.B.ADON=0;
}

/******************************************************************************
* @brief           : Enable the interrupt and set the callbak function  
* @param (in)      : @ref ADC_Interrupt_t interruptType  interrupt type to enable
* @param (in)      : pInterruptCallback pointer to function to assign it to interrupt
* @retval          : void
*******************************************************************************/
void MADC_VoidEnableInterrupt(ADC_Interrupt_t interruptType,void (*pInterruptCallback)());

/******************************************************************************
* @brief           : Disable the interrupt   
* @param (in)      : @ref ADC_Interrupt_t interruptType  interrupt type to enable
* @retval          : void
*******************************************************************************/
void MADC_VoidDisableInterrupt(ADC_Interrupt_t interruptType);


/** TODO: DMA and Analog Watchdog */


/******************************************************************************
* @brief           : Polling on EOC to read the conversion Data on the regular channels  
* @param (in)      : void                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidPollOnConversion(void) 
{
    while(ADC->SR.B.EOC != 1);/*wait until hardware set it*/
}

/******************************************************************************
* @brief           : Read the conversion Data on the regular channels  
* @param (in)      : void                                                                         
* @retval          : uint16 Data Read from Regular Data register (12bit resoultion)
*******************************************************************************/
uint16 MADC_VoidGetConversionData(void)
{
    return ADC->DR.B.REGULARDATA;
}