/*
    Copyright (c) 2017 Macrogiga Electronics Co., Ltd.

    Permission is hereby granted, free of charge, to any person 
    obtaining a copy of this software and associated documentation 
    files (the "Software"), to deal in the Software without 
    restriction, including without limitation the rights to use, copy, 
    modify, merge, publish, distribute, sublicense, and/or sell copies 
    of the Software, and to permit persons to whom the Software is 
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be 
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/

#ifndef _MG_API_H_
#define _MG_API_H_

//TX power
#define TXPWR_0DBM 0x43
#define TXPWR_3DBM 0x48


///////////////////////////lib provided APIs//////////////////////////////////////

//Function: radio_initBle
//Parameters: txpwr - input, txpower;   addr - output, BLE device address
//return: None
void radio_initBle(unsigned char txpwr, unsigned char** addr/*out*/);  //init ble mode, should be called first after spi initialization

//Function: ble_run
//Parameters: interv_adv - advertise packet interval, unit 0.625ms
//return: None
//Remarks: never reurn!!!
void ble_run(unsigned short interv_adv);

//Function: ble_set_adv_data
//Parameters: adv - advertise packet payload; len - payload len
//return: None
void ble_set_adv_data(unsigned char* adv, unsigned char len);

//Function: ble_set_adv_rsp_data
//Parameters: rsp - advertise response payload; len - payload len
//return: None
void ble_set_adv_rsp_data(unsigned char* rsp, unsigned char len);

//Function: ble_set_name
//this function IS available when using default scan response data
//Parameters: name - device name; len - name len
//return: None
void ble_set_name(unsigned char* name,unsigned char len);

//Function: ble_set_interval
//this function IS available when using default scan response data
//Parameters: interval - advertisement interval, unit 0.625ms
//return: None
void ble_set_interval(unsigned short interval);

//Function: ble_set_adv_enableFlag
//this function is to enable/disable ble adv
//Parameters: sEnableFlag - 0 to disable adv, 1 to enable adv
//return: None
void ble_set_adv_enableFlag(char sEnableFlag);

//Function: ble_disconnect
//this function is to disconnected the ble connection
//Parameters: none
//return: None
void ble_disconnect(void);

unsigned char* GetFirmwareInfo(void); //such as "FVxx.2.0.2mmx"
unsigned char* get_ble_version(void); //such as "MG_BLE_LIB_V1.0"


void att_notFd(unsigned char pdu_type, unsigned char attOpcode, unsigned short attHd );
void att_server_rdByGrTypeRspDeviceInfo(unsigned char pdu_type);
void att_server_rdByGrTypeRspPrimaryService(unsigned char pdu_type, unsigned short start_hd, unsigned short end_hd, unsigned char*uuid, unsigned char uuidlen);
void att_server_rd( unsigned char pdu_type, unsigned char attOpcode, unsigned short att_hd, unsigned char* attValue, unsigned char datalen );


void ser_write_rsp_pkt(unsigned char pdu_type);


unsigned char sconn_notifydata(unsigned char* data, unsigned char len);//returns data size has been sent, ******* user's safe API *********


////////////////////////////app implemented/porting functions//////////////////////////////
//void gatt_user_send_notify_data_callback(void)
//void ser_prepare_write(unsigned short handle, unsigned char* attValue, unsigned short attValueLen, unsigned short att_offset);
//void ser_execute_write(void);

//unsigned char* getDeviceInfoData(unsigned char* len);

//void att_server_rdByGrType( unsigned char pdu_type, unsigned char attOpcode, unsigned short st_hd, unsigned short end_hd, unsigned short att_type );
//void ser_write_rsp(unsigned char pdu_type/*reserved*/, unsigned char attOpcode/*reserved*/, 
//                   unsigned short att_hd, unsigned char* attValue/*app data pointer*/, unsigned char valueLen_w/*app data size*/);
//void server_rd_rsp(unsigned char attOpcode, unsigned short attHandle, unsigned char pdu_type);

//void ConnectStausUpdate(unsigned char IsConnectedFlag);

//unsigned char aes_encrypt_HW(unsigned char *painText128bitBE,unsigned char *key128bitBE); //porting api, returns zero means not supported


///////////////////////////test/debug APIs/////////////////////////////////
//Parameters: freq - input, 0~80, center frequency(2400+freq)MHz, txpwr - input, 0x20~0x4A, txpower
//return: None

void test_carrier(unsigned char freq, unsigned char txpwr);

void SetFixAdvChannel(unsigned char isFixCh37Flag);

void set_mg_ble_dbg_flag(unsigned char EnableFlag);

unsigned char* GetMgBleStateInfo(int* StateInfoSize/*Output*/);

#endif
