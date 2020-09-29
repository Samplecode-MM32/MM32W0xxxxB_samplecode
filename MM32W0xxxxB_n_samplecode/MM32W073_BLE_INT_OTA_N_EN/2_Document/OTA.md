---
title: MM32W0 OTA简介
date: 2020-07-01 17:23:39
tags: [DFU, OTA]
categories: OTA
mathjax: true
---

&emsp;本文介绍OTA升级的详细内容。

---
## # 1.	DFU与OTA的关系及简介 ##
<p style="text-indent:2em">如何实现BLE OTA？什么叫DFU？什么叫OTA？DFU与OTA有什么联系呢？怎么保证升级的安全性？本文主要给大家介绍MM32W0xx_n系列的蓝牙OTA升级的基础知识，主要针对OTA升级的原理，分区的划分，代码的编写以及实验验证这几个方面给大家讲解。</p>
<p style="text-indent:2em">所谓DFU（Device Firmware Update），就是设备固件升级的意思，而OTA（Over The Air）空中下载技术是实现DFU的一种方式而已，准确说，OTA的全称应该是OTA DFU，即通过空中无线方式实现设备固件升级。只不过大家为了方便起见，直接用OTA来指代固件空中升级（有时候大家也将OTA称为FOTA，即Firmware OTA，这种称呼意思更明了一些）。所谓的DFU分为后台式DFU与非后台式DFU。所谓的手机与电脑的升级就是后台式DFU，后台式DFU又称为静默式DFU,在升级的时候新固件会在后台悄悄的下载，系统的软件在下载新固件的时候还是可以正常使用的，当固件下载完成以后系统会进入BootLoader模式，然后BootLoader会将新的固件写入到老固件的位置，将老的固件覆盖掉，非后台式的DFU在升级的时候，系统必须先进入BootLoader模式来下载固件，下载完成以后BootLoader来完成新固件的更新操作，在整个升级的过程中系统是不能正常使用的。</p>
<p style="text-indent:2em">DFU也分为双区DFU与单区DFU,双区与单区式新固件与老固件覆盖的两种方式，后台是必须采用双分区的形式，因为如果采用单区的形式会影响系统在固件下载过程中的正常使用，一般老的固件与新的固件各占一半，固件下载完成以后会进行软件的校验，校验完成以后进入BootLoader模式，然后将Bank_B的代码搬运到Bank_A区，单区DFU就是系统判断进入升级模式的时候进入BootLoader模式，然后BootLoader会擦出Bank_A的代码，当下载完成以后会进行校验，当校验完成以后启动应用程序，否则升级不成功需要重新升级。单分区DFU适用于flash比较紧张的情况。如果升级不成功很容易遇到变砖的情况。双区的DFU模式虽然会浪费内存空间，但是不会遇到变砖的情况，会给客户带来更好的用户体验。</p>
----
## 2.	OTA基础知识介绍 ##
### 2.1 	BootLoader与APP介绍 ###
**BootLoader**：所谓BootLoader就是烧录引导程序，他的作用就是在进行升级的时候对APP程序进行引导存放，通俗来讲就是把APP程序存放到指定的位置，然后来启动APP程序。<br/>

**APP**：用户需要执行的程序。使用BootLoader进行引导烧录到指定的位置并运行，让系统执行用户所需要的操作。<br/>
----
### 2.2 	FLASH分区 ###
<p style="text-indent:2em">MM32W0xx_n系列蓝牙的内存空间由64位宽的存储单元组成，既可存放代码又可以存放数据。主闪存块按128页（每页1K字节）或者32个扇区（每个扇区4K字节）分块，并在进行写保护的时候以扇区为单位进行设置。FLASH地址从0x08000000开始。</p> 
<table>
<tr>
    <td bgcolor=#7B68EE><center><font color=#FF69B4><b>第0页</b></font></center></td>
    <td>0X0800 0000 - 0X0800 03FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第1页</td>
    <td>0X0800 0400 - 0X0800 07FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第2页</td>
    <td>0X0800 0800 - 0X0800 0BFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第3页</td>
    <td>0X0800 0C00 - 0X0800 0FFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>63</td>
    <td>0X0800 FC00 - 0X0800FFFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>···</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第123页</td>
    <td>0x0801 EC00 - 0x0801 EFFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第124页</td>
    <td>0x0801 F000 - 0x0801 F3FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第125页</td>
    <td>0x0801 F400 - 0x0801 F7FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第126页</td>
    <td>0x0801 F800 - 0x0801 FBFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第127页</td>
    <td>0x0801 FC00 - 0x0801 FFFF</td>
	<td>1K</td>
