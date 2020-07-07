#include "irq_rf.h"
#include "mg_api.h"

extern unsigned char SleepStop;
extern unsigned char SleepStatus;

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
  //IRQ - pb8
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
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
  return (!(GPIO_ReadInputData(GPIOB) & 0x002));
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
  if (2 == SleepStatus) //stop
  {
    RCC->CR |= RCC_CR_HSION;
    RCC->CR |= RCC_CR_PLLON;
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
    SysTick_Config(48000);
  }
  SleepStatus = 0;
  ble_run(0);
}

