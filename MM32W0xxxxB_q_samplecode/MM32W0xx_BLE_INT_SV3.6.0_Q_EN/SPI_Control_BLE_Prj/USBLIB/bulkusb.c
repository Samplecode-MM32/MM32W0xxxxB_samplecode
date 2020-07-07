//********************************************************************
//(Copyright 2015) Mindmotion All Rights Reserved
//Company Confidential and Proprietary information
//This information may not be disclosed to unauthorized individual
//********************************************************************
//
//Mindmotion Microelectronics Co.,Ltd
//
//File name 	: Bulkusb.c
//Author		  :
//Verision		: 
//Created		  : 
//Modified		: AE 2015.01.30
//Description	:
//				  
//********************************************************************
#include "usb.h"

volatile uint8   dCBWSig[4] ;
volatile uint8   dCBWTag[4] ;
volatile uint8  bmCBWDataLength[4] ;
volatile uint8   bmCBWFlag ;
volatile uint8  bCBWLUN ;
volatile uint8   bCBWCBLength ;
volatile uint8   CBWCB[16];
volatile char usb_cbw_buf[CBW_BUF_SIZE];
extern u8 txBufFromBLEtoUSB[];
void Deal_Trans_Items( void)
{
    switch( CBWCB[0] )
    {
        case    INQUIRY_OPCODE :    							// 0x12
        {
            ScsiCmdInquiry( ) ;
            break ;
        }
		    case    REQUEST_SENSE_OPCODE:    					// 0x03
        {
            ScsiCmdRequestSense( ) ;
            break ;
        }
        case    _23_OPCODE :        							// 0x23
        {
            _op_code_23_handle( ) ;
            break ;
        }
        case    READ_CAPACITY10_OPCODE :    					// 0x25
        {
            _read_capacity_handle( ) ;
            break ;
        }
        case    READ10_OPCODE :             					// 0x28
        {
            _read10_handle(TRUE) ;
            break ;
        }
        case    MODE_SENSE6_OPCODE :        					// 0x1A
        {
            _sense6_handle( ) ;
            break ;
        }
        case    WRITE10_OPCODE :            					// 0x2A
        {
            _write10_handle(TRUE);
            break ;
        }
        case    READTEST_OPCODE :             					// 0xA8
        {
            _read10_handle(FALSE) ;
            break ;
        }
		    case    WRITETEST_OPCODE :            				// 0xAA
        {		
            _write10_handle(FALSE);
            break ;
        }
		    case    STALLOUT_OPCODE :            				// 0xB8
        {		
						write_mreg32(USB_EP_HALT,(1<<EPOUT));  	//all epn except ep0 send stall
						usb_send_epn_stall[EPOUT]=TRUE;
			#ifdef printf
            printf( "EP enable out stall Cmd, 0x%x\r\n", CBWCB[0] ) ;
			#endif 
            usb_running_state = USB_IDLE ;
						p_recv_buf = (uint32)usb_cbw_buf;
						recv_residue = sizeof(usb_cbw_buf);
            break ;
        }
		
		    case    STALLIN_OPCODE :            				// 0xBA
        {		
						usb_send_epn_stall[EPIN]=TRUE;
			#ifdef printf
            printf( "EP enable In stall Cmd, 0x%x\r\n", CBWCB[0] ) ;
			#endif 
            usb_running_state = USB_IDLE ;
						p_recv_buf = (uint32)usb_cbw_buf;
						recv_residue = sizeof(usb_cbw_buf);

            break ;
        }
		
        case    TEST_UNIT_READY_OPCODE :    					// 0x00
        case    PREVENT_REMOVAL_OPCODE :    					// 0x1E
        case    VERIFY10_OPCODE :           					// 0x2F    
        {
            _cmd_common_handle( ) ;
            break ;
        }                
        default :
        {
			#ifdef printf
            printf( "Unknown Cmd, 0x%x\r\n", CBWCB[0] ) ;
			#endif 
#ifdef USB_EP_STALL_TEST
						write_mreg32(USB_EP_HALT,(1<<EPOUT));
						usb_send_epn_stall[EPOUT] = TRUE;
#endif

						usb_running_state = USB_IDLE ;			
						p_recv_buf = (uint32)usb_cbw_buf;
						recv_residue = sizeof(usb_cbw_buf);
						break;
        }
    }    
}
// ==================================== Low Sub Feature ===================================
void usb_cbw_handle( void)
{

	uint32 cnt = MIN(recv_residue,EPn_MAX_PACKAGE_SIZE);
#ifdef USB_CBWCSW_DMA_MODE	
	p_recv_buf = device_rx_fifo(p_recv_buf,cnt,TRUE);
#else
	p_recv_buf = device_rx_fifo(p_recv_buf,cnt,FALSE);
#endif
	recv_residue -= cnt;
	if(recv_residue == 0)
	{
		usb_deal_cbw();
    }
}

