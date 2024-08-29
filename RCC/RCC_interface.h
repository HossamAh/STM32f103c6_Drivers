/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_interface.h
 *       Module:  RCC Module
 *  Description:  interface funcions for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"

#include "RCC_private.h"
#include "RCC_config.h"



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
/*********** Macros Of :- RCC AHB1 CLK ENABLE ***************/

#define _PERIPHERAL_EN_DMA1EN     0U
#define _PERIPHERAL_EN_DMA2EN     1U
#define _PERIPHERAL_EN_SRAMEN     2U
#define _PERIPHERAL_EN_FLITFEN     4U
#define _PERIPHERAL_EN_CRCEN     6U
#define _PERIPHERAL_EN_FSMCEN     8U
#define _PERIPHERAL_EN_SDIOEN    10U


	/********* Macros Of :- RCC APB1 peripheral clock enable register *********/

#define PERIPHERAL_EN_TIM2						0U
#define PERIPHERAL_EN_TIM3						1U
#define PERIPHERAL_EN_TIM4						2U
#define PERIPHERAL_EN_TIM5					    3U
#define PERIPHERAL_EN_TIM6						4U
#define PERIPHERAL_EN_TIM7						5U
#define PERIPHERAL_EN_TIM12					    6U
#define PERIPHERAL_EN_TIM13					    7U
#define PERIPHERAL_EN_TIM14					    8U
#define PERIPHERAL_EN_WWDG						11U
#define PERIPHERAL_EN_SPI2						14U
#define PERIPHERAL_EN_SPI3						15U
#define PERIPHERAL_EN_UART2						17U
#define PERIPHERAL_EN_UART3						18U
#define PERIPHERAL_EN_UART4						19U
#define PERIPHERAL_EN_UART5						20U
#define PERIPHERAL_EN_I2C1						21U
#define PERIPHERAL_EN_I2C2						22U
#define PERIPHERAL_EN_USB						23U
#define PERIPHERAL_EN_CAN1						25U
#define PERIPHERAL_EN_BKP						27U
#define PERIPHERAL_EN_PWR						28U
#define PERIPHERAL_EN_DAC						29U



/**********  Macros Of :- RCC APB2 peripheral clock enable register (RCC_APB2ENR) *********/

#define PERIPHERAL_EN_AFIO  				 0U
#define PERIPHERAL_EN_IOPA					 2U
#define PERIPHERAL_EN_IOPB					 3U
#define PERIPHERAL_EN_IOPC					 4U
#define PERIPHERAL_EN_IOPD					 5U
#define PERIPHERAL_EN_IOPE					 6U
#define PERIPHERAL_EN_ADC1					 9U
#define PERIPHERAL_EN_ADC2					 10U
#define PERIPHERAL_EN_TIM1					 11U
#define PERIPHERAL_EN_SPI1					 12U
#define PERIPHERAL_EN_TIM8					 13U
#define PERIPHERAL_EN_USART1				 14U
#define PERIPHERAL_EN_ADC3					 15U
#define PERIPHERAL_EN_TIM9					 19U
#define PERIPHERAL_EN_TIM10					 20U
#define PERIPHERAL_EN_TIM11 				 21U

/*****************************************************************************************/
/** @defgroup  USBPRE*/
#define USBPRE_PLL_clock_1_5 0
#define USBPRE_PLL_clock 1

/** @defgroup  PLLXTPRE*/
#define  PLLXTPRE_HSE_clock 0
#define PLLXTPRE_HSE_clock_divided_2 1

/** @defgroup  ADCPRE*/
#define ADCPRE_PCLK2_2 0
#define ADCPRE_PCLK2_4 1
#define ADCPRE_PCLK2_6 2
#define ADCPRE_PCLK2_8 3

/** @defgroup  PPRE2 (APB2)*/
#define PPRE2_NO_DIV 0x0
#define PPRE2_DIV_2 0x8
#define PPRE2_DIV_4 0x9
#define PPRE2_DIV_8 0xA
#define PPRE2_DIV_16 0xB
#define PPRE2_DIV_32 0xC
#define PPRE2_DIV_64 0xD
#define PPRE2_DIV_128 0xE
#define PPRE2_DIV_512 0xF


/** @defgroup  PPRE1 (APB1)*/
#define PPRE1_NO_DIV 0x0
#define PPRE1_DIV_2 0x4
#define PPRE1_DIV_4 0x5
#define PPRE1_DIV_8 0x6
#define PPRE1_DIV_16 0x7

/** @defgroup  HPRE: (AHB)*/
#define HPRE_NO_DIV 0x0
#define HPRE_DIV_2 0x8
#define HPRE_DIV_4 0x9
#define HPRE_DIV_8 0xA
#define HPRE_DIV_16 0xB
#define HPRE_DIV_32 0xC
#define HPRE_DIV_64 0xD
#define HPRE_DIV_128 0xE
#define HPRE_DIV_512 0xF

/** @defgroup PLLMUL */
#define PLL_input_clock_x_2	1U
#define PLL_input_clock_x_3	2U
#define PLL_input_clock_x_4	3U
#define PLL_input_clock_x_5 4U
#define PLL_input_clock_x_6 5U
#define PLL_input_clock_x_7 6U
#define PLL_input_clock_x_8 7U
#define PLL_input_clock_x_9 8U
#define PLL_input_clock_x_10 9U
#define PLL_input_clock_x_11 10U
#define PLL_input_clock_x_12 11U
#define PLL_input_clock_x_13 12U
#define PLL_input_clock_x_14 13U
#define PLL_input_clock_x_15 14U
#define PLL_input_clock_x_16 15U

/** @defgroup PLLSRC_CLK */
#define HSI_CLK_DIV_2 0
#define HSE_CLK	1


/** @defgroup RCC_CLK_Type */
#define RCC_HSE_CRYSTAL      0
#define RCC_HSE_RC           1
#define RCC_HSI              2
#define RCC_PLL              3

typedef struct
{
	uint8 RCC_CLK_Type;
	uint8 PLLSRC_CLK;
	uint8 PLLMUL;
	uint8 USBPRE;
	uint8 PLLXTPRE;
	uint8 ADCPRE;
	uint8 PPRE2;
	uint8 PPRE1;
	uint8 HPRE;
}RCC_initConfig_t;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void MRCC_voidInitSysClock(void)                                      
* \Description     : initialize RCC using configuration by parsing all 
*       its configurations to the RCC registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pInitConfig configuration parameters                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidInitSysClock(const RCC_initConfig_t* pInitConfig);

/******************************************************************************
* \Syntax          : void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Enable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId);

/******************************************************************************
* \Syntax          : void MRCC_voidDisableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Disable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidDisableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId);

/**
 * @brief function to configure ADC prescaler
 * @param (in): ADC prescaler value
 * @retval: void
 */
void MRCC_VoidSetADCPrescaler(uint8 ADCPRE);

#endif
