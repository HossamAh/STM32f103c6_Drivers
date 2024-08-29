/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  ADC_interface.h
 *  module:  ADC Module
 *  @details:  interface header file for ADC Driver
*********************************************************************************************************************/
#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/

/** @defgroup State_t */
#define ADC_ENABLE          (0x1)/*!< ENABLE  */
#define ADC_DISABLE          (0x0)/*!< DISABLE  */

/** @defgroup samplingTime_t */
#define ADC_Sample1_5Cycles         (0x0)/*!< 1.5cycle  */
#define ADC_Sample7_5Cycles         (0x1)/*!< 7.5cycle  */
#define ADC_Sample13_5Cycles         (0x2)/*!< 13.5cycle  */
#define ADC_Sample28_5Cycles         (0x3)/*!< 28.5cycle  */
#define ADC_Sample41_5Cycles         (0x4)/*!< 41.5cycle  */
#define ADC_Sample55_5Cycles         (0x5)/*!< 55.5cycle  */
#define ADC_Sample71_5Cycles         (0x6)/*!< 71.5cycle  */
#define ADC_Sample239_5Cycles         (0x7)/*!< 239.5cycle  */

/** @defgroup Channels_t */
#define ADC_CH0               (0b01)
#define ADC_CH1               (0b10)
#define ADC_CH2               (0b100)
#define ADC_CH3               (0x1000)
#define ADC_CH4               (0x10000)
#define ADC_CH5               (0b100000)
#define ADC_CH6               (0b1000000)
#define ADC_CH7               (0b10000000)
#define ADC_CH8               (0b100000000)
#define ADC_CH9               (0b1000000000)
#define ADC_CH10              (0b10000000000)
#define ADC_CH11              (0b100000000000)
#define ADC_CH12              (0b1000000000000)
#define ADC_CH13              (0b10000000000000)
#define ADC_CH14              (0b100000000000000)
#define ADC_CH15              (0b1000000000000000)
#define ADC_CH16              (0b10000000000000000)
#define ADC_CH17              (0b100000000000000000)
#define ADC_CH18              (0b1000000000000000000)




/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/**  
* @enum ACD_PRESCALER_t ADC prescaler value enum
*/
typedef enum
{
  PCLK2_2,
  PCLK2_4,
  PCLK2_6,
  PCLK2_8,
}ACD_PRESCALER_t;



/**  
* @enum ADC_AlignmentDir_t DataAlignment Direction enum
*/
typedef enum
{
    ADC_LEFT,
    ADC_RIGHT,
}ADC_AlignmentDir_t;

/**  
* @enum ADC_Trigger_t Trigger type enum
*/
typedef enum
{
    TIM1_CC1,
    TIM1_CC2,
    TIM1_CC3,
    TIM2_CC2,
    TIM3_TRGO,
    TIM4_CC4,
    EXTI_line_11_TIM8_TRGO,
    SWSTART,
}ADC_Trigger_t;

/**  
* @enum ADC_Interrupt_t interrupt type enum
*/
typedef enum
{
    ADC_REGULAR_GROUP_CHANNEL_COMPLETE,
    ADC_INJECTED_GROUP_CHANNEL_COMPLETE,
    ADC_WATCHDOG_VIOLATION,
}ADC_Interrupt_t;

/**
  * @brief  ADC init structure definition
  */
typedef struct
{

    ADC_AlignmentDir_t DataAlignment;                       /*!< Specifies the ADC data alignment direction
                                                    this parameter can be a value of @ref ADC_AlignmentDir_t*/
    uint8 ADC_ScanMode;                                     /*!< Specifies the ADC scan mode state
                                                    this parameter can be a value of @ref State_t*/        
    uint8 ADC_ContinousMode;                                /*!< Specifies the ADC continous mode state
                                                                *ADC_ENABLE for continous conversion 
                                                                *ADC_DISABLE for single conversion  
                                                    *this parameter can be a value of @ref State_t*/
    uint8 ADC_DisContinousMode;                                /*!< Specifies the ADC Discontinous mode state
                                                                *to be enabled the ADC_ScanMode must be enable
                                                                *ADC_ENABLE for split the group conversions
                                                                *ADC_DISABLE for run the group conversion without breaks  
                                                    *this parameter can be a value of @ref State_t*/
    uint8 ADC_DiscontinousModeConversionsNum;                   /*!< Specifies the ADC conversions number at each trigger  
                                                    *this parameter can be a value of range 1 to 8*/

    uint8 ADC_ScanModeConversionsNum;                           /*!< Specifies the ADC conversions number  
                                                    *this parameter can be a value of range 1 to 16*/

    uint32 channels;                                  /*!<specifies the ADC channels to configure*/
    ACD_PRESCALER_t prescaler;                        /*!< Specifies the ADC clock prescaler value
                                                    *this parameter can be a value of @ref ACD_PRESCALER_t */
} ADC_InitTypeDef;

/**
  * @brief  ADC interrupt types definition
  */
typedef struct
{
    // uint8 ADC_ChannelUsed[16];                                  /*!< Specifies the ADC channel used and its order according to its index  
    //                                                 *this parameter can be a value of range 1 to 16*/  

    // uint8 ADC_ChannelSamplingTime[16];                                  /*!< Specifies the ADC channel sampling time value .
    //                                                             * index number represent the channel number  
    //                                                 *this parameter can be a value of range 1 to 16*/  
    // uint8 ADC_ChannelsNum;                           /*!< Specifies the number of the distinct channels  
    //                                                 *this parameter can be a value of range 1 to 16*/
                                                   
    uint8 ADC_ScanModeConversionsNum;                           /*!< Specifies the ADC conversions number  
                                                    *this parameter can be a value of range 1 to 16*/
    ADC_Trigger_t   ADC_Triggertype;                            /*!< Specifies the ADC trigger type 
                                                    *this parameter can be a value of @ref ADC_Trigger_t*/
} ADC_GroupTypeDef;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* @brief           : initialize ADC  
* @param       :   pInitConfig  pointer to ADC initalization configurations @ref ADC_InitTypeDef                                                                        
* @retval          : void
*******************************************************************************/
void MADC_VoidInit(const ADC_InitTypeDef* pInitConfig) ;

/******************************************************************************
* @brief           : Configure and start the conversion on the regular channels  
* @param (in)      : @ref ADC_Triggertype  ADC_Triggertype Specifies the ADC trigger type.                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidStartConversion(ADC_Trigger_t ADC_Triggertype);

/******************************************************************************
* @brief           : Configure the conversion on the regular channel  
* @param (in)      : @ref Channels_t u8ChannelNumber  channel number to configure and start conversion.
* @param (in)      : @ref samplingTime_t u8sampplingTime  channel number to configure and start conversion.
* @param (in)      : u8Rank rank (order) of the channel conversion in regular group value from 0 -16
* @retval          : void
*******************************************************************************/
void MADC_VoidConfigureChannel(uint8 u8ChannelNumber,uint8 u8samplingTime,uint8 u8Rank);

/******************************************************************************
* @brief           : Stop the conversion on the regular channels  
* @param (in)      : void                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidStopConversion(void) ;

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

/******************************************************************************
* @brief           : Polling on EOC to read the conversion Data on the regular channels  
* @param (in)      : void                                                                         
* @retval          : void
*******************************************************************************/
void MADC_VoidPollOnConversion(void) ;

/******************************************************************************
* @brief           : Read the conversion Data on the regular channels  
* @param (in)      : void                                                                         
* @retval          : uint16 Data Read from Regular Data register (12bit resoultion)
*******************************************************************************/
uint16 MADC_VoidGetConversionData(void) ;


#endif
