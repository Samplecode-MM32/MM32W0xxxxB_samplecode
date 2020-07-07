#ifndef __LED_MESH_H__
#define __LED_MESH_H__

#include "HAL_conf.h"
#include "HAL_device.h"
#include "mg_api.h"
extern void Led_getInfo(unsigned char *data);
void PWM_Init(void);
void UpdateLEDValueAll(void);
void TIM3_PWM_Init(u16 arr, u16 psc);
#endif
