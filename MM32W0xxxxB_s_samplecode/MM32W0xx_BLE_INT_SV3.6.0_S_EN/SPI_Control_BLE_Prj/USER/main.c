#include "sys.h"
#include "mg_api.h"
#include "delay.h"
#include "app.h"
#include "rcc.h"
#include "callback.h"
#include "uart.h"
#include "spi.h"
#include "iic.h"
#include "irq_rf.h"
#include "led_mesh.h"
#include "iwdg.h"

unsigned char *ble_mac_addr;
extern unsigned char SleepStop;
extern volatile unsigned int SysTick_Count;
u8 value_t[2];
unsigned char *get_local_addr(void) //used for ble pairing case
{
  return ble_mac_addr;
}
void TIM3_PWM_Init(u16 arr, u16 psc);

int main(void)
{
  unsigned long temp = 0x800000;
  unsigned long i = 0;
	unsigned char *ft_val = (unsigned char *)(0x1FFFF804);
	unsigned char ft_value[2] = {0xc0, 0x12};
  while (temp--);
  SystemClk_HSEInit();
  SleepStop = 0x01;
#ifdef USE_UART
#ifdef USE_AT_CMD
  SleepStop = 0x00;
#endif
#endif

#ifdef USE_UART
  uart_initwBaudRate();
#endif

#ifdef USE_I2C
  IIC_Init(I2C1);
#endif
  SysTick_Configuration();
  Write_Iwdg_ON(IWDG_Prescaler_32, 0x4E2); //1s
  SPIM_Init(SPI2,/*0x06*/0x06); //6Mhz
  IRQ_RF();
  SetBleIntRunningMode();
  radio_standby();
  radio_initBle(TXPWR_0DBM, &ble_mac_addr);
  SysTick_Count = 0;
  while (SysTick_Count < 5) {}; //delay at least 5ms between radio_initBle() and ble_run...
  printf("\r\nMAC:%02x-%02x-%02x-%02x-%02x-%02x\r\n", ble_mac_addr[5], ble_mac_addr[4], ble_mac_addr[3], ble_mac_addr[2], ble_mac_addr[1], ble_mac_addr[0]);

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
    delay_ms(50);
    IrqMcuGotoSleepAndWakeup();
  }
}

