#include "callback.h"
#include "app.h"
#include "rcc.h"
#include "mg_api.h"
#include "uart.h"
#include "delay.h"
///////////////FIFO proc for AT cmd///////////////
#define TO_HIGH_CASE
#define comrxbuf_wr_pos RxCont
u16 comrxbuf_rd_pos = 0; //init, com rx buffer
#define MAX_AT_CMD_BUF_SIZE 52
u8 AtCmdBuf[MAX_AT_CMD_BUF_SIZE], AtCmdBufDataSize = 0;
#define MAX_SIZE 100
u8 txBuf[MAX_SIZE], rxBuf[MAX_SIZE], txLen = 0;
u16 RxCont = 0;
//u16 PosR = 0;
u8 PosW = 0;
extern unsigned char WaitSetBaud;
u32 tempI2cData = 0x32;
unsigned int TxTimeout;
extern unsigned int SysTick_Count;
extern u32 BaudRate;
unsigned char SleepStop = 0x00;
unsigned char SleepStatus = 0;
unsigned int RxTimeout;
extern char GetConnectedStatus(void);
extern void CheckAtCmdInfo(void);
extern void ChangeBaudRate(void);
extern void moduleOutData(u8 *data, u8 len);

/********************************************************************************************************
 **function: McuGotoSleepAndWakeup
 **@brief    This function is the MCU auto goto sleep AND wakeup, porting api
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void McuGotoSleepAndWakeup(void) // auto goto sleep AND wakeup, porting api
{

	if ((SleepStop) && (TxTimeout < SysTick_Count)
			&& (RxTimeout < SysTick_Count)) {
		if (SleepStop == 1)  //sleep
				{
			SCB->SCR &= 0xfb;
			__WFE();
		} else     //stop
		{
			//SysClk48to8();
			SCB->SCR |= 0x4;
			__WFI();
			RCC->CR |= RCC_CR_HSION;
			//SysClk8to48();
		}
	}
}

/********************************************************************************************************
 **function: SysClk8M
 **@brief    Set the system clock, porting api
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void SysClk8M(void) {
	__ASM volatile("cpsid i");
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);   //selecting PLL clock as sys clock
	while (RCC_GetSYSCLKSource() != 0x0) {
	}
	RCC->CR &= ~(RCC_CR_PLLON); //clear PLL
	SysTick_Config(8000);
	__ASM volatile("cpsie i");
}

/********************************************************************************************************
 **function: IrqMcuGotoSleepAndWakeup
 **@brief    This function is the MCU auto goto sleep AND wakeup, porting api. This function is used in interrupt mode
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void IrqMcuGotoSleepAndWakeup(void) // auto goto sleep AND wakeup, porting api
{
	if (ble_run_interrupt_McuCanSleep() == 0)
		return;

#ifdef USE_UART
  if ((SleepStop) &&
      (TxTimeout < SysTick_Count) &&
      (RxTimeout < SysTick_Count))
  {
    if (SleepStop == 1)  //sleep
    {
      SleepStatus = 1;
      SCB->SCR &= 0xfb;
      __WFE();
    }
    else     //stop
    {
      SleepStatus = 2;
      //SysClk8M();
      SCB->SCR |= 0x4;
      SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
      RCC->CR |=  0X1 << 19;
      RCC->CR |=  0X1 << 19;
      RCC->CR |=  0X1 << 19;
      delay_us(5);
      __WFI();
    }
  }
#endif
}
void NMI_Handler(void) {
	RCC->CIR |= 0x1 << 23;
}

static char dis_int_count = 0;
/********************************************************************************************************
 **function: DisableEnvINT
 **@brief    Turn off Bluetooth interrupt.This function is used in the process of BLE processing data.
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void DisableEnvINT(void) {
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	//to disable int
	__ASM volatile("cpsid i");
	dis_int_count++;
}

/********************************************************************************************************
 **function: EnableEnvINT
 **@brief    Turn on Bluetooth interrupt.This function is used to open the interrupt after
 **          the BLE processing data is completed.
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void EnableEnvINT(void) {
	//to enable/recover int
	dis_int_count--;
	if (dis_int_count <= 0) //protection purpose
			{
		dis_int_count = 0; //reset
		__ASM volatile("cpsie i");
	}
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

/********************************************************************************************************
 **function: CheckComPortInData
 **@brief    This function is used to pass data through Bluetooth.
 **
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void CheckComPortInData(void) //at cmd NOT supported
{
	u16 send;

	if (comrxbuf_wr_pos != comrxbuf_rd_pos) //not empty
			{
		if (!GetConnectedStatus()) {
			comrxbuf_rd_pos = comrxbuf_wr_pos; //empty the buffer if any
		} else //connected
		{
			if (comrxbuf_wr_pos > comrxbuf_rd_pos) {
				send = sconn_notifydata(rxBuf + comrxbuf_rd_pos,
						comrxbuf_wr_pos - comrxbuf_rd_pos);
				comrxbuf_rd_pos += send;
			} else {
				send = sconn_notifydata(rxBuf + comrxbuf_rd_pos,
						MAX_SIZE - comrxbuf_rd_pos);
				comrxbuf_rd_pos += send;
				comrxbuf_rd_pos %= MAX_SIZE;
			}
		}
	}
}

/********************************************************************************************************
 **function: UsrProcCallback
 **@brief    This function is a callback function. This function will be called
 **          every time a Bluetooth interrupt is entered.
 **          and the data is processed in this function. You can do something in this function
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void UsrProcCallback(void) //porting api
{
	//moduleOutData("mm32init_cbk",12);//test2020/4/28
#ifdef USE_AT_CMD
  CheckAtCmdInfo();//AT CMD not supported
#else
	CheckComPortInData();
#endif
	if ((2 != SleepStop) || (!(GPIO_ReadInputData(GPIOB) & 0x40))) //CTL low
			{
		if ((txLen) && (0 == PosW)) {
			UART_ITConfig(UART2, UART_IT_TXIEN, ENABLE);
			UART_SendData(UART2, txBuf[PosW++]);

			TxTimeout = SysTick_Count + (20000 / BaudRate);
		}
	}
	if ((SleepStop == 2) && (RxTimeout < SysTick_Count)) {
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		RxTimeout = SysTick_Count + (20000 / BaudRate);
	}

#ifdef USE_AT_CMD
  if (WaitSetBaud)
  {
    WaitSetBaud++;

    if (WaitSetBaud > 2)
    {
      ChangeBaudRate();
      WaitSetBaud = 0;
      moduleOutData((u8 *)"IND:OK\n", 7);
    }
  }
#endif
//  master_mac= GetMasterDeviceMac(Mac_Type);
}