void usb_deal_cbw(void)
{
    uint8   cbw_ix;
    uint8   dCBWSigCont[4] = { 0x55, 0x53, 0x42, 0x43 } ;   	// USBC dCBWSignature
    uint8   error_flag = 0 ;
	//***********************************************//
	//Table 5.1 Command Block Wrapper
	//***********************************************//	
 	//read dCBWSignature byte[3]--byte[0]
    for( cbw_ix = 0; cbw_ix <= 3; cbw_ix++ )  
   	{
		dCBWSig[cbw_ix-0] = usb_cbw_buf[cbw_ix];
    }
	//read dCBWTag byte[7]--byte[4]
    for( cbw_ix = 4; cbw_ix <= 7; cbw_ix++ )  
   	{
		dCBWTag[cbw_ix-4] = usb_cbw_buf[cbw_ix];
   	}
	//read dCBWDataTRansferLength byte[11]--byte[8]
    for( cbw_ix = 8; cbw_ix <= 11; cbw_ix++ )  
   	{
		bmCBWDataLength[cbw_ix-8] = usb_cbw_buf[cbw_ix];
   	}
	//read bmCBWFlags byte[12]
    bmCBWFlag = usb_cbw_buf[12];
	//read bCBWLUN byte[13]
    bCBWLUN = usb_cbw_buf[13];
	//read bCBWCBLength byte[14]
    bCBWCBLength = usb_cbw_buf[14];								//valid data is 1--16
    //read CBWCB byte[30]--byte[15]
    for( cbw_ix = 15; cbw_ix <= 30; cbw_ix++ ) 
   	{
		CBWCB[cbw_ix-15] = usb_cbw_buf[cbw_ix];
   	}
    //judge correct or wrong
    for( cbw_ix = 0; cbw_ix < 4; cbw_ix++ )  
    {
        if( dCBWSigCont[cbw_ix] != dCBWSig[cbw_ix] )    
			error_flag = 1 ;
    }
    if( bCBWLUN != 0x00 )   
	{
		error_flag = 1 ;
	}
    if( error_flag )    
    {
		#ifdef printf
		printf("CBW error!\r\n");
		#endif
        usb_running_state = USB_IDLE ;
		p_recv_buf = (uint32)usb_cbw_buf;
		recv_residue = sizeof(usb_cbw_buf);
        return ;
    }	
    usb_running_state = USB_BULK_CBW ;
  	Deal_Trans_Items( ) ;
}

void usb_bulk_in_token_handle( void)
{
    Deal_Trans_Items( ) ;
}
void usb_bulk_out_handle( void)
{
    Deal_Trans_Items( ) ;
}
void usb_bulk_trans_finish_handle( void)
{
    Deal_Trans_Items( ) ;
}
// =============================== usb IN OUT main fature ==========================
void usb_in_handle( void)       // IN Request Received
{
	if( usb_ep_flag== USB_EP0 )
	{
		ctrl_in_token_handle() ;
	}
	else 
	{
#ifdef DEVICE_HID
		usb_hid_report_handle();
#else
#ifndef USB_DEVICE_MASS_STORAGE
		if( usb_running_state == USB_IDLE)
		{
			if(usb_send_epn_stall[EPIN])
			{
				write_mreg32(USB_EP_HALT,(1<<EPIN));  			//all epn except ep0 send stall
				#ifdef printf
	            printf( "EP Send in stall Cmd\r\n") ;
				#endif
			}
			else
			{			
				write_mreg32(USB_EPn_FIFO(EPIN),'U');
				write_mreg32(USB_EPn_CTRL(EPIN),0x81);
				#ifdef printf
	            printf( "in@IDLE\r\n") ;
				#endif
			}
		}
		else
#endif 			
		{
			usb_bulk_in_token_handle( ) ;
		}		

#endif
	}

}

