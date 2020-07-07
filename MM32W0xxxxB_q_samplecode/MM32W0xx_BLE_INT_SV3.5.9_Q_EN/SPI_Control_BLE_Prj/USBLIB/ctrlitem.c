//********************************************************************
//(Copyright 2015) Mindmotion All Rights Reserved
//Company Confidential and Proprietary information
//This information may not be disclosed to unauthorized individual
//********************************************************************
//
//Verisilicon Microelectronics Co.,Ltd
//
//File name 	: ctrlitem.c
//Author		:
//Verision		: 
//Created	    : 
//Modified		: AE 2015.01.30
//Description	:
//				  
//********************************************************************
#include "usb.h"

#ifdef DEVICE_HID
	
	#ifdef  KEYBOARD_HID
	#define MY_VID  		0x080a
	#define MY_PID  		0x0606
	#else
	#define MY_VID  		0x0461
	#define MY_PID  		0x4D15
	#endif
	
#else 															//CBW/CSW
#ifdef USB_DEVICE_MASS_STORAGE
	#define MY_VID  		0x05E2
	#define MY_PID  		0x0101
	#define IFCLASS			IFCLASS_MASS
	#define IFSUBCLASS		IFSUBCLASS_MASS
	#define IFPROTOCOL      IFPROTOCOL_MASS 	
#else
	#define MY_VID  		0x05E4
	#define MY_PID  		0x0101
	#define IFCLASS			IFCLASS_TEST
	#define IFSUBCLASS		IFSUBCLASS_TEST
	#define IFPROTOCOL      IFPROTOCOL_TEST 	
#endif 															// MASS STORAGE
#endif 															//HID

volatile uint8    ctrl_buf[256] ;
volatile uint8    *p_ctrl_buf=0;
volatile uint8    ctrl_count ;
#ifdef DEVICE_HID												//HID 
/*(Mouse) information from Appendix E: Example USB Descriptors for HID Class Devices, in Page76 @ HID1.1*/
static uint8    DeviceDesc[] = {
0x12/*bLength*/,0x01/*bDescrType=DEVICE*/,0x10/*bcdUSB*/,0x01/*bcdUSB*/,0x00/*bDevClass*/,0x00/*bDevSubClass*/,0x00/*bDevProtocol*/,
EP0_MAX_PACKAGE_SIZE/*bMaxPacketSize*/,(MY_VID>>0)&0xFF/*idVendor*/,(MY_VID>>8)&0xFF/*idVendor*/,(MY_PID>>8)&0xFF/*idProduct*/,(MY_PID>>8)&0xFF/*idProduct*/,0x00/*bcdDev*/,0x02/*bcdDev*/,
0x00/*iManugacturer*/,0x02/*iProduct*/,0x00/*iSerialNum*/,0x01/*bNumConfig*/};  

#ifdef  KEYBOARD_HID

static uint8    ConfigDesc[] = {
0x09/*bLength*/,0x02/*bDescrType=CONFIGURATION*/,0x22/*wTotalLength*/,0x00/*wTotalLength*/,0x01/*bNumIF*/,0x01/*bCfgValue*/,0x00/*iConfig*/,0xA0/*bmAttribute=bus Power, remote wakeup*/,0x32/*MaxPower*/,/*device configuration*/
0x09/*bLength*/,0x04/*bDescrType=INTERFACES*/,0x00/*bIFNum*/,0x00/*bAlternateSetting*/,0x01/*bNumEP*/,IFCLASS_HID/*bIFClass=HID*/,IFSUBCLASS_HID/*bIFSubClass=boot IF*/,0x01/*bIFProtocol=keyboard*/,0x00/*biIF*/,/*interface configuration*/
0x09/*bLength*/,0x21/*bDescrType=HID*/,0x10/*bcdHID*/,0x01/*bcdHID*/,0x21/*bcountryCode*/,0x01/*bNumDescriptors=number of HID class Desriptors*/,0x22/*bDescriptorType=report*/,0x41/*wDescriptorLength=sizeof(IntefaceDes)*/,0x00/*wDescriptorLength*/,  /*HID Descriptor*/
0x07/*bLength*/,0x05/*bDescrType=ENDPOINT*/,EPn_INPORT(EPIN)/*bEPAddr*/,0x03/*bmAttributes=Interrupt*/,EPn_MAX_PACKAGE_SIZE/*wMaxPacketSize*/,0x00/*bInterval*/,0xFF/*bInterval*/
};/*EndPoint Configuration Descriptor*/
//0x05/*bDescrType=ENDPOINT*/,0x02/*bEPAddr*/,0x03/*bmAttributes=Interrupt*/,EPn_MAX_PACKAGE_SIZE/*wMaxPacketSize*/,0x00/*bInterval*/,0x0a/*bInterval*/

