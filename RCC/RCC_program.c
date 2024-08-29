/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_program.c
 *       Module:  RCC Module
 *  Description:  implementaion C file for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
//#include "../../LIB//Std_Types.h"
//#include "../../LIB//Bit_Math.h"
//
//#include "RCC_private.h"
//#include "RCC_config.h"
#include "RCC_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTION
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
void MRCC_voidInitSysClock(const RCC_initConfig_t* pInitConfig)
{
	/*AHB prescaler facor 1,2 ... ,512*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<4));//clear this section
	RCC->CFGR |= (pInitConfig->HPRE<<4);
	/*APB1 prescaler facor 1,2 ... ,16*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<8));//clear this section
	RCC->CFGR |= (pInitConfig->PPRE1<<8);
	/*APB2 prescaler facor 1,2 ... ,16*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<11));//clear this section
	RCC->CFGR |= (pInitConfig->PPRE2<<11);
	
	/*USB prescaler facor /1.5 ,/1*/
	if(pInitConfig->USBPRE==USBPRE_PLL_clock)
	{
		SET_BIT(RCC->CFGR,22);
	}
	else if(pInitConfig->USBPRE==USBPRE_PLL_clock_1_5)
	{
		CLEAR_BIT(RCC->CFGR,22);
	}
	else{
		
	}
	
	/*PLLXTPRE HSE or HSE/2*/
	if(pInitConfig->PLLXTPRE==PLLXTPRE_HSE_clock_divided_2)
	{
		SET_BIT(RCC->CFGR,17);
	}
	else if(pInitConfig->PLLXTPRE==PLLXTPRE_HSE_clock)
	{
		CLEAR_BIT(RCC->CFGR,17);
	}
	else{}
	
	/*ADC prescaler facor 1,2 ... ,8*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<14));//clear this section
	RCC->CFGR |= (pInitConfig->ADCPRE<<14);
	 
	if(pInitConfig->RCC_CLK_Type == RCC_HSE_CRYSTAL)      /* More accurate 4-16 MHZ OSC*/
	{
		/* Enable HSE with no bypass  HSE_ON = 1 */
		SET_BIT(RCC->CR ,16);
		CLEAR_BIT(RCC->CR,18);
		/* HSE selected as system clock*/
		SET_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
	}
	else if(pInitConfig->RCC_CLK_Type == RCC_HSE_RC) /* External clock source (user clock source)*/
	{
		/* Enable HSE with bypass HSE_ON = 1 , HSE_BYP = 1  */
		SET_BIT(RCC->CR ,16);
		SET_BIT(RCC->CR,18);
		/* HSE selected as system clock*/
		SET_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
	}
	else if(pInitConfig->RCC_CLK_Type== RCC_HSI)/*8 MHZ*/
	{	
		/* Enable HSI + Trimming(default) = 0 */
		SET_BIT(RCC->CR ,0);
		/* HSI selected as system clock*/
		CLEAR_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
	}
	else if(pInitConfig->RCC_CLK_Type== RCC_PLL)
	{
		/*PLLMUX  facor 1,2 ... ,16*/
		RCC->CFGR = RCC->CFGR & (~(0b111<<18));//clear this section
		RCC->CFGR |= (pInitConfig->PLLMUL<<18);
		
		if(pInitConfig->PLLSRC_CLK==HSI_CLK_DIV_2)
		{	
			/*HSI*/
			SET_BIT(RCC->CR ,0);
			/*PLL as system clock + HSI*/
			CLEAR_BIT(RCC->CFGR , SW0);
			SET_BIT(RCC->CFGR , SW1);
			CLEAR_BIT(RCC->CFGR , PLLSRC);
			/*Enable PLL*/
			SET_BIT(RCC->CR , PLL_ON);
		}
		else if(pInitConfig->PLLSRC_CLK==HSE_CLK)
		{
			/*HSE*/
			SET_BIT(RCC->CR ,16);
			/*PLL as system clock + HSE*/
			CLEAR_BIT(RCC->CFGR , SW0);
			SET_BIT(RCC->CFGR , SW1);
			SET_BIT(RCC->CFGR , PLLSRC);
			/*Enable PLL*/
			SET_BIT(RCC->CR , PLL_ON);
		}
	}
	else{}
		
}

/******************************************************************************
* \Syntax          : void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Enable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidEnableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId)
{
	/*check input validation (32 bits)*/
	if (Copy_uint8PeripheralId <= 31)     
	{
		switch (Copy_uint8BusId)
		{
			case RCC_AHB : SET_BIT(RCC->AHBENR  , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB1 : SET_BIT(RCC->APB1ENR , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB2 : SET_BIT(RCC->APB2ENR , Copy_uint8PeripheralId);   
			break;
		}
	}

}

/******************************************************************************
* \Syntax          : void MRCC_voidDisableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Disable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidDisableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId)
{
	/*check input validation (32 bits)*/
	if (Copy_uint8PeripheralId <= 31)
	{
		switch (Copy_uint8BusId)
		{
			case RCC_AHB : CLEAR_BIT(RCC->AHBENR  , Copy_uint8PeripheralId);   
			break;
			
			
			case RCC_APB1 : CLEAR_BIT(RCC->APB1ENR , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB2 : CLEAR_BIT(RCC->APB2ENR , Copy_uint8PeripheralId);   
			break;
		}
	}

}


/**
 * @brief function to configure ADC prescaler
 * @param (in): ADC prescaler value
 * @retval: void
 */
void MRCC_VoidSetADCPrescaler(uint8 ADCPRE)
{
	/*ADC prescaler facor 1,2 ... ,8*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<14));//clear this section
	RCC->CFGR |= (ADCPRE<<14);
		
}