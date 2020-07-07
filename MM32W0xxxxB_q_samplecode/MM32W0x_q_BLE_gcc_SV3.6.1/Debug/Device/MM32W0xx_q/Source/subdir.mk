################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device/MM32W0xx_q/Source/system_MM32W0xx_q.c 

S_UPPER_SRCS += \
../Device/MM32W0xx_q/Source/startup_MM32_M0_q_GCC.S 

OBJS += \
./Device/MM32W0xx_q/Source/startup_MM32_M0_q_GCC.o \
./Device/MM32W0xx_q/Source/system_MM32W0xx_q.o 

S_UPPER_DEPS += \
./Device/MM32W0xx_q/Source/startup_MM32_M0_q_GCC.d 

C_DEPS += \
./Device/MM32W0xx_q/Source/system_MM32W0xx_q.d 


# Each subdirectory must supply rules for building sources it contributes
Device/MM32W0xx_q/Source/%.o: ../Device/MM32W0xx_q/Source/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/CMSIS/GCC_CORE" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Include" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Source" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/uart" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Device/MM32W0xx_q/Source/%.o: ../Device/MM32W0xx_q/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_UART -DUSE_AT_CMD -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/CMSIS" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/CMSIS/GCC_CORE" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/HAL_lib/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Include" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/Device/MM32W0xx_q/Source" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/APP" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/AT_CMD" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/CALLBACK" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IIC" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/IRQ" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/LED_MESH" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/RCC_MCU" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/HARDWARE/SPI" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SRC_LIB/inc" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/delay" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/sys" -I"/home/neomissing/eclipse-workspace/MM32W0x_q/SYSTEM/uart" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


