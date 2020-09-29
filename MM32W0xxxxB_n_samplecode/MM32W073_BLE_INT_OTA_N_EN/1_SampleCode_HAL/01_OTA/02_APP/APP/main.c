#include "sys.h"
#include "mg_api.h"
#include "delay.h"
#include "app.h"
#include "rcc.h"
#include "callback.h"
#include "uart.h"
#include "spi.h"
#include "irq_rf.h"
#include "led_mesh.h"
#include "iwdg.h"
#include "HAL_conf.h"

unsigned char *ble_mac_addr;
extern unsigned char SleepStop;
extern volatile unsigned int SysTick_Count;
unsigned char *get_local_addr(void) //used for ble pairing case
{
  return ble_mac_addr;
}

void TIM3_PWM_Init(u16 arr, u16 psc);
extern void  get_DEVINCEINFO(void);
u8 Value_t[2];

void LED_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB , ENABLE);	 //使能PA,PC端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //LD2-->PA.8 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
		GPIO_ResetBits(GPIOB, GPIO_Pin_3);

}


int main(void)
{
  unsigned long temp = 0x800000;
  unsigned long i = 0;
	unsigned char *ft_val = (unsigned char *)(0x1FFFF804);
	unsigned char ft_value[2] = {0xc0, 0x12};
  while (temp--);
	CodeNvcRemap();
  SystemClk_HSEInit();
#ifdef USE_UART
#ifdef USE_AT_CMD
  SleepStop = 0x00;
#endif
#endif

#ifdef USE_UART
  uart_initwBaudRate();
#endif

  SysTick_Configuration();
  Write_Iwdg_ON(IWDG_Prescaler_32, 0x4E2); //1s
  SPIM_Init(SPI2,/*0x06*/0x06); //6Mhz
  IRQ_RF();
  SetBleIntRunningMode();
  radio_initBle(TXPWR_0DBM, &ble_mac_addr);
	LED_Init();
  SysTick_Count = 0;
  while (SysTick_Count < 5) {}; //delay at least 5ms between radio_initBle() and ble_run...
	if((*ft_val > 11) && (*ft_val < 27)){
			ft_value[1] = *ft_val;
			mg_activate(0x53);
			mg_writeBuf(0x4, ft_value, 2);
			mg_activate(0x56);
	}

  ble_run_interrupt_start(160 * 2); //320*0.625=200 ms
  while (1)
  {
    /*************do sometging and sleep****************/
    Delay_ms(50);
    IrqMcuGotoSleepAndWakeup();
  }
}

