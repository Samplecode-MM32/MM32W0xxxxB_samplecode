#include "uart.h"
#define MAX_SIZE 100

u32 BaudRate = 9600;  //BaudRate/*115200*/

extern u8 txBuf[MAX_SIZE], rxBuf[MAX_SIZE], txLen, PosW;
extern u16 RxCont;
extern unsigned int RxTimeout, TxTimeout, SysTick_Count;

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#endif

#ifdef USE_IAR
PUTCHAR_PROTOTYPE
{
  while ((UART2->CSR & UART_IT_TXIEN) == 0); //Send data cyclically
  UART2->TDR = (ch & (uint16_t)0x00FF);
  return ch;
}

#else
#pragma import(__use_no_semihosting)
struct __FILE//Support functions required by the standard library
{
  int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
  x = x;
}
/********************************************************************************************************
**function: fputc
**@brief         Write a character to a file.redefine function of printf function,
**               need to call this function in printf function         
**@param    ch : Data to be transmitted
**
**@param    f  : Pointer to FILE structure
**
**@return   ch
********************************************************************************************************/
int fputc(int ch, FILE *f)//redefine function of printf function
{
  while ((UART2->CSR & UART_IT_TXIEN) == 0); //Send data cyclically
  UART2->TDR = (ch & (uint16_t)0x00FF);
  return ch;
}

#endif

/********************************************************************************************************
**function: uart_initwBaudRate
**@brief    Use this function to configure the basic configuration of the serial port,
**          such as serial clock, pins, interrupts
**@param    None
**
**@return   None.
********************************************************************************************************/
void uart_initwBaudRate(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  UART_InitTypeDef UART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE); //Enable UART2 clock
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);   //Enable GPIOA clock
  //UART2 NVIC Cfg
  NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3 ;      //Preemption priority 3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       //UART2 IRQ channel enable
  NVIC_Init(&NVIC_InitStructure);                       //Initialize the VIC register according to the specified parameters

  //UART  initialization Cfg
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

  UART_InitStructure.UART_BaudRate = BaudRate;              //BaudRate
  UART_InitStructure.UART_WordLength = UART_WordLength_8b;  //Word length is 8-bit data format
  UART_InitStructure.UART_StopBits = UART_StopBits_1;       //stop bit
  UART_InitStructure.UART_Parity = UART_Parity_No;//No parity
  UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//No hardware data flow control
  UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx; //Configure send and receive mode

  UART_Init(UART2, &UART_InitStructure);            //uart2 enable
  UART_ITConfig(UART2, UART_IT_RXIEN, ENABLE);      //Enable UART receive interrupt
  UART_ITConfig(UART2, UART_IT_TXIEN, DISABLE);
  UART_Cmd(UART2, ENABLE);                    

  //UART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;         //PA2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //Multiplexed push-pull output
  GPIO_Init(GPIOA, &GPIO_InitStructure);            //GPIO initialization

  //UART2_RX   GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//Floating input
  GPIO_Init(GPIOA, &GPIO_InitStructure);//GPIO initialization

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_3);

  //RTS
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //CTS
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

/********************************************************************************************************
**function: ChangeBaudRate
**@brief    Use this function to configure BaudRate
**          
**@param    None.
**
**@return   None.
********************************************************************************************************/
void ChangeBaudRate(void)
{
  uint32_t apbclock = 0x00;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  UART_Cmd(UART2, DISABLE);
  apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  UART2->BRR = (apbclock / BaudRate) / 16;
  UART2->FRA = (apbclock / BaudRate) % 16;
  UART_Cmd(UART1, ENABLE);
}
/********************************************************************************************************
**function: moduleOutData
**@brief    Data sending API functions.Serial communication can call this function to send data
**          
**@param    data : Data address
**
**@param    len : Data length
**
**@return   None.
********************************************************************************************************/
void moduleOutData(u8 *data, u8 len) //api
{
  unsigned char i;
  if ((txLen + len) < MAX_SIZE) //buff not overflow
  {
    for (i = 0; i < len; i++)
    {
      txBuf[txLen + i] = *(data + i);
    }
    txLen += len;
  }
}
/********************************************************************************************************
**function: UART2_IRQHandler
**@brief    Serial port interrupt function.Secondary interrupts include receive interrupts 
**          and transmit interrupts. Data can be processed in this interrupt          
**@param    None.
**
**@return   None.
********************************************************************************************************/
void UART2_IRQHandler(void)                 
{
  if (UART_GetITStatus(UART2, UART_IT_RXIEN)  != RESET)   //Receive interrupt
  {
    UART_ClearITPendingBit(UART2, UART_IT_RXIEN);
    rxBuf[RxCont] = UART_ReceiveData(UART2);
    RxTimeout = SysTick_Count + 1000;
    RxCont++;
    if (RxCont >= MAX_SIZE)
    {
      RxCont = 0;
    }
  }
  if (UART_GetITStatus(UART2, UART_IT_TXIEN)  != RESET)   //Send interrupt
  {
    UART_ClearITPendingBit(UART2, UART_IT_TXIEN);
    TxTimeout = SysTick_Count + (20000 / BaudRate);
    if (PosW < txLen)
    {
      UART_SendData(UART2, txBuf[PosW++]);
      if (PosW == txLen)
      {
        txLen = 0;
        PosW = 0;
      }
    }
    else
    {
      UART_ITConfig(UART2, UART_IT_TXIEN, DISABLE);
    }
  }
}




