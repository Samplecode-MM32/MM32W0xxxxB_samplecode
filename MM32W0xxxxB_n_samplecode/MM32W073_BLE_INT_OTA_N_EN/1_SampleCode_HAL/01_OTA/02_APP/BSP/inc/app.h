#ifndef _MG_APP_H_
#define _MG_APP_H_
#include "HAL_device.h"
//#define u8 unsigned char
//#define u16 unsigned short
void CodeNvcRemap(void);
void IrqMcuGotoSleepAndWakeup(void);
void OtaSystemReboot(void);//porting api
void WriteFlashE2PROM(u8* data, u16 len, u32 pos, u8 flag);
#endif