</tr>
</table>
&emsp;**以上图的128KFLASH为例，将FLASH分为三个区：BootLoader区，Bank_A区，Bank_B区（程序备份区）具体的划分如下：**</p> 

**Bootloader区**</p> 
**08000000------08000FFF 	4kB**</p> 

<table>
<tr>
    <td bgcolor=#7B68EE><center><font color=#FF69B4><b>第0页</b></font></center></td>
    <td>0X0800 0000 - 0X0800 03FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第1页</td>
    <td>0X0800 0400 - 0X0800 07FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第2页</td>
    <td>0X0800 0800 - 0X0800 0BFF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第3页</td>
    <td>0X0800 0C00 - 0X0800 0FFF</td>
	<td>1K</td>
</tr>
</table>
**Bank_A区**</p> 
**08001000------0800FFFF  60KB**</p> 

<table>
<tr>
    <td bgcolor=#7B68EE><center><font color=#FF69B4><b>第4页</b></font></center></td>
    <td>0X0800 1000 - 0X0800 13FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第...页</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第...页</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第63页</td>
    <td>0X0800 FC00 - 0X0800FFFF</td>
	<td>1K</td>
</tr>
</table>
**Bank_B区**</p> 
**08010000------0801EFFF  60KB**</p> 
<table>
<tr>
    <td bgcolor=#7B68EE><center><font color=#FF69B4><b>第64页</b></font></center></td>
    <td>0X0801 0000- 0X080103FF</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第...页</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第...页</td>
    <td>...</td>
	<td>1K</td>
</tr>
<tr>
    <td bgcolor=#7B68EE>第123页</td>
    <td>0x0801 EC00 - 0x0801 EFFF</td>
	<td>1K</td>
</tr>
</table>
----
### 2.3 	程序执行流程 ###

<p style="text-indent:2em">程序会先执行BootLoader程序，程序会去检查Bank_B是否存在代码，如果不存在则直接跳转到Bank_A的APP程序执行。</p>
<p style="text-indent:2em">在执行Bank_A区的程序过程中，因为APP与BootLoader这两个代码的中断向量表不同，所以在跳转到Bank_A区的APP的程序的时候，第一步就是需要更改程序的中断向量表，然后再去执行其他的应用程序。</p>
<p style="text-indent:2em">在程序中加入OTA升级的部分，然后进行OTA升级，手机端文件传输完毕以后会对系统进行重启然后进入BootLoader模式，在此模式下会对Bank_B区的代码进行检测，如果没有代码就跳转到Bank_A区执行APP程序，如果Bank_B区存在代码则对Bank_B区的代码进行相应的校验，校验成功就进行代码区的操作，将Bank_B区的代码复制到Bank_A，操作成功以后跳转到Bank_A执行相应的APP程序。</p>
## 3.	代码实现 ##
### 3.1 	BootLoader的 编写 ###
<p style="text-indent:2em">MM32W0xx_n的第一个地址的前两个字节代表需要升级的代码的大小，第三第四个字节为CRC校验的数值，升级的过程中，手机端先与蓝牙数据通信，数据通信完毕以后蓝牙会重新启动然后进入BootLoader模式，在进入BootLoader模式以后会判断B区是否存在代码，如果存在代码会对代码的大小进行判断并进行CRC校验，校验完成以后会将B区的代码复制到A区，然后再将B区的代码清除并跳转到APP区。</p>


