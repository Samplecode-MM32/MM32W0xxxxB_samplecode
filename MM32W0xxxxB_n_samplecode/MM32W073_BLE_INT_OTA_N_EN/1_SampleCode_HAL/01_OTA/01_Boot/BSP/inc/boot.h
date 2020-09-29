#define APP_Offset                           (1024*4)
#define BOOT_PROGRAM_DATA_START			((uint32_t)0x08000000) 		  
#define APP_ENTRY_ADDRESS					 (uint32_t)0x08001010
#define LED4_ON()  GPIO_ResetBits(GPIOB,GPIO_Pin_5)	
#define LED4_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_5)	
#define LED4_TOGGLE()  (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5))?\
(GPIO_ResetBits(GPIOB,GPIO_Pin_5)):(GPIO_SetBits(GPIOB,GPIO_Pin_5))	

#define LED3_ON()  GPIO_ResetBits(GPIOB,GPIO_Pin_4)	
#define LED3_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_4)	
#define LED3_TOGGLE()  (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4))?\
(GPIO_ResetBits(GPIOB,GPIO_Pin_4)):(GPIO_SetBits(GPIOB,GPIO_Pin_4))	

#define LED2_ON()  GPIO_ResetBits(GPIOB,GPIO_Pin_3)	
#define LED2_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_3)	
#define LED2_TOGGLE()  (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3))?\
(GPIO_ResetBits(GPIOB,GPIO_Pin_3)):(GPIO_SetBits(GPIOB,GPIO_Pin_3))	

#define LED1_ON()  GPIO_ResetBits(GPIOA,GPIO_Pin_15)	
#define LED1_OFF()  GPIO_SetBits(GPIOA,GPIO_Pin_15)	
#define LED1_TOGGLE()  (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_15))?\
(GPIO_ResetBits(GPIOA,GPIO_Pin_15)):(GPIO_SetBits(GPIOA,GPIO_Pin_15))
//extern uint8_t  Boot_value; // RAM ±êÖ¾Î»





