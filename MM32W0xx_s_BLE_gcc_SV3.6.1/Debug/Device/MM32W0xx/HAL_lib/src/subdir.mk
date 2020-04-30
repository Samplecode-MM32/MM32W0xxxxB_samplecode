################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device/MM32W0xx/HAL_lib/src/HAL_adc.c \
../Device/MM32W0xx/HAL_lib/src/HAL_aes.c \
../Device/MM32W0xx/HAL_lib/src/HAL_bkp.c \
../Device/MM32W0xx/HAL_lib/src/HAL_can.c \
../Device/MM32W0xx/HAL_lib/src/HAL_comp.c \
../Device/MM32W0xx/HAL_lib/src/HAL_dma.c \
../Device/MM32W0xx/HAL_lib/src/HAL_exti.c \
../Device/MM32W0xx/HAL_lib/src/HAL_flash.c \
../Device/MM32W0xx/HAL_lib/src/HAL_gpio.c \
../Device/MM32W0xx/HAL_lib/src/HAL_i2c.c \
../Device/MM32W0xx/HAL_lib/src/HAL_iwdg.c \
../Device/MM32W0xx/HAL_lib/src/HAL_memprotect.c \
../Device/MM32W0xx/HAL_lib/src/HAL_misc.c \
../Device/MM32W0xx/HAL_lib/src/HAL_pwr.c \
../Device/MM32W0xx/HAL_lib/src/HAL_rcc.c \
../Device/MM32W0xx/HAL_lib/src/HAL_spi.c \
../Device/MM32W0xx/HAL_lib/src/HAL_syscfg.c \
../Device/MM32W0xx/HAL_lib/src/HAL_tim.c \
../Device/MM32W0xx/HAL_lib/src/HAL_uart.c \
../Device/MM32W0xx/HAL_lib/src/HAL_wwdg.c 

OBJS += \
./Device/MM32W0xx/HAL_lib/src/HAL_adc.o \
./Device/MM32W0xx/HAL_lib/src/HAL_aes.o \
./Device/MM32W0xx/HAL_lib/src/HAL_bkp.o \
./Device/MM32W0xx/HAL_lib/src/HAL_can.o \
./Device/MM32W0xx/HAL_lib/src/HAL_comp.o \
./Device/MM32W0xx/HAL_lib/src/HAL_dma.o \
./Device/MM32W0xx/HAL_lib/src/HAL_exti.o \
./Device/MM32W0xx/HAL_lib/src/HAL_flash.o \
./Device/MM32W0xx/HAL_lib/src/HAL_gpio.o \
./Device/MM32W0xx/HAL_lib/src/HAL_i2c.o \
./Device/MM32W0xx/HAL_lib/src/HAL_iwdg.o \
./Device/MM32W0xx/HAL_lib/src/HAL_memprotect.o \
./Device/MM32W0xx/HAL_lib/src/HAL_misc.o \
./Device/MM32W0xx/HAL_lib/src/HAL_pwr.o \
./Device/MM32W0xx/HAL_lib/src/HAL_rcc.o \
./Device/MM32W0xx/HAL_lib/src/HAL_spi.o \
./Device/MM32W0xx/HAL_lib/src/HAL_syscfg.o \
./Device/MM32W0xx/HAL_lib/src/HAL_tim.o \
./Device/MM32W0xx/HAL_lib/src/HAL_uart.o \
./Device/MM32W0xx/HAL_lib/src/HAL_wwdg.o 

C_DEPS += \
./Device/MM32W0xx/HAL_lib/src/HAL_adc.d \
./Device/MM32W0xx/HAL_lib/src/HAL_aes.d \
./Device/MM32W0xx/HAL_lib/src/HAL_bkp.d \
./Device/MM32W0xx/HAL_lib/src/HAL_can.d \
./Device/MM32W0xx/HAL_lib/src/HAL_comp.d \
./Device/MM32W0xx/HAL_lib/src/HAL_dma.d \
./Device/MM32W0xx/HAL_lib/src/HAL_exti.d \
./Device/MM32W0xx/HAL_lib/src/HAL_flash.d \
./Device/MM32W0xx/HAL_lib/src/HAL_gpio.d \
./Device/MM32W0xx/HAL_lib/src/HAL_i2c.d \
./Device/MM32W0xx/HAL_lib/src/HAL_iwdg.d \
./Device/MM32W0xx/HAL_lib/src/HAL_memprotect.d \
./Device/MM32W0xx/HAL_lib/src/HAL_misc.d \
./Device/MM32W0xx/HAL_lib/src/HAL_pwr.d \
./Device/MM32W0xx/HAL_lib/src/HAL_rcc.d \
./Device/MM32W0xx/HAL_lib/src/HAL_spi.d \
./Device/MM32W0xx/HAL_lib/src/HAL_syscfg.d \
./Device/MM32W0xx/HAL_lib/src/HAL_tim.d \
./Device/MM32W0xx/HAL_lib/src/HAL_uart.d \
./Device/MM32W0xx/HAL_lib/src/HAL_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Device/MM32W0xx/HAL_lib/src/%.o: ../Device/MM32W0xx/HAL_lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_UART -DUSE_AT_CMD -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/CMSIS" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Include" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Source" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/Device/MM32W0xx/Source/ARM" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/IWDG" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0xx_s_BLE_gcc_SV3.6.1/SYSTEM/uart" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