<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: CheckCodeBank
**@brief    This function is Check if there is code in CODE area and verify
**
**@param    BANK_ID_Flag    :  Code area selection
**
**@return   0/1				:  CRC check returns 1 correctly, otherwise returns 0
********************************************************************************************************/
int CheckCodeBank(int BANK_ID_Flag)
{
    uint16_t Size,Crc = 0;
    uint8_t* BankAddr = (uint8_t*)(BANK_BASE + BANK_A_OFFSET); //BANKA
    if(BANK_ID_Flag == BANK_ID_B)
    {
        BankAddr = (uint8_t*)(BANK_BASE + BANK_B_OFFSET);        
    }
    Size = BankAddr[1]; Size <<= 8;  Size |= BankAddr[0];        
    if(Size > BANK_B_SIZE_KB_MAX * 1024 - 16)
    {
        Size = BANK_B_SIZE_KB_MAX * 1024 - 16;
    }
    Crc = CRC16(BankAddr+16,(int)Size,Crc);
    if(((Crc & 0xFF) != BankAddr[2]) || (((Crc>>8) & 0xFF) != BankAddr[3]))
    {
        return 0; //CRC failed
    }
    return 1; //OK
}
</pre> 
<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: CopyCode_B_to_A
**@brief    This function is Copy the code of area B to area A
**
**@param    None.
**
**@return   None.
********************************************************************************************************/
void CopyCode_B_to_A(void)
{ 
    uint16_t i,Size;
    uint32_t BankAddrA = BANK_BASE + BANK_A_OFFSET,Data;
    unsigned char* addr = (unsigned char*)(BANK_BASE + BANK_B_OFFSET);
    Size = addr[1]; Size <<= 8;  Size |= addr[0];
    Size >>= 2;
    Size += 4;//header 16 bytes
    if(Size > BANK_B_SIZE_KB_MAX * 256)
    {
        Size = BANK_B_SIZE_KB_MAX * 256; 
    }
    ClearBank(BANK_ID_A);
    FLASH_Unlock();
    for(i = 0 ; i < Size ; i ++)
    {
        Data  = addr[3]; Data <<= 8;
        Data |= addr[2]; Data <<= 8;
        Data |= addr[1]; Data <<= 8;
        Data |= addr[0];
        FLASH_ProgramWord(BankAddrA, Data);
        BankAddrA += 4;
        addr += 4;
    }
    FLASH_Lock();
    if(!CheckCodeBank(BANK_ID_A))
	{

    }
}
</pre> 


<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: Jump_App
**@brief    This function is a jump function, jump from BOOT to APP.
**
**@param    None.
**
**@return   None.
********************************************************************************************************/
void Jump_App()
{
    JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
    /* Jump to application */
    Jump_To_Application();
}
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    if(CheckCodeBank(BANK_ID_B))
    {
        CopyCode_B_to_A(); 
    }
    ClearBank(BANK_ID_B);
    Jump_App();
    while (1)
    {
    }
}
</pre> 

### 3.2 	APP代码实现 ###

给自己的蓝牙工程添加OTA功能具体的操作如下：
#### 3.2.1 	在蓝牙工程中添加以下几个函数： ####
中断向量表重映射函数
<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: CodeNvcRemap
**@brief    APPLICATION ADDRESS remapping function, adjust the starting address of APP
**
**@param    None.
**
**@return   None.
********************************************************************************************************/
void CodeNvcRemap(void)
{
    uint32_t i = 0;
    for(i = 0; i < 48; i++) {
        *((uint32_t*)(0x20000000 +  (i << 2))) = *(__IO uint32_t*)(APPLICATION_ADDRESS + (i << 2));
    }
    RCC->APB2ENR |= 0x00000001;
    SYSCFG->CFGR |= 0x03;
}
u32 GetOtaAddr(void)
{
    return FLASH_E2PROM_ADDR_OTA;
}
</pre> 

