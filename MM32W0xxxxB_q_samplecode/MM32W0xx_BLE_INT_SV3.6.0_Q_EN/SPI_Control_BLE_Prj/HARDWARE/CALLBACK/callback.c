#include "callback.h"
#include "app.h"
#include "rcc.h"
#include "mg_api.h"
#include "spi.h"
///////////////FIFO proc for AT cmd///////////////
#define TO_HIGH_CASE
#define comrxbuf_wr_pos RxCont
#define MAX_AT_CMD_BUF_SIZE 52
#define MAX_SIZE 100

u8 AtCmdBuf[MAX_AT_CMD_BUF_SIZE], AtCmdBufDataSize = 0;
u8 txBuf[MAX_SIZE], rxBuf[MAX_SIZE], txLen = 0;
u8 PosW = 0;
u16 RxCont = 0;
u16 comrxbuf_rd_pos = 0; //init, com rx buffer
u32 tempI2cData = 0x32;

unsigned int TxTimeout;
unsigned char SleepStop = 0x00; 
unsigned char SleepStatus = 0;
unsigned int RxTimeout;

extern char GetConnectedStatus(void);
extern void CheckAtCmdInfo(void);
extern void ChangeBaudRate(void);
extern  unsigned int SysTick_Count;
extern u32 BaudRate;
extern unsigned char WaitSetBaud;
extern void moduleOutData(u8 *data, u8 len);

void ALL_IO_AIN(void);

static char dis_int_count = 0;

/********************************************************************************************************
**function: McuGotoSleepAndWakeup
**@brief    This function is the MCU auto goto sleep AND wakeup, porting api
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void McuGotoSleepAndWakeup(void)
{
  if ((SleepStop) &&
      (TxTimeout < SysTick_Count) &&
      (RxTimeout < SysTick_Count))
  {
    if (SleepStop == 1)
    {
      SCB->SCR &= 0xfb;
      __WFE();
    }
    else if (UART_GetITStatus(UART2, UART_IT_TXIEN)  != RESET)
    {
      SysClk48to8();
      SCB->SCR |= 0x4;
      __WFI();
      RCC->CR |= RCC_CR_HSION;
      SysClk8to48();
      //GPIO_SetBits(GPIOB, GPIO_Pin_7);        //TEST
    }
  }
}

/********************************************************************************************************
**function: IrqMcuGotoSleepAndWakeup
**@brief    This function is the MCU auto goto sleep AND wakeup, porting api. This function is used in interrupt mode
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void IrqMcuGotoSleepAndWakeup(void)
{
  if (ble_run_interrupt_McuCanSleep() == 0) return;
#ifdef USE_UART
  if ((SleepStop) &&
      (TxTimeout < SysTick_Count) &&
      (RxTimeout < SysTick_Count))
  {
    if (SleepStop == 1) //sleep
    {
      SleepStatus = 1;
      SCB->SCR &= 0xFB;
      __WFE();
    }
    else   //stop
    {
      SleepStatus = 2;
      SCB->SCR |= 0x4;
      __WFI();
#ifndef SWDDEBUG
      GPIO_ResetBits(GPIOA, GPIO_Pin_13);
#endif
    }
  }
#endif
}

/********************************************************************************************************
**function: DisableEnvINT
**@brief    Turn off Bluetooth interrupt.This function is used in the process of BLE processing data.
**                   
**@param    None.
**
**@return   None.
********************************************************************************************************/
void DisableEnvINT(void)
{
  GPIO_SetBits(GPIOB, GPIO_Pin_7);//to disable int
  __ASM volatile("cpsid i");
  dis_int_count ++;
}

/********************************************************************************************************
**function: EnableEnvINT
**@brief    Turn on Bluetooth interrupt.This function is used to open the interrupt after 
**          the BLE processing data is completed.                 
**@param    None.
**
**@return   None.
********************************************************************************************************/
void EnableEnvINT(void)
{
  //to enable/recover int
  dis_int_count --;
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
    if (!GetConnectedStatus())
    {
      comrxbuf_rd_pos = comrxbuf_wr_pos; //empty the buffer if any
    }
    else    //connected
    {
      if (comrxbuf_wr_pos > comrxbuf_rd_pos)
      {
        send = sconn_notifydata(rxBuf + comrxbuf_rd_pos, comrxbuf_wr_pos - comrxbuf_rd_pos);
        comrxbuf_rd_pos += send;
      }
      else
      {
        send = sconn_notifydata(rxBuf + comrxbuf_rd_pos, MAX_SIZE - comrxbuf_rd_pos);
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
#ifdef USE_AT_CMD
  CheckAtCmdInfo();
#else //AT CMD not supported
  CheckComPortInData();
#endif

  if ((2 != SleepStop) || (!(GPIO_ReadInputData(GPIOB) & 0x40))) //CTL low
  {
    if ((txLen) && (0 == PosW))
    {
      UART_ITConfig(UART2, UART_IT_TXIEN, ENABLE);
      UART_SendData(UART2, txBuf[PosW++]);
      TxTimeout = SysTick_Count + (20000 / BaudRate);
    }
  }
  if ((SleepStop == 2) && (RxTimeout < SysTick_Count))
  {
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

}




