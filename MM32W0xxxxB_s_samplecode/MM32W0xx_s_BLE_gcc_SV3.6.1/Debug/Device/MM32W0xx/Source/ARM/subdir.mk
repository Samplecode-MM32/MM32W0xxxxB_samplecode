################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Device/MM32W0xx/Source/ARM/startup_MM32_M0_S_GCC.S 

OBJS += \
./Device/MM32W0xx/Source/ARM/startup_MM32_M0_S_GCC.o 

S_UPPER_DEPS += \
./Device/MM32W0xx/Source/ARM/startup_MM32_M0_S_GCC.d 


# Each subdirectory must supply rules for building sources it contributes
Device/MM32W0xx/Source/ARM/%.o: ../Device/MM32W0xx/Source/ARM/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/CMSIS" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Include" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Source/ARM" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IWDG" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/uart" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


