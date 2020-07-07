#include "HAL_device.h"
#include "HAL_conf.h"
#include "rcc.h"
#include "sys.h"

/********************************************************************************************************
 **function: SetSysClock_HSI
 **@brief    This function sets the HSI clock to 48Mhz
 **
 **@param   	None.
 **
 **@return   None.
 ********************************************************************************************************/
#if 1//using internal RC as clock ref
void SetSysClock_HSI() {
	unsigned char temp = 0;
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY))
		;
	RCC->CR &= ~(1 << 20);
	RCC->CR &= ~(1 << 2);
	RCC->CFGR = RCC_CFGR_PPRE1_2;
	FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;
	RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;
	/* PCLK2 = HCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV1;
	/* PCLK1 = HCLK */
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= 0x02;
	while (temp != 0x02) {
		temp = RCC->CFGR >> 2;
		temp &= 0x03;
	}
}
#endif
/********************************************************************************************************
 **function: SysClk8to48
 **@brief    This function sets the HSI clock from 8MHZ to 48MHZ.Turn off low power mode.
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void SysClk8to48(void) //////DO NOT REMOVE, used in ble lib//////
{

	unsigned char temp = 0;
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY))
		;
	RCC->CR &= ~(1 << 20);
	RCC->CR &= ~(1 << 2);
	RCC->CFGR = RCC_CFGR_PPRE1_2;
	FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;
	RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV1;
	RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= 0x02;
	while (temp != 0x02) {
		temp = RCC->CFGR >> 2;
		temp &= 0x03;
	}
}
/********************************************************************************************************
 **function: SysClk48to8
 **@brief    This function sets the HSI clock from 48MHZ to 8MHZ.Turn on low power mode.
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void SysClk48to8(void) {
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI); //selecting PLL clock as sys clock
	while (RCC_GetSYSCLKSource() != 0x0) {
	}
	RCC->CR &= ~(RCC_CR_PLLON);   //clear PLL
	SysTick_Config(8000);
}

