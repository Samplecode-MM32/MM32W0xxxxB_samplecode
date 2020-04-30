/**************************************************************************//**
* @file HAL_device.h
* @brief CMSIS Cortex-M Peripheral Access Layer for MindMotion
*        microcontroller devices
*
* This is a convenience header file for defining the part number on the
* build command line, instead of specifying the part specific header file.
*
* Example: Add "MM32W0xx_s" to your build options, to define part
*          Add "#include "HAL_device.h" to your source files
*
*
* @version 2.0.0
*
*
*****************************************************************************/

#ifndef __HAL_device_H
#define __HAL_device_H


#define  MM32W0xx

#if defined(MM32W0xx)

#include "MM32W0xx.h"

#else
#error "HAL_device.h: PART NUMBER undefined"
#endif
#endif /* __HAL_device_H */
/*-------------------------(C) COPYRIGHT 2016 MindMotion ----------------------*/