/*Report Descriptor (keyboard) */
static uint8    IntefaceDes[] = {  	0x05,0x01,0x09,0x06,0xa1,0x01,0x05,0x07,
									0x19,0xe0,0x29,0xe7,0x15,0x00,0x25,0x01,
									0x95,0x08,0x75,0x01,0x81,0x02,0x95,0x01,
									0x75,0x08,0x81,0x03,0x95,0x06,0x75,0x08,
									0x15,0x00,0x25,0xff,0x05,0x07,0x19,0x00,
									0x29,0x65,0x81,0x00,0x25,0x01,0x95,0x05,
									0x75,0x01,0x05,0x08,0x19,0x01,0x29,0x05,
									0x91,0x02,0x95,0x01,0x75,0x03,0x91,0x03,
									0xc0};
/*0~9 DEC: {HIDKeyVlaue,Ascll}*/
uint8	numASCLLConvertHIDKeyBoard[keyNums][2]={    {30,49}/*1*/,{31,50}/*2*/,{32,51}/*3*/,{33,52}/*4*/,{34,53}/*5*/,{35,54}/*6*/,{36,55}/*7*/,{37,56}/*8*/,{38,57}/*9*/,{39,48}/*0*/};

/*a(A)~z(Z) DEC: {HIDKeyVlaue,lowerAscll,upperAscll}*/
uint8   charASCLLConvertHIDKeyBoard[keychar][3]={    {04,97,65}/*a,A*/,{05,98,66}/*b,B*/,{06,99,67}/*c,C*/,{07,100,68}/*d,D*/,{8,101,69},/*e,E*/{9,102,70}/*f,F*/,{10,103,71}/*g,G*/, 
                                              {11,104,72}/*h,H*/,{12,105,73}/*i,I*/,{13,106,74}/*j,J*/,{14,107,75}/*k,K*/,{15,108,76}/*l,L*/,{16,109,77}/*m,M*/,{17,110,78}/*n,N*/,
                                              {18,111,79}/*o,O*/,{19,112,80}/*p,P*/,{20,113,81}/*q,Q*/,{21,114,82}/*r,R*/,{22,115,83}/*s,S*/,{23,116,84}/*t,T*/,
                                              {24,117,85}/*u,U*/,{25,118,86}/*v,V*/,{26,119,87}/*w,W*/,{27,120,88}/*x,X*/,{28,121,89}/*y,Y*/,{29,122,90}/*z,Z*/};

 #else
