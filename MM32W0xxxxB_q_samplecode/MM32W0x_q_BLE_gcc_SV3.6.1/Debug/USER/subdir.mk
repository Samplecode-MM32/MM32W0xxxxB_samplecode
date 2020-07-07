################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/main.c 

OBJS += \
./USER/main.o 

C_DEPS += \
./USER/main.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_UART -DUSE_AT_CMD -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/CMSIS" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/CMSIS/GCC_CORE" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Include" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Source" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/uart" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


