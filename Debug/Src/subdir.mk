################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dic.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/dic.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/dic.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F051x8 -I"Z:/Satyajyoti Nanda/Documents/Purdue University/Semester6_Spring2018/ECE 36200/ece362_workspace/ARM_ASSEMBLY/Inc" -I"Z:/Satyajyoti Nanda/Documents/Purdue University/Semester6_Spring2018/ECE 36200/ece362_workspace/ARM_ASSEMBLY/Drivers/STM32F0xx_HAL_Driver/Inc" -I"Z:/Satyajyoti Nanda/Documents/Purdue University/Semester6_Spring2018/ECE 36200/ece362_workspace/ARM_ASSEMBLY/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"Z:/Satyajyoti Nanda/Documents/Purdue University/Semester6_Spring2018/ECE 36200/ece362_workspace/ARM_ASSEMBLY/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"Z:/Satyajyoti Nanda/Documents/Purdue University/Semester6_Spring2018/ECE 36200/ece362_workspace/ARM_ASSEMBLY/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


