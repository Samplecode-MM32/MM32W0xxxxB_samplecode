#ifndef __LED_MESH_H__
#define __LED_MESH_H__

#include "HAL_conf.h"
#include "HAL_device.h"
#include "mg_api.h"
extern void Led_getInfo(unsigned char* data);
void PWM_Init(void);
void UpdateLEDValueAll(void);
#endif