<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: GetCodeAddr
**@brief    Get the address where the code is written to flash
**
**@param    None.
**
**@return   None.
********************************************************************************************************/

u32 GetCodeAddr(void)
{
    return (FLASH_E2PROM_ADDR_BASE + FLASH_BOOT_ROM_SIZE);
}
</pre> 

<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: WriteFlashE2PROM
**@brief    MM32 write flash function, write data to the corresponding flash area
**
**@param    data    :  Storage address of data written to flash
**
**@param    len     :  Storage length of data written to flash
**
**@param    pos     :  flash storage data address
**
**@param    flag    :  flash unlock flag
**
**@return   None.
********************************************************************************************************/
void WriteFlashE2PROM(u8* data, u16 len, u32 pos, u8 flag) //4 bytes aligned
{
    u32 t;
    if(flag)FLASH_Unlock();
    while(len >= 4) {
        t = data[3]; t <<= 8;
        t |= data[2]; t <<= 8;
        t |= data[1]; t <<= 8;
        t |= data[0];
        FLASH_ProgramWord(pos, t);
        pos += 4;
        len -= 4;
        data += 4;
    }
    if(flag)FLASH_Lock();
}
</pre> 

<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: OtaSystemReboot
**@brief    MM32 interrupt reset function.
**
**@param    None.
**
**@return   None.
********************************************************************************************************/
void OtaSystemReboot(void)//porting api
{
    NVIC_SystemReset();
}
</pre> 
#### 3.2.2 	给自己的蓝牙添加相应的特征服务值 ####
<pre class="prettyprint lang-javascript">  
const BLE_CHAR AttCharList[] =
{
// ======  gatt =====  Do NOT Change!!
  {TYPE_CHAR, 0x03, ATT_CHAR_PROP_RD, 0x04, 0, 0x00, 0x2a, UUID16_FORMAT}, //name
  //05-06 reserved
// ======  device info =====    Do NOT Change if using the default!!!
  {TYPE_CHAR, 0x08, ATT_CHAR_PROP_RD, 0x09, 0, 0x29, 0x2a, UUID16_FORMAT}, //manufacture
  {TYPE_CHAR, 0x0a, ATT_CHAR_PROP_RD, 0x0b, 0, 0x26, 0x2a, UUID16_FORMAT}, //firmware version
  {TYPE_CHAR, 0x0e, ATT_CHAR_PROP_RD, 0x0f, 0, 0x28, 0x2a, UUID16_FORMAT}, //sw version
// ======  User service or other services added here =====  User defined
  {TYPE_CHAR, 0x11, ATT_CHAR_PROP_NTF,                               0x12, 0, 0, 0, 1/*uuid128-idx1*/ }, //RxNotify
  {TYPE_CFG, 0x13, ATT_CHAR_PROP_RD | ATT_CHAR_PROP_W}, //cfg
  {TYPE_CHAR, 0x14, ATT_CHAR_PROP_W | ATT_CHAR_PROP_W_NORSP,         0x15, 0, 0, 0, 2/*uuid128-idx2*/ }, //Tx
  {TYPE_CHAR, 0x17, ATT_CHAR_PROP_W | ATT_CHAR_PROP_RD,              0x18, 0, 0, 0, 3/*uuid128-idx3*/ }, //BaudRate
  {TYPE_INFO, 0x19, ATT_CHAR_PROP_RD}, //description,"BaudRate"
// ======  User service or other services added here ===== OTA
  {TYPE_CHAR, 0x1B, ATT_CHAR_PROP_W_NORSP | ATT_CHAR_PROP_RD,        0x1C, 0, 0, 0, 7/*uuid128-idx3*/ }, //OTA
  {TYPE_INFO, 0x1D, ATT_CHAR_PROP_RD}, //description,"MM32 OTA"
};

