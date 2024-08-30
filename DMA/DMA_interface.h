/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  DMA_interface.h
 *  module:  DMA Module
 *  @details:  interface header file for DMA Driver
*********************************************************************************************************************/
#ifndef _DMA_INTERFACE_H
#define _DMA_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/

/** @defgroup State_t */
#define DMA_ENABLE          (0x1)/*!< ENABLE  */
#define DMA_DISABLE          (0x0)/*!< DISABLE  */

/** @defgroup PriorityLevels_t */
#define DMA_PRIORITY_LOW         (0x0)/*!< low priority  */
#define DMA_PRIORITY_MEDIUM         (0x1)/*!< medium priority  */
#define DMA_PRIORITY_HIGH         (0x2)/*!< High priority  */
#define DMA_PRIORITY_VERY_HIGH         (0x3)/*!< very_High priority  */

/** @defgroup DataSize_t */
#define DMA_SIZE_8_BIT         (0x0)/*!< 8-bit  */
#define DMA_SIZE_16_BIT         (0x1)/*!< 16-bit  */
#define DMA_SIZE_32_BIT         (0x2)/*!< 32-bit  */

/** @defgroup TransferDirection_t */
#define DMA_DIRECTION_READ_FROM_PERIPHERAL         (0x0)/*!< read from peripheral  */
#define DMA_DIRECTION_READ_FROM_MEMORY         (0x1)/*!< read from peripheral  */

/** @defgroup DMA_Interrupt_t */
#define DMA_INTERRUPT_COMPLETE_TRANSMISSION     (0x0)
#define DMA_INTERRUPT_HALF_TRANSMISSION         (0x1)
#define DMA_INTERRUPT_ERROR_TRANSMISSION         (0x2)


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/** @brief DMA_perpheral_t peripheral to select the channel according*/
typedef enum
{
  /*ch1*/
  DMA_PERIPHERAL_ADC1, 
  DMA_PERIPHERAL_TIM2_CH3, 
  DMA_PERIPHERAL_TIM4_CH1,
  /*ch2*/
  DMA_PERIPHERAL_USART3_TX, 
  DMA_PERIPHERAL_TIM1_CH1, 
  DMA_PERIPHERAL_TIM2_UP, 
  DMA_PERIPHERAL_TIM3_CH3, 
  DMA_PERIPHERAL_SPI1_RX,
  /*ch3*/
  DMA_PERIPHERAL_USART3_RX, 
  DMA_PERIPHERAL_TIM1_CH2, 
  DMA_PERIPHERAL_TIM3_CH4, 
  DMA_PERIPHERAL_TIM3_UP, 
  DMA_PERIPHERAL_SPI1_TX,
  /*ch4*/
  DMA_PERIPHERAL_USART1_TX,
  DMA_PERIPHERAL_TIM1_CH4,
  DMA_PERIPHERAL_TIM1_TRIG,
  DMA_PERIPHERAL_TIM1_COM,
  DMA_PERIPHERAL_TIM4_CH2,
  DMA_PERIPHERAL_SPI_I2S2_RX,
  DMA_PERIPHERAL_I2C2_TX,
  /*ch5*/
  DMA_PERIPHERAL_USART1_RX,
  DMA_PERIPHERAL_TIM1_UP,
  DMA_PERIPHERAL_SPI_I2S2_TX,
  DMA_PERIPHERAL_TIM2_CH1,
  DMA_PERIPHERAL_TIM4_CH3,
  DMA_PERIPHERAL_I2C2_RX,
  /*ch6*/
  DMA_PERIPHERAL_USART2_RX,
  DMA_PERIPHERAL_TIM1_CH3,
  DMA_PERIPHERAL_TIM3_CH1,
  DMA_PERIPHERAL_TIM3_TRIG,
  DMA_PERIPHERAL_I2C1_TX,
  /*ch7*/
  DMA_PERIPHERAL_USART2_TX,
  DMA_PERIPHERAL_TIM2_CH2,
  DMA_PERIPHERAL_TIM2_CH4,
  DMA_PERIPHERAL_TIM4_UP,
  DMA_PERIPHERAL_I2C1_RX,
}DMA_perpheral_t;
/**
  * @brief  DMA Configure Channel structure definition
  */
