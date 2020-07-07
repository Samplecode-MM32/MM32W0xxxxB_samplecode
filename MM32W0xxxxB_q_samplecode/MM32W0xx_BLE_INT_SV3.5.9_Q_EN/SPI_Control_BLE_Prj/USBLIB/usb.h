//********************************************************************
//(Copyright 2012) Verisilicon Inc. All Rights Reserved
//Company Confidential and Proprietary information
//This information may not be disclosed to unauthorized individual
//********************************************************************
//
//Verisilicon Microelectronics Co.,Ltd
//
//File name 	: usb.h
//Author		: 
//Verision		: V0.1
//Created		: 
//Modified		: Houyue.Shi 2012.02.24
//Description	:
//				  
//********************************************************************
#ifndef		_USB_REG_H
#define		_USB_REG_H
#include "sys.h"	 
#include "HAL_dma.h"


#define DEVICE_HID
#define	keyNums 10
#define keychar 26
#define KEYBOARD_HID
#ifndef DEVICE_HID
	#define USB_DEVICE_MASS_STORAGE
#endif

//#define USB_INTR_MODE
//#define USB_DMA_MODE	  wsf modify 2013.10.21
//#define USB_EP_STALL_TEST

#ifdef	USB_DMA_MODE	
//#define DMA_FLOW_CTRL_IS_PER
#ifdef DEVICE_HID
	#define USB_DMA_BURST1_8BIT
#else	
	#define USB_DMA_BURST1_8BIT
	//#define USB_DMA_BURST1_16BIT
	//#define USB_DMA_BURST1_32BIT
	//
	#ifdef USB_DMA_BURST1_8BIT
		//#define USB_CBWCSW_DMA_MODE
	#endif
#endif //DEVICE_HID	 	
#endif //USB_DMA_MODE

#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)<(b)?(a):(b))
	

#define IFCLASS_TEST 		0xDC
#define IFSUBCLASS_TEST		0xA0
#define IFPROTOCOL_TEST 	0xB0

#define IFCLASS_MASS 		0x08
#define IFSUBCLASS_MASS		0x06
#define IFPROTOCOL_MASS 	0x50

#define IFCLASS_HID 		0x03
#define IFSUBCLASS_HID		0x01
#define IFPROTOCOL_HID  	0x02

//#define   	USB_BASE          		(0x40010000)
//#define   	USB_BASE          		(0x40005C00)   //wsf modify

/*
#define     USB_DISK_OFFSET         (0x68001000)
//#define     USB_DISK_OFFSET_END     (0x68002000) //8K SRAM for release version
#define     USB_DISK_OFFSET_END     (0x68010000) //64K SRAM for debug verison
*/
//wsf  modify 2013.10.21
#define     USB_DISK_OFFSET         (0x40006000)
#define     USB_DISK_OFFSET_END     (0x400063FF) //64K SRAM for debug verison

#define     USB_PAGE_SIZE           	(512)
#define     EPn_MAX_PACKAGE_SIZE       	(64)
#define     EP0_MAX_PACKAGE_SIZE       	(64)

#define     IRQ_USB_NUM				(12)
#define     USB_EP0                 (0)
#define     USB_EPn(x)              (x)
/*********************************************************************************/
/***************please note: only EP1 and EP2 support DMA mode********************/
/***************please note: EP1&EP2 don't support bi-direction @DMA mode*********/
/*********************************************************************************/
#define 	EPIN					(USB_EPn(1))
#define 	EPOUT					(USB_EPn(2))
/*********************************************************************************/
/***************for DMA, channel can be assigned anyway***************************/
/*********************************************************************************/
#define 	DMA_TX_CH 				(0)
#define 	DMA_RX_CH 				(1)

