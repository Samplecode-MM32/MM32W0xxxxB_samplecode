#include "iic.h"

#define MAX_SIZE 100

/********************************************************************************************************
 **function: IIC_Init
 **@brief    This function is the IIC initialization function.  Configure gpio and IIC in this function.
 **
 **@param    I2Cx :  I2C selection.
 **
 **@return   None.
 ********************************************************************************************************/

void IIC_Init(I2C_TypeDef *I2Cx) {
	//I2C_InitTypeDef I2C_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//I2C NVIC cfg
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3; //Preemption priority 3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IIC Interrupt enable
	NVIC_Init(&NVIC_InitStructure); //Initialize the VIC register according to the specified parameters

	if (I2Cx == I2C1) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);  //i2c1 clk enable
		GPIO_SetBits(GPIOA, GPIO_Pin_10);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //Push-pull output
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_SetBits(GPIOA, GPIO_Pin_10);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //i2c1_scl  pb6  i2c1_sda  pb7
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // Multiplexed open-drain output
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_1);
	}

	I2Cx->IC_ENABLE = 0x0;
	I2Cx->IC_CON = 0x122;
	I2Cx->IC_SAR = 0xAA >> 1; //Address
	I2Cx->IC_SS_SCL_HCNT = 0x77;
	I2Cx->IC_SS_SCL_LCNT = 0x55;
	I2Cx->IC_RX_TL = 0x0; //set Rx FIFO threshold level
	I2Cx->IC_TX_TL = 0x0; //set Tx FIFO threschold level
	I2Cx->IC_INTR_MASK = 0X24; //disable all inttrupt
	I2Cx->IC_ENABLE = 0x1;

//  I2Cx->IC_DATA_CMD |= 0x100;
}

extern u8 txBuf[], rxBuf[], txLen, PosW;
extern u16 RxCont;
/********************************************************************************************************
 **function: I2C1_IRQHandler
 **@brief    IIC interrupt function.Secondary interrupts include receive interrupts
 **          and transmit interrupts. Data can be processed in this interrupt
 **@param    None.
 **
 **@return   None.
 ********************************************************************************************************/
void I2C1_IRQHandler(void) {

	if ((I2C1->IC_INTR_STAT & 0x0004) == 0x0004) {
		I2C_ClearITPendingBit(I2C1, I2C_IT_RX_FULL);
		rxBuf[RxCont++] = I2C1->IC_DATA_CMD;
		if (RxCont >= MAX_SIZE) {
			RxCont = 0;
		}
	}
	if ((I2C1->IC_INTR_STAT & 0x0020) == 0x0020) {
		I2C_ClearITPendingBit(I2C1, I2C_IT_RD_REQ);
		if ((I2C1->IC_RAW_INTR_STAT & 0x0010) == 0x0010) {
			if (PosW < txLen) {
				I2C1->IC_DATA_CMD = txBuf[PosW++];
				I2C1->IC_CLR_RD_REQ; //dummy
				if (PosW == txLen) {
					txLen = 0;
					GPIO_SetBits(GPIOA, GPIO_Pin_10);
				}
			} else //over
			{
			}
		}
	}
}
