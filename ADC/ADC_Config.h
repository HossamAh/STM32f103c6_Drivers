/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  CAN_config.h
 *  module:  CAN Module
 *  @details:  Configuration header file for CAN Driver
*********************************************************************************************************************/
#ifndef _CAN_CONFIG_H
#define _CAN_CONFIG_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
/******** BoudRate value rating to table at web site {http://www.bittiming.can-wiki.info/}
 * 1. select ST Microelectronics bxCAN
 * 2. put freq with 8Mhz (APB1 freq)
 * 3. click Request Table						        ***********************************/
// CAN_BitTimingConfig CAN_bitRateConfig[7] = {{2, 13, 10}, {2, 13, 5}, {2, 13, 4}, {2, 13, 2}, {2, 13, 1},{1, 8, 1}, {1, 6, 1}};







#endif