// usb register group
#define     USB_TOP                 (USB_BASE )
#define     USB_INT_STATE           (USB_BASE + 0x4 )
#define     EP_INT_STATE           	(USB_BASE + 0x8 )
#define     EP0_INT_STATE           (USB_BASE + 0xc )
#define     USB_INT_EN           	(USB_BASE + 0x10 )
#define     EP_INT_EN           	(USB_BASE + 0x14 )
#define     EP0_INT_EN           	(USB_BASE + 0x18 )
#define 	EPn_INT_STATE(x)		(USB_BASE + 0x20+((x)-1)*0x04)
#define     EPn_INT_EN(x)           (USB_BASE + 0x40+((x)-1)*0x04 )
#define     USB_ADDR                (USB_BASE + 0x60 )
#define     USB_EP_EN               (USB_BASE + 0x64 )
#define     USB_EP_DMA_DIR          (USB_BASE + 0x68 )
#define     USB_EP_DMA_SIZE         (USB_BASE + 0x6c )
#define     USB_EP_INDEX1_2         (USB_BASE + 0x70 )
#define     USB_EP_INDEX3_4         (USB_BASE + 0x74 )
#define     USB_TOG_CTRL1_4         (USB_BASE + 0x78 )
#define     USB_EP_SETUPn(x)        (USB_BASE + 0x80 +(x)*0x04)
#define     USB_PACKAGE_SIZE0       (USB_BASE + 0xa0 )
#define     USB_PACKAGE_SIZE1       (USB_BASE + 0xa4 )
#define     USB_EP0_AVL       		(USB_BASE + 0x100 )
#define     USB_EPn_AVL(x)      	(USB_BASE + 0x100 +(x)*0x04 )
#define 	USB_DMA_BYTE_NUML(x)	(USB_BASE + 0x110 +((x)*0x10))
#define 	USB_DMA_BYTE_NUMH(x)	(USB_BASE + 0x114 +((x)*0x10))
#define 	USB_EP0_CTRL			(USB_BASE + 0x140 )
#define 	USB_EPn_CTRL(x)			(USB_BASE + 0x140 +(x)*0x04)
#define 	USB_EP0_FIFO			(USB_BASE + 0x160 )
#define 	USB_EPn_FIFO(x)			(USB_BASE + 0x160 +(x)*0x04)
#define 	USB_EP_MEM				(USB_BASE + 0x180 )
#define 	USB_EP_DMA				(USB_BASE + 0x184 )
#define 	USB_EP_HALT				(USB_BASE + 0x188 )

//#define 	USB_AHB_POWER			(USB_BASE + 0xd58 )
//#define 	USB_AHB_DMA				(USB_BASE + 0xd5c )
//#define 	USB_AHB_RST				(USB_BASE + 0xd60 )
#define 	USB_AHB_POWER			(USB_BASE + 0x1C0 )
#define 	USB_AHB_DMA				(USB_BASE + 0x1C4 )
#define 	USB_AHB_RST				(USB_BASE + 0x1C8 )

//usb_top registerr
#define	  	USB_FS                  	0x00
#define     USB_LS                  	0x01
#define     USB_CONNECT             	0x02
#define     USB_DISCONNECT          	0x00
#define     USB_USBRST              	0x08
//usb_int_state
#define     USB_INTHOSTRESET        	0x01
#define     USB_INTSUSPEND            	0x02
#define     USB_INTRESUME           	0x04
#define     USB_INTSOF             		0x08
#define     USB_INTEP      				0x10
#define     USB_INT_DMA	            	0x60
#define     USB_INT_DMA_CH0            	0x20
#define     USB_INT_DMA_CH1            	0x40
//ep_int_state
#define		EP0_INT						0x01
#define 	EPn_INT(x)					(1<<(x))
//ep0_int_state
#define		EP_SETUP					0x01
#define		EP_FINISH					0x02
#define		EP_IN_NACK					0x04
#define		EP_IN_ACK					0x08
#define		EP_IN_STALL					0x10
#define		EP_OUT_NACK					0x20
#define		EP_OUT_ACK					0x40
#define		EP_OUT_STALL				0x80
#define     EP_STALL					0x90
/*
//ep1~4_int_state
#define 	EP_TRANSFER_FINISH			0x02
#define 	EP_IN_NACK_RECV				0x04
#define 	EP_IN_ACK_RECV				0x08
#define 	EP_IN_STALL_RECV			0x10
#define 	EP_OUT_NACK_RECV			0x20
#define 	EP_OUT_ACK_RECV				0x40
#define 	EP_OUT_STALL_RECV			0x80
*/
#define     EP_DIR_IN				(0x01) //read ep to host
#define     EP_DIR_OUT				(0x00) //write host to ep
//
#define     EPn_DIR_IN(x)			(EP_DIR_IN<<((x)-1)) //read ep to host
#define     EPn_DIR_OUT(x)			(EP_DIR_OUT<<((x)-1)) //write host to ep
//

#define 	USB_INT_ENABLE 			0x01

#define     USB_IDLE                0xFF

#define     USB_CTRL_SETUP          0x00
#define     USB_CTRL_IN       		0x01
#define     USB_CTRL_OUT      		0x02

#define     USB_BULK_CBW            0x10
#define     USB_BULK_IN       		0x11
#define     USB_BULK_OUT            0x12
#define     USB_BULK_CSW            0x14
#define     USB_BULK_STALL          0x15

#define     MAX_STD_REQUEST         13


#define 	EPn_INPORT(x)				(0x80|(x))
#define 	EPn_OUTPORT(x)				(0x00|(x))

