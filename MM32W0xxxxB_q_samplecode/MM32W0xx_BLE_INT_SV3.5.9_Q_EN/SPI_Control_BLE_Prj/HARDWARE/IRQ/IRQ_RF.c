#include "irq_rf.h"
#include "mg_api.h"

unsigned char pld_adv[] =
{
  0x02,  0x01, 0x06,
  0x09,  0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xA7, 0xF9,
  0x05,  0x03, 0xE7, 0xFE, 0xE0, 0xFE,
  0x06,  0x09, 0x4C, 0x53, 0x4C, 0x45, 0x44,
};

/********************************************************************************************************
**function: IRQ_RF
**@brief    This function is the IRQ initialization function.  Configure Clock GPIO and NVIC in this function.
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void IRQ_RF(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  //IRQ - pb1
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //Pull-up input
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  SYSCFG_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  PWR->CR = PWR->CR & 0xfffd; //PDDS = 0;enter stop mode
  SCB->SCR |= 0x4;
}

/********************************************************************************************************
**function: IsIrqEnabled
**@brief    This function is used to determine whether a Bluetooth interrupt is generated
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
char IsIrqEnabled(void) //porting api
{
  return (!(GPIO_ReadInputData(GPIOB) & 0x02));
}

/********************************************************************************************************
**function: EXTI0_1_IRQHandler
**@brief    Bluetooth interrupt handler
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void EXTI0_1_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line1);
  ble_run(0);
}