static uint8    ConfigDesc[] = {
0x09/*bLength*/,0x02/*bDescrType=CONFIGURATION*/,0x22/*wTotalLength*/,0x00/*wTotalLength*/,0x01/*bNumIF*/,0x01/*bCfgValue*/,0x00/*iConfig*/,0xA0/*bmAttribute=bus Power, remote wakeup*/,0x32/*MaxPower*/,/*device configuration*/
0x09/*bLength*/,0x04/*bDescrType=INTERFACES*/,0x00/*bIFNum*/,0x00/*bAlternateSetting*/,0x01/*bNumEP*/,IFCLASS_HID/*bIFClass=HID*/,IFSUBCLASS_HID/*bIFSubClass=boot IF*/,IFPROTOCOL_HID/*bIFProtocol=Mouse*/,0x00/*biIF*/,/*interface configuration*/
0x09/*bLength*/,0x21/*bDescrType=HID*/,0x11/*bcdHID*/,0x01/*bcdHID*/,0x00/*bcountryCode*/,0x01/*bNumDescriptors=number of HID class Desriptors*/,0x22/*bDescriptorType=report*/,0x34/*wDescriptorLength=sizeof(IntefaceDes)*/,0x00/*wDescriptorLength*/,  /*HID Descriptor*/
0x07/*bLength*/,0x05/*bDescrType=ENDPOINT*/,EPn_INPORT(EPIN)/*bEPAddr*/,0x03/*bmAttributes=Interrupt*/,EPn_MAX_PACKAGE_SIZE/*wMaxPacketSize*/,0x00/*bInterval*/,0x0a/*bInterval*/,


};/*EndPoint Configuration Descriptor*/

/*Report Descriptor (Mouse)*/
static uint8    IntefaceDes[] = {  0x05,0x01,0x09,0x02,0xa1,0x01,0x09,0x01,
								   0xa1,0x00,0x05,0x09,0x19,0x01,0x29,0x03,
								   0x15,0x00,0x25,0x01,0x75,0x01,0x95,0x03,
								   0x81,0x02,0x75,0x05,0x95,0x01,0x81,0x01,
								   0x05,0x01,0x09,0x30,0x09,0x31,0x09,0x38,
								   0x15,0x81,0x25,0x7f,0x75,0x08,0x95,0x03,
								   0x81,0x06,0xc0,0xc0};
 #endif

static uint8    Str0Desc[] = {0x04, 0x03, 0x09, 0x04 };
static uint8    Str1Desc[] = {0x04, 0x03, ' ', 0x00};
static uint8    Str2Desc[] = {0x24,0x03,0x55,0x00,0x53,0x00,0x42,0x00,
							   0x20,0x00,0x4f,0x00,0x70,0x00,0x74,0x00,
							   0x69,0x00,0x63,0x00,0x61,0x00,0x6c,0x00,
							   0x20,0x00,0x4d,0x00,0x6f,0x00,0x75,0x00,
							   0x73,0x00,0x65,0x00};

static uint8    Str3Desc[] = {0x16, 0x03, '2', 0x00, '0', 0x00, '2', 0x00, '7', 0x00, '3', 0x00,
                            '0', 0x00, '0', 0x00, '4', 0x00, '1', 0x00, '3', 0x00};



#define InterfaceDesLen		(sizeof(IntefaceDes))
#else // Mass-storage
//=========================== Common Para  =============================
static uint8    DeviceDesc[] = {    
0x12/*bLength*/, 0x01/*bDescrType=DEVICE*/, 0x10/*bcdUSB*/, 0x01/*bcdUSB*/, 0x00/*bDevClass*/, 0x00/*bDevSubClass*/, 0x00/*bDevProtocol*/,  // USB Version 1.10
EP0_MAX_PACKAGE_SIZE/*bMaxPacketSize*/,(MY_VID>>0)&0xFF/*idVendor*/,(MY_VID>>8)&0xFF/*idVendor*/,(MY_PID>>8)&0xFF/*idProduct*/,(MY_PID>>8)&0xFF/*idProduct*/, 0x00/*bcdDev*/, 0x01/*bcdDev*/,
0x01/*iManugacturer*/, 0x02/*iProduct*/, 0x03/*iSerialNum*/, 0x01/*bNumConfig*/} ;   