#define 	USB_DMA_BURST_1BYTE(ch)		(0x00<<(ch<<1))
#define 	USB_DMA_BURST_2BYTE(ch)		(0x01<<(ch<<1))
#define 	USB_DMA_BURST_4BYTE(ch)		(0x02<<(ch<<1))
#define 	USB_DMA_TIMEOUT					(0x70)

//===================code that is from usb1.1 protocal===========================//
// Usb Request Type
//transfer dircetion
#define 	USB_REQ_DIR_MASK			0x80
#define     USB_REQ_DIR_OUT				0x00 //host to device
#define     USB_REQ_DIR_IN				0x80 //device to host
//type
#define     USB_REQ_TYPE_MASK       	0x60     
#define     USB_REQ_TYPE_STANDARD       0x00
#define     USB_REQ_TYPE_CLASS          0x20
#define     USB_REQ_TYPE_VENDOR         0x40
#define     USB_REQ_TYPE_RESV	        0xE0
//recipient
#define 	USB_REQ_RECIP_MASK			0x1F
#define 	USB_REQ_RECIP_DEV			0x00
#define 	USB_REQ_RECIP_IF			0x01
#define 	USB_REQ_RECIP_EP			0x02
#define 	USB_REQ_RECIP_OTHER			0x03
#define 	USB_REQ_RECIP_RESV			0x04
//Feature
#define 	DEVICE_REMOTE_WAKEUP		0x01
#define 	ENDPOINT_HALT				0x00
// Standard Request Codes
#define     GET_STATUS             0
#define     CLEAR_FEATURE          1
#define     SET_FEATURE            3
#define     SET_ADDRESS            5
#define     GET_DESCRIPTOR         6
#define     SET_DESCRIPTOR         7
#define     GET_CONFIGURATION      8
#define     SET_CONFIGURATION      9
#define     GET_INTERFACE         10
#define     SET_INTERFACE         11
#define     SYNCH_FRAME           12

// Class Request Codes
#define     BULK_ONLY_MASS_STORAGE_RESET             0xFF
#define     GET_MAX_LUN             0xFE

// Scsi Command Operation Code List.
#define     TEST_UNIT_READY_OPCODE      0x00
#define     REQUEST_SENSE_OPCODE        0x03
#define     MODE_SELECT6_OPCODE         0x15   
#define     MODE_SENSE6_OPCODE          0x1A   
#define     INQUIRY_OPCODE              0x12
#define     START_STOP_UNIT_OPCODE      0x1B
#define     PREVENT_REMOVAL_OPCODE      0x1E
#define     _23_OPCODE                  0x23
#define     READ_CAPACITY10_OPCODE      0x25
#define     READ10_OPCODE               0x28
#define     WRITE10_OPCODE              0x2A
#define     VERIFY10_OPCODE             0x2F
#define     MODE_SENSE10_OPCODE         0x5A
//
#define     READTEST_OPCODE             0xA8
#define     WRITETEST_OPCODE            0xAA
#define     STALLIN_OPCODE	 			0xB8
#define     STALLOUT_OPCODE 			0xBA

// Descriptor Types
#define     DEVICE_DESC_TYPE              0x0100
#define     CONFIGURATION_DESC_TYPE       0x0200
#define     STRING_DESC_TYPE              0x0300
#define     INTERFACE_DESC_TYPE           0x0400
#define     ENDPOINT_DESC_TYPE            0x0500
//Class
#define 	HID_REPORT_TYPE				  0x2200

//for CSW
#define   CSW_CMD_PASSED				0x00
#define   CSW_CMD_FAILED				0x01
#define   CSW_PHASE_ERR					0x02



typedef unsigned long int 	uint32;
typedef unsigned short int  uint16;
typedef unsigned char  		uint8;
typedef signed long int  	int32;
typedef signed short int 	int16;
typedef signed char  	 	int8;

//typedef enum {FALSE = 0,TRUE = 1}BOOL;
typedef enum {
	USB_STATE_ATTACHED=0,
	USB_STATE_POWERED=1,
	USB_STATE_DEFAULT=2,
	USB_STATE_ADDRESS=3,
	USB_STATE_CONFIGURED=4,
	USB_STATE_SUSPENDED=5,
}USB_STATE_t;

//extern void    system_delay( uint32 temp);
extern volatile uint8 write_finish;
extern volatile uint8 dma_finished_flag[2];
extern volatile uint8 usb_running_state ;  // running stage
extern volatile uint8 usb_running_ctrl_state ;  // running stage

