################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/LED/led.c 

OBJS += \
./HARDWARE/LED/led.o 

C_DEPS += \
./HARDWARE/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/LED/%.o: ../HARDWARE/LED/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I/home/neomissing/eclipse-workspace/MM32W0xx_s/SYSTEM/uart -I/home/neomissing/eclipse-workspace/MM32W0xx_s/SYSTEM/sys -I/home/neomissing/eclipse-workspace/MM32W0xx_s/SYSTEM/delay -I/home/neomissing/eclipse-workspace/MM32W0xx_s/HARDWARE/LED -I/home/neomissing/eclipse-workspace/MM32W0xx_s/Device/CMSIS -I/home/neomissing/eclipse-workspace/MM32W0xx_s/Device/MM32W0xx/HAL_lib/inc -I/home/neomissing/eclipse-workspace/MM32W0xx_s/Device/MM32W0xx/Include -I/home/neomissing/eclipse-workspace/MM32W0xx_s/Device/MM32W0xx/Source -I/home/neomissing/eclipse-workspace/MM32W0xx_s/Device/MM32W0xx/Source/ARM -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