static uint8    ConfigDesc[] = {    
0x09/*bLength*/,0x02/*bDescrType=CONFIGURATION*/,0x20/*wTotalLength*/,0x00/*wTotalLength*/,0x01/*bNumIF*/,0x01/*bCfgValue*/,0x00/*iConfig*/,0xA0/*bmAttribute=bus Power, remote wakeup*/,0x32/*MaxPower*/,/*device configuration*/
0x09/*bLength*/,0x04/*bDescrType=INTERFACES*/,0x00/*bIFNum*/,0x00/*bAlternateSetting*/,0x02/*bNumEP*/,IFCLASS/*bIFClass=Mass Storage*/,IFSUBCLASS/*bIFSubClass*/,IFPROTOCOL/*bIFProtocol=Bulk-Only*/,0x00/*biIF*/,/*interface configuration*/
0x07/*bLength*/,0x05/*bDescrType=ENDPOINT*/,EPn_INPORT(EPIN)/*bEPAddr*/,0x02/*bmAttribute=Bulk*/,EPn_MAX_PACKAGE_SIZE/*wMaxPacketSize*/,0x00/*wMaxPacketSize*/,0x00/*bInterval*/,/*ep configuration*/
0x07/*bLength*/,0x05/*bDescrType=ENDPOINT*/,EPn_OUTPORT(EPOUT)/*bEPAddr*/,0x02/*bmAttribute=Bulk*/,EPn_MAX_PACKAGE_SIZE/*wMaxPacketSize*/,0x00/*wMaxPacketSize*/,0x00/*bInterval*/}/*ep configuration*/;

static uint8    Str0Desc[] = {0x04/*bLength*/, 0x03/*bDescrType=STRING*/, 0x09, 0x04 };
/*manugacturer*/
static uint8    Str1Desc[] = {0x04/*bLength*/, 0x03/*bDescrType=STRING*/, ' '/*' '*/, 0x00};
/*Product*/
static uint8    Str2Desc[] = {0x1a/*bLength*/, 0x03/*bDescrType=STRING*/, 
							'S', 0x00, 'C', 0x00, 'C', 0x00, '5',
                            0x00, '1', 0x00, '.', 0x00, '1', 0x00, ' ', 0x00,
                            'D',  0x00, 'i', 0x00, 's', 0x00, 'k', 0x00};
/*serial number at least 12 characters @4.1.1 */
static uint8    Str3Desc[] = {0x16/*bLength*/, 0x03/*bDescrType=STRING*/, 
							'2', 0x00, '0', 0x00, '2', 0x00, '7', 0x00, '3', 0x00,
                            '0', 0x00, '0', 0x00, '4', 0x00, '1', 0x00, '3', 0x00};
#endif 
#define DeviceDescLen       (sizeof(DeviceDesc))
#define ConfigDescLen       (sizeof(ConfigDesc))
#define Str0DescLen         (sizeof(Str0Desc))
#define Str1DescLen         (sizeof(Str1Desc))
#define Str2DescLen         (sizeof(Str2Desc))
#define Str3DescLen         (sizeof(Str3Desc))
static uint8    StrDescLenGroup[] = { Str0DescLen, Str1DescLen, Str2DescLen, Str3DescLen } ;
//=========================== Each Request =============================
void Chap9_SetConfiguration( void)								//0x09
{
	if(req_dir == USB_REQ_DIR_OUT)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{
		
	}
}
void Chap9_SetAddress( void)	    							//0x05
{
	if(req_dir == USB_REQ_DIR_OUT)
	{
		EP0_Send_Empty_Packet();	
		usb_state = USB_STATE_ADDRESS;
	}
	else
	{

	}
}