extern volatile uint8 usb_send_epn_stall[5];
extern volatile uint8 usb_ep_stall[5];
extern volatile uint8 usb_ep_in_stall[5];
extern volatile uint8 usb_ep_out_stall[5];
extern volatile uint8 usb_setup_flag;
extern volatile uint8 usb_out_flag;
extern volatile uint8 usb_in_flag;
extern volatile uint8 usb_reset_flag;
extern volatile uint8 usb_suspend_flag;
extern volatile uint8 usb_resume_flag;
extern volatile uint8 usb_finish_flag[5];
extern volatile uint8 usb_ep_flag;
extern volatile USB_STATE_t usb_state;
//extern DMA_REQUST usb_dma_rx_cmd,usb_dma_tx_cmd;
// for control transaction
extern volatile uint8    bmRequestType ;
extern volatile uint8    bRequest ;
extern volatile uint16   wValue ;
extern volatile uint16   wIndex ;
extern volatile uint16   wLength ;
extern volatile uint8    req_dir;//bmRequestType[7];
extern volatile uint8    req_type;//bmRequestType[6:5];
extern volatile uint8    req_recip;//bmRequestType[4:0];

extern  volatile uint8     dCBWSig[4] ;
extern  volatile uint8     dCBWTag[4] ;
extern  volatile uint8     bmCBWDataLength[4] ;
extern  volatile uint8     bmCBWFlag ;
extern  volatile uint8     bCBWLUN ;
extern  volatile uint8     bCBWCBLength ;
extern  volatile uint8     CBWCB[16];

extern volatile uint32 p_send_buf;
extern volatile uint32 p_recv_buf;
extern volatile uint32 send_residue;
extern volatile uint32 recv_residue;

#define USB_CSW_SIZE 13	
extern volatile char usb_csw_buf[USB_CSW_SIZE];
#define CBW_BUF_SIZE 31
extern volatile char usb_cbw_buf[CBW_BUF_SIZE];

// functions for control transaction
void usb_deal_cbw(void);
void usb_hid_report_handle(void);
void EP0_Send_Empty_Packet(void);
void Chap9_GetStatus( void);        // 0x00
void Chap9_ClearFeature( void);     // 0x01
void MLsup_StallEP0( void);         // reserve
void Chap9_SetFeature( void);	    // 0x03
void MLsup_StallEP1( void);         // reserve
void Chap9_SetAddress( void);	    // 0x05
void Chap9_GetDescriptor( void);    // 0x06
void Chap9_SetDescriptor( void);    // 0x07
void Chap9_GetConfiguration( void);	// 0x08
void Chap9_SetConfiguration( void);	// 0x09
void Chap9_GetInterface( void);		// 0x0a
void Chap9_SetInterface( void);		// 0x0b
void Class_Send_Max_Lun( void) ;    // 0xFE       
void Class_BulkOnly_MassStorage_Reset( void); //0xFF
void ScsiCmdInquiry( void);         // 0x12 
void ScsiCmdRequestSense(void);	//0x03
void _op_code_23_handle( void) ;    // 0x23
void _read_capacity_handle( void) ; // 0x25
void _read10_handle( uint32 stand_requst) ;        // 0x28
void _sense6_handle(void) ;        // 0x06
void _write10_handle( uint32 stand_requst) ;       // 0x2A
void _cmd_common_handle( void) ;   // 0x00
void ctrl_in_token_handle( void) ;
void ctrl_out_handle( void) ;
void ctrl_trans_finish_handle( void ) ;
void ctrl_deal_handle(void);
void USB_Prepare_CSW( uint32  num, uint32  state );
void SendCSWBack(void);
uint32 device_tx_fifo(uint32 srcAddr, uint32 byteCnt, uint32 bDMAmode);
uint32 device_rx_fifo(uint32 dstAddr, uint32 byteCnt, uint32 bDMAmode);
void usb_init( void);
void usb_setup_handle( void);
void usb_in_handle( void);
void usb_out_handle( void) ;
void usb_trans_finish( void);
void usb_reset_handle( void) ;
void usb_suspend_handle( void) ;
void usb_resume_handle( void) ;
void usb_wakeup_handle( void) ;
void USBTest(void);
void usb_test(void);
void usb_reset(void);

// usb dma 
void usb_dma_init(void);
void usb_dma_rx_start(uint32 srcAddr,uint32 dstAddr,uint32 byteCnt);
void usb_dma_tx_start(uint32 srcAddr,uint32 dstAddr,uint32 byteCnt);
//void usb_dma_process(DMA_REQUST * dma_req);
//void usb_dma_close(DMA_REQUST * dma_req);

uint32 read_mreg32( uint32 mreg);
void write_mreg32( uint32 mreg, uint32 val);
uint8 read_mreg8( uint32 mreg);
void write_mreg8( uint32 mreg, uint8 val);
void usb_delay1ms(uint32 dly);

void keyBoard_ctrl(char spcKey,char nomKey0,char nomKey1,char nomKey2,
					char nomKey3,char nomKey4,char nomKey5);

#endif

