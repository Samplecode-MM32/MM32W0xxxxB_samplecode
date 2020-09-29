/******************** (C) COPYRIGHT 2009 MM32 ********************
* File Name          : MM32L073_it.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 06/08/2020
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MM32 SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "MM32W0xx_it.h"
#include "HAL_gpio.h"
#include "boot.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/******************************************************************************/
/*            MM32W0xx Peripherals Interrupt Handlers                        */
/******************************************************************************/



/******************************************************************************
********** 将中断跳转到APP
******************************************************************************/

//void Reset_Handler(void)
//{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+4)); AppEntry();}

void NMI_Handler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+8)); AppEntry();}

void HardFault_Handler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+12)); AppEntry();}

void SVC_Handler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+44)); AppEntry();}

void PendSV_Handler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+56)); AppEntry();}

void SysTick_Handler(void)
{
volatile void (*AppEntry)(void);
AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+60));
AppEntry();
}
	 
void WWDG_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+64)); AppEntry();}

void PVD_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+68)); AppEntry();}

void RTC_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+72)); AppEntry();}

void FLASH_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+76)); AppEntry();}

void RCC_CRS_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+80)); AppEntry();}

void EXTI0_1_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+84)); AppEntry();}

void EXTI2_3_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+88)); AppEntry();}

void EXTI4_15_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+92)); AppEntry();}

void DMA1_Channel1_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+100)); AppEntry();}

void DMA1_Channel2_3_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+104)); AppEntry();}

void DMA1_Channel4_5_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+108)); AppEntry();}

void ADC_COMP_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+112)); AppEntry();}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+116)); AppEntry();}

void TIM1_CC_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+120)); AppEntry();}
	 
void TIM2_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+124)); AppEntry();}

void TIM3_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+128)); AppEntry();}

void TIM14_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+140)); AppEntry();}

void TIM16_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+148)); AppEntry();}

void TIM17_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+152)); AppEntry();}

void I2C1_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+156)); AppEntry();}

void SPI1_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+164)); AppEntry();}

void SPI2_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+168)); AppEntry();}

void UART1_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+172)); AppEntry();}

void UART2_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+176)); AppEntry();}

void AES_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+180)); AppEntry();}

void CAN_IRQHandler(void)
{volatile void (*AppEntry)(void); AppEntry = (volatile void(*)())(*(uint32_t*)(APP_ENTRY_ADDRESS+184)); AppEntry();}




/******************* (C) COPYRIGHT 2009 MM32 *****END OF FILE****/
