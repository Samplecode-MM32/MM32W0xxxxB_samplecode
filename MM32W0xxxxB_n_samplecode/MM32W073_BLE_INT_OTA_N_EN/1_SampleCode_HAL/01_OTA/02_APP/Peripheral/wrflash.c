#include "wrflash.h"
#include "delay.h"
#include "uart.h"

//////////////////////////////////////////////////////////////////////////////////
//103开发板
//FLASH 驱动代码
//////////////////////////////////////////////////////////////////////////////////

//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
u16 ONCHIP_FLASH_ReadHalfWord(u32 faddr)
{
  return *(vu16 *)faddr;
}
#if ONCHIP_FLASH_WREN //如果使能了写   
//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void ONCHIP_FLASH_Write_NoCheck(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
  u16 i;
  for (i = 0; i < NumToWrite; i++)
  {
    FLASH_ProgramHalfWord(WriteAddr, pBuffer[i]);
    WriteAddr += 2; //地址增加2.
  }
}
//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if ONCHIP_FLASH_SIZE<256
  #define ONCHIP_FLASH_SECTOR_SIZE 1024 //字节
#else
  #define ONCHIP_FLASH_SECTOR_SIZE  2048
#endif
u16 ONCHIP_FLASH_BUF[ONCHIP_FLASH_SECTOR_SIZE / 2]; //最多是2K字节
void ONCHIP_FLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
  u32 Secpos;    //扇区地址
  u16 Secoff;    //扇区内偏移地址(16位字计算)
  u16 Secremain; //扇区内剩余地址(16位字计算)
  u16 i;
  u32 Offaddr;   //去掉0X08000000后的地址
  if (WriteAddr < ONCHIP_FLASH_BASE || (WriteAddr >= (ONCHIP_FLASH_BASE + 1024 * ONCHIP_FLASH_SIZE)))return; //非法地址
  FLASH_Unlock();           //解锁
  Offaddr = WriteAddr - ONCHIP_FLASH_BASE; //实际偏移地址.
  Secpos = Offaddr / ONCHIP_FLASH_SECTOR_SIZE;  //扇区地址  0~127 for 103RBT6
  Secpos = (Offaddr % ONCHIP_FLASH_SECTOR_SIZE) / 2; //在扇区内的偏移(2个字节为基本单位.)
  Secremain = ONCHIP_FLASH_SECTOR_SIZE / 2 - Secpos; //扇区剩余空间大小
  if (NumToWrite <= Secremain)Secremain = NumToWrite; //不大于该扇区范围
  while (1)
  {
    ONCHIP_FLASH_Read(Secpos * ONCHIP_FLASH_SECTOR_SIZE + ONCHIP_FLASH_BASE, ONCHIP_FLASH_BUF, ONCHIP_FLASH_SECTOR_SIZE / 2); //读出整个扇区的内容
    for (i = 0; i < Secremain; i++) //校验数据
    {
      if (ONCHIP_FLASH_BUF[Secoff + i] != 0XFFFF)break; //需要擦除
    }
    if (i < Secremain) //需要擦除
    {
      FLASH_ErasePage(Secpos * ONCHIP_FLASH_SECTOR_SIZE + ONCHIP_FLASH_BASE); //擦除这个扇区
      for (i = 0; i < Secremain; i++) //复制
      {
        ONCHIP_FLASH_BUF[i + Secoff] = pBuffer[i];
      }
      ONCHIP_FLASH_Write_NoCheck(Secpos * ONCHIP_FLASH_SECTOR_SIZE + ONCHIP_FLASH_BASE, ONCHIP_FLASH_BUF, ONCHIP_FLASH_SECTOR_SIZE / 2); //写入整个扇区
    }
    else ONCHIP_FLASH_Write_NoCheck(WriteAddr, pBuffer, Secremain); //写已经擦除了的,直接写入扇区剩余区间.
    if (NumToWrite == Secremain)break; //写入结束了
    else//写入未结束
    {
      Secpos++;       //扇区地址增1
      Secoff = 0;     //偏移位置为0
      pBuffer += Secremain; //指针偏移
      WriteAddr = Secpos * ONCHIP_FLASH_SECTOR_SIZE + ONCHIP_FLASH_BASE; //WriteAddr+=secremain; //写地址偏移
      NumToWrite -= Secremain; //字节(16位)数递减
      if (NumToWrite > (ONCHIP_FLASH_SECTOR_SIZE / 2))Secremain = ONCHIP_FLASH_SECTOR_SIZE / 2; //下一个扇区还是写不完
      else Secremain = NumToWrite; //下一个扇区可以写完了
    }
  };
  FLASH_Lock();//上锁
}
#endif

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void ONCHIP_FLASH_Read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead)
{
  u16 i;
  for (i = 0; i < NumToRead; i++)
  {
    pBuffer[i] = ONCHIP_FLASH_ReadHalfWord(ReadAddr); //读取2个字节.
    ReadAddr += 2; //偏移2个字节.
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write(u32 WriteAddr, u16 WriteData)
{
  ONCHIP_FLASH_Write(WriteAddr, &WriteData, 1); //写入一个字
}
