</pre> 
#### 3.2.3 	OTA与UUID128匹配 ####
<pre class="prettyprint lang-javascript">  
const BLE_UUID128 AttUuid128List[] =
{
  {0x9e, 0xca, 0x0dc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 1, 0, 0x40, 0x6e}, //idx0,little endian, service uuid
  {0x9e, 0xca, 0x0dc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 3, 0, 0x40, 0x6e}, //idx1,little endian, RxNotify
  {0x9e, 0xca, 0x0dc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 2, 0, 0x40, 0x6e}, //idx2,little endian, Tx
  {0x9e, 0xca, 0x0dc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 4, 0, 0x40, 0x6e}, //idx3,little endian, BaudRate
  {0x10, 0x19, 0x0d, 0xc, 0xb, 0xa, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, //idx4,little endian, service uuid
  {0x11, 0x19, 0x0d, 0xc, 0xb, 0xa, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, //idx5,little endian, character status uuid
  {0x12, 0x19, 0x0d, 0xc, 0xb, 0xa, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, //idx6,little endian, character cmd uuid
  {0x13, 0x19, 0x0d, 0xc, 0xb, 0xa, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, //idx7,little endian, character OTA uuid
};

</pre> 
#### 3.2.4 	给蓝牙添加相应的读写操作 ####
<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: ser_write_rsp
**@brief    This function is the reply function after the BLE device receives the write request
**
**@param    pdu_type  :  PDU type parameters. Directly reference the corresponding parameter
**          in the callback function att_server_rdByGrType
**@param    attOpcode :  corresponding value of attOpcode operation
**
**@param    att_hd    :  BLE service handle value
**
**@param    attValue  :  Received data
**
**@param    valueLen_w :  Data length
**
**@return   None.
********************************************************************************************************/
void ser_write_rsp(u8 pdu_type/*reserved*/, u8 attOpcode/*reserved*/,
                   u16 att_hd, u8 *attValue/*app data pointer*/, u8 valueLen_w/*app data size*/)
{
  switch (att_hd)
  {
	case 0x1C://OTA
	OTA_Proc(attValue, valueLen_w);
	break;
  case 0x18://BaudRate
    BaudRate = ((*(attValue + 2)) << 16) | ((*(attValue + 1)) << 8) | (*attValue);
    ser_write_rsp_pkt(pdu_type);
    ChangeBaudRate();
    break;
  case 0x15://Tx
#ifdef USE_UART
#ifdef USE_AT_CMD
    moduleOutData("IND:DATA", 8);
    moduleOutData(&valueLen_w, 1);
    moduleOutData("=", 1);
#endif
    moduleOutData(attValue, valueLen_w);
#endif
  case 0x12://cmd
  case 0x13://cfg
    ser_write_rsp_pkt(pdu_type);  /*if the related character has the property of WRITE(with response) or TYPE_CFG, one MUST invoke this func*/
    break;
  default:
    att_notFd(pdu_type, attOpcode, att_hd);    /*the default response, also for the purpose of error robust */
    break;
  }
}

</pre> 

<pre class="prettyprint lang-javascript">  
/********************************************************************************************************
**function: server_rd_rsp
**@brief    This function is a write function for BLE devices
**
**@param    handle     :  BLE service handle value
**
**@param    attValue   :  Received data
**
**@param    valueLen_w :  Data length
**
**@param    att_offset :  Address offset
**
**@return   None.
********************************************************************************************************/
void server_rd_rsp(u8 attOpcode, u16 attHandle, u8 pdu_type)
{
  u8 tab[3];
  switch (attHandle) //hard code
  {
  case 0x04: //MANU_INFO
    //att_server_rd( pdu_type, attOpcode, attHandle, (u8*)(MANU_INFO), sizeof(MANU_INFO)-1);
    att_server_rd(pdu_type, attOpcode, attHandle, "MINDMOTION", 10); //ble lib build version
    break;
  case 0x09: //MANU_INFO
    //att_server_rd( pdu_type, attOpcode, attHandle, (u8*)(MANU_INFO), sizeof(MANU_INFO)-1);
		//ble lib build version
    att_server_rd(pdu_type, attOpcode, attHandle, get_ble_version(), strlen((const char *)get_ble_version())); 
    break;
  case 0x0b: //FIRMWARE_INFO
  {
    //do NOT modify this code!!!
    att_server_rd(pdu_type, attOpcode, attHandle, GetFirmwareInfo(), strlen((const char *)GetFirmwareInfo()));
    break;
  }
  case 0x0f://SOFTWARE_INFO
    att_server_rd(pdu_type, attOpcode, attHandle, (u8 *)(SOFTWARE_INFO), sizeof(SOFTWARE_INFO) - 1);
    break;
  case 0x13://cfg
  {
    u8 t[2] = {0, 0};
    att_server_rd(pdu_type, attOpcode, attHandle, t, 2);
  }
  break;
  case 0x18://BaudRate
    tab[0] = (BaudRate & 0xff0000) >> 16;
    tab[1] = (BaudRate & 0xff00) >> 8;
    tab[2] = BaudRate;
    att_server_rd(pdu_type, attOpcode, attHandle, tab, 3);
    break;
  case 0x19: //description
#define MG_BaudRate "BaudRate"
    att_server_rd(pdu_type, attOpcode, attHandle, (u8 *)(MG_BaudRate), sizeof(MG_BaudRate) - 1);
    break;
	case 0x1D: //ota description
#define MM_OTA "MM OTA"
  att_server_rd( pdu_type, attOpcode, attHandle, (u8*)(MM_OTA), sizeof(MM_OTA) - 1);
  break;
  default:
    att_notFd(pdu_type, attOpcode, attHandle);  /*the default response, also for the purpose of error robust */
    break;
  }
}

</pre> 
#### 3.2.5 	修改中断向量表 ####
<p style="text-indent:2em">在主函数刚开始的时候调用CodeNvcRemap()函数来进行中断向量表地址的映射。</p> 
<pre class="prettyprint lang-javascript"> 
int main(void)
{
  unsigned long temp = 0x800000;
  unsigned long i = 0;
  unsigned char *ft_val = (unsigned char *)(0x1FFFF804);
  unsigned char ft_value[2] = {0xc0, 0x12};
  while (temp--);
  CodeNvcRemap();
  SystemClk_HSEInit();
#ifdef USE_UART
#ifdef USE_AT_CMD
  SleepStop = 0x00;
#endif
#endif

#ifdef USE_UART
  uart_initwBaudRate();
#endif

  SysTick_Configuration();
  Write_Iwdg_ON(IWDG_Prescaler_32, 0x4E2); //1s
  SPIM_Init(SPI2,/*0x06*/0x06); //6Mhz
  IRQ_RF();
  SetBleIntRunningMode();
  radio_initBle(TXPWR_0DBM, &ble_mac_addr);
  SysTick_Count = 0;
	
  while (SysTick_Count < 5) {}; //delay at least 5ms between radio_initBle() and ble_run...

  if((*ft_val > 11) && (*ft_val < 27))
  {
    ft_value[1] = *ft_val;
    mg_activate(0x53);
    g_writeBuf(0x4, ft_value, 2);
    mg_activate(0x56);
  }

  ble_run_interrupt_start(160 * 2); //320*0.625=200 ms
  while (1)
  {
    /*************do sometging and sleep****************/
    Delay_ms(50);
    IrqMcuGotoSleepAndWakeup();
  }
}
</pre> 

#### 3.2.6 	修改FLASH的起始地址 ####
<p style="text-indent:2em">在MDK界面中进行flash地址以及SRAM的设置。</p> 