void Get_Desc_Prepare( void)
{
	uint32 type = wValue & 0xFF00;
	uint32 index = wValue & 0x00FF;
    switch(type)
    {
        case    DEVICE_DESC_TYPE :
        {  	
            if( wLength > DeviceDescLen )   wLength = DeviceDescLen ;
            p_ctrl_buf = DeviceDesc ;
		
            break ;
        }
        case    CONFIGURATION_DESC_TYPE :
        {
            if( wLength > ConfigDescLen )   wLength = ConfigDescLen ;
            p_ctrl_buf = ConfigDesc ;

            break ;
        }
        case    STRING_DESC_TYPE :
        {
            if( index < 4 )
            {
                if( wLength > StrDescLenGroup[index] )   
					wLength = StrDescLenGroup[index] ;
                switch(index)
                {
					case 0:
						p_ctrl_buf = Str0Desc;
						break;
					case 1:
						p_ctrl_buf = Str1Desc;
						break;
					case 2:
						p_ctrl_buf = Str2Desc;
						break;
					case 3:
						p_ctrl_buf = Str3Desc;
						break;
                }

            }
			else
            {
                wLength = 0 ;
            }
            break ;
        }
#ifdef DEVICE_HID		
		case HID_REPORT_TYPE:  									// class des
		{
			if( wLength > ConfigDescLen )   wLength = InterfaceDesLen;
			p_ctrl_buf = IntefaceDes;

			break;
		}
#endif		
        default :
        {
            wLength = 0 ;
            break ;
        }
    }
}
void Chap9_GetDescriptor( void)     							//0x06
{
	static uint16    ctrl_buf_ix = 0;
	
    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :
        {	
            Get_Desc_Prepare( ) ;								//发送BUF指针指向待发送数据
			usb_running_ctrl_state = USB_CTRL_IN ;
			ctrl_buf_ix = 0;

            break ;
        }
        case    USB_CTRL_IN :
        {
            uint16    count = 0;
            uint16    ix = 0 ;
			
			if(wLength>0)										//数据分批发送
			{
				count = MIN(EP0_MAX_PACKAGE_SIZE,wLength);
				while(read_mreg32(USB_EP0_CTRL)&0x80);			//wait last send data finish
				for(ix=0; ix < count; ix++)
	            {

	                write_mreg32(USB_EP0_FIFO,p_ctrl_buf[ctrl_buf_ix]);//将数据写入FIFO
					ctrl_buf_ix++;
	            }
	            write_mreg32(USB_EP0_CTRL,count|0x80);  		//待发送数据准备就绪
	            wLength -= count;
			}			
			if( wLength == 0)
           	{
           		if(count==EP0_MAX_PACKAGE_SIZE)					//发送数据总数为包最大值的整数倍时在末尾帧发送空数据
       			{
					EP0_Send_Empty_Packet();
				}
				else
				{
				}
                usb_running_ctrl_state = USB_IDLE;				//数据发送完成
				ctrl_buf_ix = 0;
           	}
            break ;
        }
        default :
        {
            usb_running_ctrl_state = USB_IDLE ;
            break ;
        }
    }
	usb_state = USB_STATE_CONFIGURED;
}
void Class_Send_Max_Lun( void)      							// bRequest = 0xFE        
{
	switch( usb_running_ctrl_state )
	{
	    case    USB_CTRL_SETUP :
	    {
			if(req_dir == USB_REQ_DIR_IN)
	            usb_running_ctrl_state = USB_CTRL_IN;
			else
	            usb_running_ctrl_state = USB_IDLE;
	        break ;
	    }
	    case    USB_CTRL_IN :
	    {
	
#ifdef USB_EP_STALL_TEST
			{
				write_mreg32(USB_EP_HALT,0x01);
			#ifndef SCC5_VER_0302				
		    	write_mreg32(USB_EP0_CTRL,0x80);
		    #endif
		    	usb_send_epn_stall[0] = TRUE;
			}
#else
			{
				while(read_mreg32(USB_EP0_CTRL)&0x80);			//wait last send data finish
				write_mreg32(USB_EP0_FIFO,0);
		    	write_mreg32(USB_EP0_CTRL,0x81);
	    	}
#endif
	    	usb_running_ctrl_state = USB_IDLE;  
	        break ;
	    }		
	    default :
	    {
	        usb_running_ctrl_state = USB_IDLE ;
	        break ;
	    }
	} 
}


