#include "usb.h"
#include "usbapp.h"
#include "sys.h"
#include "HAL_device.h"
#include "uart.h"
/********************************************************************************************************
**函数信息 ： usb_gpio                        
**功能描述 ： USB IO初始化
**输入参数 ：
**输出参数 ：
********************************************************************************************************/
void usb_gpio(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 					//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;   					//用于触发
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
/********************************************************************************************************
**函数信息 ： usb_test                      
**功能描述 ： USB外设初始化
**输入参数 ：
**输出参数 ：
********************************************************************************************************/
void usb_test(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB,ENABLE); 				//USB CLK EN
	
	usb_gpio();
#ifdef USB_INTR_MODE
	NVIC_InitStructure.NVIC_IRQChannel = USB_IRQn;		//配置USB中断向量
	NVIC_InitStructure.NVIC_IRQChannelPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
	usb_init();

}




#define CLICK_NO		0
#define CLICK_LEFT		1
#define CLICK_RIGHT		2
#define CLICK_MID		3
/********************************************************************************************************
**函数信息 ： mouse_ctrl               
**功能描述 ： 鼠标报告数据
**输入参数 ： char clickEnt(鼠标点击事件)
			 char x(x坐标移动相对位置)
			 char y(y坐标移动相对位置)
			 char rol(滚轮移动相对位置)
**输出参数 ：
********************************************************************************************************/
void mouse_ctrl(char clickEnt,char x,char y,char rol) 
{
	write_mreg32(USB_EPn_FIFO(EPIN),clickEnt);					//单击事件
	write_mreg32(USB_EPn_FIFO(EPIN),x);							//x坐标相对移动位置 (-128~127)
	write_mreg32(USB_EPn_FIFO(EPIN),y);							//y坐标相对移动位置 (-128~127)
	write_mreg32(USB_EPn_FIFO(EPIN),rol);						//滚轮相对移动位置 (-128~127)
	write_mreg32(USB_EPn_CTRL(EPIN),0x84);						//send 4 bytes packet	
}


#define KEY_NONE 	0x00
#define KEY_UP    	0x1A
#define KEY_DOWN  	0x16
#define KEY_LEFT  	0x04
#define KEY_RIGHT 	0x07
#define KEY_A		0x18
#define KEY_B		0x0C
#define KEY_C		0x0D
#define KEY_D		0x0E

#define KEY_L_CTRL	0x01
#define KEY_L_SHIFT	0x02
#define KEY_L_ALT	0x04
#define KEY_L_WIN	0x08
#define KEY_R_CTRL	0x10
#define KEY_R_SHIFT	0x20
#define KEY_R_ALT	0x40
#define KEY_R_WIN	0x80
/********************************************************************************************************
**函数信息 ： keyBoard_value               
**功能描述 ： 键盘报告数据
**输入参数 ： char spcKey(功能键)
			 nomKeyx(常用按键键值)
**输出参数 ：
********************************************************************************************************/
void keyBoard_value(char spcKey,char nomKey0,char nomKey1,char nomKey2,
					char nomKey3,char nomKey4,char nomKey5) 	
{
	write_mreg32(USB_EPn_FIFO(EPIN),spcKey);					//功能键
	write_mreg32(USB_EPn_FIFO(EPIN),0x00);						//保留
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey0);					//常用按键键值,按键1为0x59 数字依次类推
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey1);					//常用按键键值
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey2);					//常用按键键值
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey3);				
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey4);				
	write_mreg32(USB_EPn_FIFO(EPIN),nomKey5);						
	write_mreg32(USB_EPn_CTRL(EPIN),0x88);						//send 4 bytes packet		
}
/********************************************************************************************************
**函数信息 ： keyBoard_ctrl            
**功能描述 ： 键盘报告数据防重复发送
**输入参数 ： char spcKey(功能键)
			 nomKeyx(常用按键键值)
**输出参数 ：
********************************************************************************************************/
void keyBoard_ctrl(char spcKey,char nomKey0,char nomKey1,char nomKey2,
					char nomKey3,char nomKey4,char nomKey5)
{

	keyBoard_value(spcKey,nomKey0,nomKey1,nomKey2,nomKey3,nomKey4,nomKey5);	//键值写入缓冲寄存器
//	while(read_mreg32(USB_EPn_CTRL(EPIN))&0x80);							//等待发送完成
//	keyBoard_value(KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE);//清键值
//	while(read_mreg32(USB_EPn_CTRL(EPIN))&0x80);
	
}

