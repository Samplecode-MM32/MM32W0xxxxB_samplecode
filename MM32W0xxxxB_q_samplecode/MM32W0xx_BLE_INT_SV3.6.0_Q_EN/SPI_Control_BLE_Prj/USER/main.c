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
//#include "usb.h"

unsigned char *ble_mac_addr;
extern unsigned char SleepStop;
extern void IrqMcuGotoSleepAndWakeup(void)  ;

unsigned char *get_local_addr(void) //used for ble pairing case
{
  return ble_mac_addr;
}
GPIO_InitTypeDef  GPIO_InitStructure;

int main(void)
{
  unsigned long temp = 0x800000;
	unsigned char *ft_val = (unsigned char *)(0x1FFFF804);
	unsigned char ft_value[2] = {0xc0, 0x12};
	
  u8 value_t[2];
  SysTick_Configuration();

#ifdef USE_UART
#ifdef USE_AT_CMD
  SleepStop = 0x00;
#endif
#endif

#ifdef USE_UART
  uart_initwBaudRate();
#endif

  SPIM_Init(SPI2,/*0x06*/0x06); //6Mhz
  IRQ_RF();
  while (temp--);
  SetBleIntRunningMode();
  radio_initBle(TXPWR_0DBM, &ble_mac_addr);
  printf("\r\nMAC:%02x-%02x-%02x-%02x-%02x-%02x\r\n", ble_mac_addr[5], ble_mac_addr[4], ble_mac_addr[3], ble_mac_addr[2], ble_mac_addr[1], ble_mac_addr[0]);

	if((*ft_val > 11) && (*ft_val < 27))
		{
			ft_value[1] = *ft_val;
			mg_activate(0x53);
			mg_writeBuf(0x4, ft_value, 2);
			mg_activate(0x56);
		}

  ble_run_interrupt_start(160 * 2); //320*0.625=200 ms
  while (1)
  {

  }
}

