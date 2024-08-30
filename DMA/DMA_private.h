/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  DMA_private.h
 *  module:  DMA Module
 *  @details:  private header file for DMA Driver
*********************************************************************************************************************/
#ifndef _DMA_PRIVATE_H
#define _DMA_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/** @brief CCRx_Reg_t DMA channel configuration register */
typedef union
{
    uint32 r;
    struct CCRx_Reg_TAG
    {
        uint32 EN                    :1;
        uint32 TCIE                  :1;
        uint32 HTIE                  :1;
        uint32 TEIE                  :1;
        uint32 DIR                   :1;
        uint32 CIRC                  :1;
        uint32 PINC                  :1;
        uint32 MINC                  :1;
        uint32 PSIZE                 :2;
        uint32 MSIZE                 :2;
        uint32 PL                    :2;
        uint32 MEM2MEM               :1;
        uint32                       :17;
    }B;
}CCRx_Reg_t;

/** @brief CNDTR_Reg_t DMA channel number of data register */
typedef union
{
    uint32 r;
    struct CNDTR_Reg_TAG
    {
        uint32 NDT                   :16;
        uint32                       :16;
    }B;
}CNDTR_Reg_t;

/** @brief DMA_Channel_t DMA Channel registers */
typedef struct
{
    CCRx_Reg_t CCRx;
    CNDTR_Reg_t CNDTRx;
    uint32 CPARx;
    uint32 CMARx;
    uint32 reserved;
}DMA_Channel_t;


/** @brief DMA_t DMA DMA registers */
typedef struct
{
    uint32 ISR;
    uint32 IFCR;
    DMA_Channel_t CHx[7];
}DMA_t;

/*******************************TX Mailbox Registers********************************************** */


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	DMA_Base_Address        0x40020000          // Base address of DMA1

#define 	DMA 		((volatile DMA_t *) DMA_Base_Address)

#endif