typedef struct
{

    DMA_perpheral_t Peripheral;                       /*!< Specifies the peripheral
                                                    this parameter can be a value of @ref DMA_perpheral_t*/
    uint32* DMA_Peripheral_address;                    /*!< Specifies the DMA Peripheral address */   

    uint32* DMA_Memory_address;                    /*!< Specifies the DMA Memory address */ 

    uint32 DMA_Data_Number;                    /*!< Specifies the DMA Data number
                                                  this parmeter can be a value of 0-65535 */   
    
    uint32 DMA_Channel_Priority;                    /*!< Specifies the DMA Channel priority
                                                  this parmeter can be a value of @ref PriorityLevels_t */   

    uint8 DMA_Mem2MemMode;                               /*!< Specifies the DMA Channel mem2mem mode
                                                  this parmeter can be a value of @ref State_t */   

    uint8 DMA_Direction;                                /*!< Specifies the DMA Channel direction
                                                  this parmeter can be a value of @ref TransferDirection_t */   

    uint8 DMA_CircularMode;                                /*!< Specifies the DMA Channel circular mode
                                                  this parmeter can be a value of @ref State_t */   

    uint8 DMA_PERIPHERAL_PTR_INC;                                /*!< Specifies the DMA Channel peripheral pointer increment
                                                  this parmeter can be a value of @ref State_t */   
    uint8 DMA_MEMORY_PTR_INC;                                /*!< Specifies the DMA Channel memory pointer increment
                                                  this parmeter can be a value of @ref State_t */   

    uint8 DMA_PERIPHERAL_Data_Size;                                /*!< Specifies the DMA Channel peripheral Data size
                                                  this parmeter can be a value of @ref DataSize_t */   
    uint8 DMA_MEMORY_Data_Size;                                /*!< Specifies the DMA Channel memory Data size
                                                  this parmeter can be a value of @ref DataSize_t */
} DMA_InitTypeDef;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* @brief           : initialize DMA  channel according to the request required
* @param       :   pInitConfig  pointer to DMA initalization configurations @ref DMA_InitTypeDef                                                                        
* @retval          : void
*******************************************************************************/
void MDMA_VoidChannelInit(const DMA_InitTypeDef* pInitConfig) ;

/******************************************************************************
* @brief           : initialize DMA  channel according to the request required
* @param           :  channelNumber   channel to disable.                                                                        
* @retval          : void
*******************************************************************************/
void MDMA_VoidDisableChannel(uint8 channel_Number) ;

// /******************************************************************************
// * @brief           : Enable request channel to acivate the channel  
// * @param           : Peripheral to request @ref DMA_perpheral_t                                                                        
// * @param           : numberOfData number of data to transfer                                                                         
// * @retval          : void
// *******************************************************************************/
// void MDMA_VoidEnableRequest(DMA_perpheral_t Peripheral,uint8 numberOfData);

/******************************************************************************
* @brief           : Enable the interrupt on channel and set the callback function  
* @param           :  channelNumber  interrupt channel to enable. 
* @param           :  interruptType  of interrupt channel to enable. @ref DMA_Interrupt_t
* @param           : pInterruptCallback pointer to function to assign it to interrupt
* @retval          : void
*******************************************************************************/
void MDMA_VoidEnableInterrupt(uint8 channelNumber,uint8 interruptType,void (*pInterruptCallback)());

/******************************************************************************
* @brief           : Disable the interrupt   
* @param           :  channelNumber  interrupt channel to disable.
* @retval          : void
*******************************************************************************/
void MDMA_VoidDisableInterrupt(uint8 channelNumber);

/******************************************************************************
* @brief           : Polling on end of transmission of DMA data  
* @param           :  channelNumber  interrupt channel to wait on.                                                                         
* @retval          : void
*******************************************************************************/
void MDMA_VoidPollOnTransmission(uint8 channelNumber) ;


#endif
