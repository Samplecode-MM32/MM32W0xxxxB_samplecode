/**
******************************************************************************
* @file  HAL_flash.c
* @author  AE team
* @version  V1.5.0
* @date  21/10/2016
* @brief  This file provides all the FLASH firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 MindMotion</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_flash.h"
#include "HAL_memprotect.h"
/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup FLASH
* @brief FLASH driver modules
* @{
*/

/** @defgroup FLASH_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup FLASH_Private_Defines
* @{
*/

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask         ((uint32_t)0x00000038)
#define ACR_HLFCYA_Mask          ((uint32_t)0xFFFFFFF7)
#define ACR_PRFTBE_Mask          ((uint32_t)0xFFFFFFEF)

/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask          ((uint32_t)0x00000020)

/* Flash Control Register bits */
#define CR_PG_Set                ((uint32_t)0x00000001)
#define CR_PG_Reset              ((uint32_t)0x00001FFE)
#define CR_PER_Set               ((uint32_t)0x00000002)
#define CR_PER_Reset             ((uint32_t)0x00001FFD)
#define CR_MER_Set               ((uint32_t)0x00000004)
#define CR_MER_Reset             ((uint32_t)0x00001FFB)
#define CR_OPTPG_Set             ((uint32_t)0x00000010)
#define CR_OPTPG_Reset           ((uint32_t)0x00001FEF)
#define CR_OPTER_Set             ((uint32_t)0x00000020)
#define CR_OPTER_Reset           ((uint32_t)0x00001FDF)
#define CR_STRT_Set              ((uint32_t)0x00000040)
#define CR_LOCK_Set              ((uint32_t)0x00000080)

/* FLASH Mask */
#define RDPRT_Mask               ((uint32_t)0x00000002)
#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

/* Delay definition */
#define EraseTimeout             ((uint32_t)0x00000FFF)
#define ProgramTimeout           ((uint32_t)0x0000000F)

/**
* @}
*/

/** @defgroup FLASH_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup FLASH_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup FLASH_Private_FunctionPrototypes
* @{
*/


/**
* @}
*/

/** @defgroup FLASH_Private_Functions
* @{
*/



/**
  * @brief  Erases the FLASH option bytes.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY,
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseSysSpace(void)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE) {
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        FLASH->ACR |= (0xcc103 << 12) | (1 << 11);
        FLASH->CR |= (0xA5BA << 16);
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= CR_OPTER_Set;
        FLASH->AR = 0x1ffff400;
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if(status == FLASH_COMPLETE) {
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= CR_OPTER_Reset;
        } else {
            if (status != FLASH_BUSY) {
                /* Disable the OPTPG Bit */
                FLASH->CR &= CR_OPTPG_Reset;
            }
        }
        FLASH->CR &= 0xFFFF;
        FLASH->ACR &= 0x03FF;
    }
    /* Return the erase status */
    return status;
}
/**
  * @brief  Erases the FLASH option bytes.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY,
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseSecSpace(uint32_t Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE) {
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= CR_OPTER_Set;
        FLASH->AR = Address;
        FLASH->CR |= CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if(status == FLASH_COMPLETE) {
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= CR_OPTER_Reset;
        } else {
            if (status != FLASH_BUSY) {
                /* Disable the OPTPG Bit */
                FLASH->CR &= CR_OPTPG_Reset;
            }
        }
    }
    /* Return the erase status */
    return status;
}
/**
  * @brief  Erases all FLASH pages.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY,
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
  *   FLASH_TIMEOUT.
  */
void FLASH_EraseProSpaceSramMdoe(void)
{
    FLASH_Unlock();

    FLASH_EraseAllPages();
    FLASH_EraseSecSpace(0x1FFE0000);
}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @param Address: specifies the address to be programmed.
  *   This parameter can be 0x1FFFF804 or 0x1FFFF806.
  * @param Data: specifies the data to be programmed.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY,
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramSysSecProByteData(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_OB_DATA_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status == FLASH_COMPLETE) {
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
//    *(u32*)(0x40022040)=0xffffffff;
//    *(u32*)(0x40022044)=0xffffffff;
        /* Enables the Option Bytes Programming operation */
        FLASH->CR |= CR_OPTPG_Set;
        *(__IO uint16_t*)Address = Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status != FLASH_BUSY) {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }
    /* Return the Option Byte Data Program Status */
    return status;
}

/**
* @brief  Program flash space half data.
* @param  Address,flash system?¡éuser?¡éprotect space address
* @param  Data
* @retval :FLASH Status: The returned value can be: FLASH_BUSY,
*   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*   FLASH_TIMEOUT.
*/
FLASH_Status FLASH_ProgramOptionHalfData(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_OB_DATA_ADDRESS(Address));
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status == FLASH_COMPLETE) {
        FLASH->AR = Address;
        /* Authorize the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* Enables the Option Bytes Programming operation */
        FLASH->CR |= CR_OPTPG_Set;
        *(__IO uint16_t*)Address = Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status != FLASH_BUSY) {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= CR_OPTPG_Reset;
        }
    }
    /* Return the Option Byte Data Program Status */
    return status;
}

/*-------------------------(C) COPYRIGHT 2016 MindMotion ----------------------*/