void Chap9_GetStatus( void)         							// 0x00
{
    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :
        {
			usb_running_ctrl_state = USB_CTRL_IN;
			break;
       	}
		case USB_CTRL_IN:
		{
			if(req_dir == USB_REQ_DIR_IN)
			{
				if(req_recip==USB_REQ_RECIP_EP)
				{		
					char ep = wIndex & 0x0F;
					write_mreg32(USB_EP0_FIFO,usb_ep_stall[ep]);
					write_mreg32(USB_EP0_FIFO,0x00);
				}
				else if(req_recip==USB_REQ_RECIP_DEV)
				{
					write_mreg32(USB_EP0_FIFO,0x02);
					write_mreg32(USB_EP0_FIFO,0x00);
				}
				else
				{
					write_mreg32(USB_EP0_FIFO,0x00);
					write_mreg32(USB_EP0_FIFO,0x00);
				}			
				write_mreg32(USB_EP0_CTRL,0x82);	        	
	        }		
			else
			{

			}
			usb_running_ctrl_state = USB_IDLE;
			break;				
	    }
        default :
        {
            usb_running_ctrl_state = USB_IDLE ;
            break ;
        }
	}
}

void Chap9_ClearFeature( void)      							// 0x01
{
	switch(usb_running_ctrl_state)
	{
        case    USB_CTRL_SETUP :
        {
			if(req_dir == USB_REQ_DIR_OUT)
			{
				uint8 ix;
				if((req_recip==USB_REQ_RECIP_EP)&&(wValue==ENDPOINT_HALT))//ENDPOINT_HALT
				{
					write_mreg32(USB_EP_HALT,0x00); 			//clear epn halt

					for(ix = 0; ix < 5; ix++)
					{
						usb_ep_stall[ix] = FALSE;
						usb_send_epn_stall[ix] = FALSE;	
					}
				}
				else if((req_recip==USB_REQ_RECIP_DEV)&&(wValue==DEVICE_REMOTE_WAKEUP))//DEVICE_REMOTE_WAKEUP
				{
				
				
				}					
			}
			else
			{

			}
			usb_running_ctrl_state = USB_CTRL_IN;
			break;
		}
	case USB_CTRL_IN: 											//status stage
		{
			EP0_Send_Empty_Packet();
        }
	default:
		{
			usb_running_ctrl_state = USB_IDLE;
			break;
		}
	}
}
void MLsup_StallEP0( void)          							// reserve      0x02
{
	if(req_dir == USB_REQ_DIR_IN)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}
void MLsup_StallEP1( void)          							// reserve      0x04
{
	if(req_dir == USB_REQ_DIR_IN)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}
void Chap9_SetFeature( void)	    							// 0x03
{
	if(req_dir == USB_REQ_DIR_OUT)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}

void Chap9_SetDescriptor( void)     							//0x07
{
	if(req_dir == USB_REQ_DIR_OUT)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}
void Chap9_GetConfiguration( void)								//0x08
{
	if(req_dir == USB_REQ_DIR_IN)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}

void Chap9_GetInterface( void)									//0x0a
{
	if(req_dir == USB_REQ_DIR_IN)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}
void Chap9_SetInterface( void)									//0x0b
{
	if(req_dir == USB_REQ_DIR_OUT)
	{
		EP0_Send_Empty_Packet();
	}
	else
	{

	}
}


void EP0_Send_Empty_Packet()
{

    switch( usb_running_ctrl_state )
    {
        case    USB_CTRL_SETUP :
        {
            usb_running_ctrl_state = USB_CTRL_IN;
            break ;
        }
        case    USB_CTRL_IN :
        {
			while(read_mreg32(USB_EP0_CTRL)&0x80); 				//wait last send data finish
        	write_mreg32(USB_EP0_CTRL,0x80);					//send empty packet
        	usb_running_ctrl_state = USB_IDLE; 
            break ;
        }		
        default :
        {
            usb_running_ctrl_state = USB_IDLE ;
            break ;
        }
    } 
}

