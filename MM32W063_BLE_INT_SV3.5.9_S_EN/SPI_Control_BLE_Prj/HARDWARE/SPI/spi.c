#include "HAL_device.h"
#include "HAL_conf.h"
#include "spi.h"

/********************************************************************************************************
**function: SPI_WriteRead
**@brief    SPI2 read and write functions 
**                   
**@param    SendData :  SPI2 read or write data
**
**@param    WriteFlag :  SPI2 read or write flag
**
**@return   SPI2->RXREG :  SPI2 received data
********************************************************************************************************/
unsigned char SPI_WriteRead(unsigned char SendData, unsigned char WriteFlag) //porting api
{
  SPI2->TXREG = SendData;
  while (!(SPI2->CSTAT & SPI_FLAG_TXEPT));
  while (!(SPI2->CSTAT & SPI_FLAG_RXAVL));
  return SPI2->RXREG;
}

/********************************************************************************************************
**function: SPI_CS_Enable_
**@brief    SPI2 CS enable
**                   
**@return   None.
********************************************************************************************************/
void SPI_CS_Enable_(void) //porting api
{
  //SPI1->SCSR &= SPI_CS_BIT0;
  GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

/********************************************************************************************************
**function: SPI_CS_Disable_
**@brief    SPI2 CS disable
**
**@return   None.
********************************************************************************************************/
void SPI_CS_Disable_(void) //porting api
{
  //SPI1->SCSR |= ~SPI_CS_BIT0;
  GPIO_SetBits(GPIOB, GPIO_Pin_15);
}

/********************************************************************************************************
**function: SPIM_TXEn
**@brief    SPI2 tx enable
**                   
**@param    SPIx £ºspi selection.such as SPI1 , SPI2
**
**@return   None.
********************************************************************************************************/
void SPIM_TXEn(SPI_TypeDef *SPIx)
{
  //Transmit Enable bit TXEN
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Tx);
}

/********************************************************************************************************
**function: SPIM_TXDisable
**@brief    SPI2 tx disable
**                   
**@param    SPIx £ºspi selection.such as SPI1 , SPI2
**
**@return   None.
********************************************************************************************************/
void SPIM_TXDisable(SPI_TypeDef *SPIx)
{
  //disable TXEN
  SPI_BiDirectionalLineConfig(SPIx, SPI_Disable_Tx);
}

/********************************************************************************************************
**function: SPIM_RXEn
**@brief    SPI2 rx enable.
**                   
**@param    SPIx £ºspi selection.such as SPI1 , SPI2.
**
**@return   None.
********************************************************************************************************/
void SPIM_RXEn(SPI_TypeDef *SPIx)
{
  //enable RXEN
  SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);
}

/********************************************************************************************************
**function: SPIM_RXDisable
**@brief    SPI2 rx disable.
**                   
**@param    SPIx £ºspi selection.such as SPI1 , SPI2.
**
**@return   None.
********************************************************************************************************/
void SPIM_RXDisable(SPI_TypeDef *SPIx)
{
  //disable RXEN
  SPI_BiDirectionalLineConfig(SPIx, SPI_Disable_Rx);
}

/********************************************************************************************************
**function: SPIM_Init
**@brief    This function is the spi initialization function.  Configure gpio and spi in this function.
**                   
**@param    SPIx :  SPI2 selection.
**
**@param    spi_baud_div £º Set the SPI transmission.
**
**@return   None.
********************************************************************************************************/
void SPIM_Init(SPI_TypeDef *SPIx, unsigned short spi_baud_div)
{
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;
  if (SPIx == SPI2)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    SPI_CS_Disable_();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_4); //MISO
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_4); //MOSI
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_3); //SCK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_1); //CSN

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;       //spi2_cs  pb15
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Push-pull output
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_12); //csn=H
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;       //spi2_sck  pb14
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // Multiplexed push-pull output
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;       //spi2_mosi  pb13
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // Multiplexed push-pull output
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;     //spi2_miso  pb12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //Pull-up input
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  }

  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;    // mode0 SPI_CPOL_Low, SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;  // mode3 SPI_CPOL_High,SPI_CPHA_2Edge
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = spi_baud_div;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_Init(SPIx, &SPI_InitStructure);

  SPI_Cmd(SPIx, ENABLE); //Enables the specified SPI peripheral
  SPIM_TXEn(SPIx);
  SPIM_RXEn(SPIx);
}