void usb_out_handle( void)      								// OUT Packet Received
{
	if( usb_ep_flag == USB_EP0 )
	{
		ctrl_out_handle();
		p_recv_buf = (uint32)usb_cbw_buf;
		recv_residue = sizeof(usb_cbw_buf);		
	}
	else
	{
		if( usb_running_state == USB_IDLE)
		{
			usb_cbw_handle();
		}
		else                       								// Out for bulk trans 
		{
			usb_bulk_out_handle();

		}
	}

}

uint32 device_rx_fifo(uint32 dstAddr, uint32 byteCnt,uint32 bDMAmode)
{
	uint32 count;
	for( count = 0; count < byteCnt; count++ )
	{
		uint8 val=read_mreg8(USB_EPn_FIFO(EPOUT));
		write_mreg8(dstAddr,val);
		dstAddr++;
  }

	return dstAddr;
}

uint32 device_tx_fifo(uint32 srcAddr, uint32 byteCnt, uint32 bDMAmode)
{
	uint32 count;
	while(read_mreg32(USB_EPn_CTRL(EPIN))&0x80);				//wait last send data finish, maybe not need it
	for( count = 0; count < byteCnt; count++)
	{
		uint8 val = read_mreg8(srcAddr);
		write_mreg8(USB_EPn_FIFO(EPIN),val);
		srcAddr++;
	}
	write_mreg32(USB_EPn_CTRL(EPIN),0x80|byteCnt);

	return srcAddr;
}


extern u8 BLE_DATA;
extern u8 txBuf[100];
#ifdef DEVICE_HID

void usb_hid_report_handle()
{
#ifdef USB_EP_STALL_TEST
	static uint32 hid_cnt = 1;
	if(((hid_cnt++)%0x80==0x00))	
	{
		write_mreg32(USB_EP_HALT,(1<<(EPIN)));
		#ifndef SCC5_VER_0302				
	    	write_mreg32(USB_EPn_CTRL(EPOUT),0x80);//
	    #endif			
		usb_send_epn_stall[EPIN] = TRUE;
	}
	else
#endif
	{
#ifdef USB_DMA_MODE

		uint32 ch;
		uint32 *hid_val = (uint32*)0x68000000; 					//because it's place at sram which dam can access
		hid_val[0] = 0x00010100;
		usb_dma_tx_start((uint32)hid_val,USB_EPn_FIFO(EPIN),sizeof(hid_val));
		ch = (EPIN==USB_EPn(1))?(0):(1);
		dma_finished_flag[ch] = 0;
#ifdef USB_INTR_MODE			
		while(dma_finished_flag[ch]==0x00);						//wait dma transfer done
#else
		do{
			uint32 temp = read_mreg32(USB_INT_STATE);
			if(ch==0)
			{
				if(temp&USB_INT_DMA_CH0) 
				{
					dma_finished_flag[0]=1; 					//dma transfer done
					write_mreg32(USB_INT_STATE, USB_INT_DMA_CH0);//clear interrupt
					break;
				}
			}else
			{			
				if(temp&USB_INT_DMA_CH1) 
				{
					dma_finished_flag[1]=1; 					//dma transfer done
					write_mreg32(USB_INT_STATE, USB_INT_DMA_CH1);//clear interrupt
					break;
				}
			}
		}while(1);												//wait dma transfer done
#endif
		dma_finished_flag[ch] = 0;
		usb_dma_close(&usb_dma_tx_cmd);
#else
//		while(read_mreg32(USB_EPn_CTRL(EPIN))&0x80);			//wait last send data finish
		
		if(read_mreg32( USB_EPn_CTRL(EPIN)) == 0)
		{
			if(BLE_DATA == 1)
			{
				GPIOA->ODR ^= 1<<6;
				keyBoard_ctrl(0x00,txBufFromBLEtoUSB[0],txBufFromBLEtoUSB[1],txBufFromBLEtoUSB[2],txBufFromBLEtoUSB[3],txBufFromBLEtoUSB[4],txBufFromBLEtoUSB[5]);
				BLE_DATA = 0;
			}
			else
			{
				
				GPIOA->ODR ^= 1<<5;
//				write_mreg32( USB_EPn_CTRL(EPIN), 0x80);
				keyBoard_ctrl(0x00,0x00,0x0,0x00,0x00,0x00,0x00);
			}
	  }
		
		
#endif
	}	
}

#endif

