/*********************************************************************************
* @author    : Hossam Ahmed                                                     
* @version   : V01                                                               
* @date      : 20 Aug 2024                                                       
/*********************************************************************************/
/*******************************************************************************************************************
 *  *  FILE DESCRIPTION
 *  --------------------
 *  @file:  CAN_private.h
 *  module:  CAN Module
 *  @details:  private header file for CAN Driver
*********************************************************************************************************************/
#ifndef _ADC_PRIVATE_H
#define _ADC_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/** @brief SR_Reg_t ADC status register */
typedef union
{
    uint32 r;
    struct SR_Reg_TAG
    {
        uint32 AWD  :1;
        uint32 EOC  :1;
        uint32 jJEOC:1;
        uint32 JSTRT:1;
        uint32 STRT :1;
        uint32      :27;
    }B;
}SR_Reg_t;

/** @brief CR1_Reg_t ADC control 1 register */
typedef union
{
    uint32 r;
    struct CR1_Reg_TAG
    {
        uint32 AWDCH            :5;
        uint32 EOCIE            :1;
        uint32 AWDIE            :1;
        uint32 JEOCIE           :1;
        uint32 SCAN             :1;
        uint32 AWDSGL           :1;
        uint32 JAUTO            :1;
        uint32 DISCEN           :1;
        uint32 JDISCEN          :1;
        uint32 DISCNUM          :3;
        uint32 DUALMOD          :4;
        uint32                  :2;
        uint32 JAWDEN           :1;
        uint32 AWDEN            :1;
        uint32                  :8;
    }B;
}CR1_Reg_t;

/** @brief CR2_Reg_t ADC control 2 register */
typedef union
{
    uint32 r;
    struct CR2_Reg_TAG
    {
        uint32 ADON             :1;
        uint32 CONT             :1;
        uint32 CAL              :1;
        uint32 RSTCAL           :1;
        uint32                  :4;
        uint32 DMA              :1;
        uint32                  :2;
        uint32 ALIGN            :1;
        uint32 JEXTSEL          :3;
        uint32 JEXTTRIG         :1;
        uint32                  :1;
        uint32 EXTSEL           :3;
        uint32 EXTTRIG          :1;
        uint32 JSWSTAR          :1;
        uint32 SWSTART          :1;
        uint32 TSVREFE          :1;
        uint32                  :8;
    }B;
}CR2_Reg_t;

/** @brief JOFR_Reg_t ADC injected channel data offset register */
typedef union
{
    uint32 r;
    struct JOFR_Reg_TAG
    {
        uint32 JOFFSET             :12;
        uint32                     :20;
    }B;
}JOFR_Reg_t;

/** @brief SQR1_Reg_t ADC regular channels sequence register */
typedef union
{
    uint32 r;
    struct SQR1_Reg_TAG
    {
        uint32 SQ13                :5;
        uint32 SQ14                :5;
        uint32 SQ15                :5;
        uint32 SQ16                :5;
        uint32 L                   :4;
        uint32                     :8;
    }B;
}SQR1_Reg_t;

/** @brief SQR2_3_Reg_t ADC regular channels sequence register */
typedef union
{
    uint32 r;
    struct SQR2_3_Reg_TAG
    {
        uint32 SQ1                :5;
        uint32 SQ2                :5;
        uint32 SQ3                :5;
        uint32 SQ4                :5;
        uint32 SQ5                :5;
        uint32 SQ6                :5;
        uint32                    :2;
    }B;
}SQR2_3_Reg_t;

/** @brief JSQR_Reg_t ADC injected channels sequence register */
typedef union
{
    uint32 r;
    struct JSQR_Reg_TAG
    {
        uint32 JSQ1                :5;
        uint32 JSQ2                :5;
        uint32 JSQ3                :5;
        uint32 JSQ4                :5;
        uint32 L                   :2;
        uint32                     :10;
    }B;
}JSQR_Reg_t;
/** @brief JDR_Reg_t ADC injected channel data  register */
typedef union
{
    uint32 r;
    struct JDR_Reg_TAG
    {
        uint32 JDATA               :16;
        uint32                     :16;
    }B;
}JDR_Reg_t;

/** @brief DR_Reg_t ADC regular channel data  register */
typedef union
{
    uint32 r;
    struct DR_Reg_TAG
    {
        uint32 REGULARDATA         :16;
        uint32 ADC2DATA            :16;
    }B;
}DR_Reg_t;


/** @brief ADC_t ADC ADC registers */
typedef struct
{
    SR_Reg_t    SR;
    CR1_Reg_t   CR1;
    CR2_Reg_t   CR2;
    uint32      SMPR1;
    uint32      SMPR2;
    JOFR_Reg_t  JOFR[4];
    uint32      HTR;
    uint32      LTR;
    SQR1_Reg_t   SQR1;
    SQR2_3_Reg_t SQR2;
    SQR2_3_Reg_t SQR3;
    JSQR_Reg_t   JSQR;
    JDR_Reg_t    JDR[4];
    DR_Reg_t     DR;
}ADC_t;

/*******************************TX Mailbox Registers********************************************** */


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	ADC_Base_Address        0x40012400          // Base address of ADC1

#define 	ADC 		((volatile ADC_t *) ADC_Base_Address)

#endif