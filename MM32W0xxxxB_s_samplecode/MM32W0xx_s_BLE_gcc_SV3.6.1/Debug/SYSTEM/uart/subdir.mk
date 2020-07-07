################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SYSTEM/uart/uart.c 

OBJS += \
./SYSTEM/uart/uart.o 

C_DEPS += \
./SYSTEM/uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
SYSTEM/uart/%.o: ../SYSTEM/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_UART -DUSE_AT_CMD -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/CMSIS" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Include" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Source" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Source/ARM" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IWDG" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/uart" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


