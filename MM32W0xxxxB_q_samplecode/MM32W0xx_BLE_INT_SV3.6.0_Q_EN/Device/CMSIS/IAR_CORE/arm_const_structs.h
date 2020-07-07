/**
******************************************************************************
* @file     arm_const_structs.h
* @author   AE team
* @version  V1.1.0
* @date     10/04/2019
* @brief    This file has constant structs that are initialized for
*           user convenience.  For example, some can be given as
*           arguments to the arm_cfft_f32() function.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

#ifndef _ARM_CONST_STRUCTS_H
#define _ARM_CONST_STRUCTS_H

#include "arm_math.h"
#include "arm_common_tables.h"

const arm_cfft_instance_f32 arm_cfft_sR_f32_len16 = {
    16, twiddleCoef_16, armBitRevIndexTable16, ARMBITREVINDEXTABLE__16_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len32 = {
    32, twiddleCoef_32, armBitRevIndexTable32, ARMBITREVINDEXTABLE__32_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len64 = {
    64, twiddleCoef_64, armBitRevIndexTable64, ARMBITREVINDEXTABLE__64_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len128 = {
    128, twiddleCoef_128, armBitRevIndexTable128, ARMBITREVINDEXTABLE_128_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len256 = {
    256, twiddleCoef_256, armBitRevIndexTable256, ARMBITREVINDEXTABLE_256_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len512 = {
    512, twiddleCoef_512, armBitRevIndexTable512, ARMBITREVINDEXTABLE_512_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len1024 = {
    1024, twiddleCoef_1024, armBitRevIndexTable1024, ARMBITREVINDEXTABLE1024_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len2048 = {
    2048, twiddleCoef_2048, armBitRevIndexTable2048, ARMBITREVINDEXTABLE2048_TABLE_LENGTH
};

const arm_cfft_instance_f32 arm_cfft_sR_f32_len4096 = {
    4096, twiddleCoef_4096, armBitRevIndexTable4096, ARMBITREVINDEXTABLE4096_TABLE_LENGTH
};

#endif

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

