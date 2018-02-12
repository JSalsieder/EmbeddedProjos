################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AT28C256.c \
../src/DMA.c \
../src/DS75176B.c \
../src/Gpio.c \
../src/Timers.c \
../src/delay.c \
../src/encoder.c \
../src/error.c \
../src/keypad.c \
../src/lcd.c \
../src/main.c \
../src/syscalls.c \
../src/uart1.c \
../src/uart_driver.c 

OBJS += \
./src/AT28C256.o \
./src/DMA.o \
./src/DS75176B.o \
./src/Gpio.o \
./src/Timers.o \
./src/delay.o \
./src/encoder.o \
./src/error.o \
./src/keypad.o \
./src/lcd.o \
./src/main.o \
./src/syscalls.o \
./src/uart1.o \
./src/uart_driver.o 

C_DEPS += \
./src/AT28C256.d \
./src/DMA.d \
./src/DS75176B.d \
./src/Gpio.d \
./src/Timers.d \
./src/delay.d \
./src/encoder.d \
./src/error.d \
./src/keypad.d \
./src/lcd.d \
./src/main.d \
./src/syscalls.d \
./src/uart1.d \
./src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F4 -DSTM32 -DDEBUG -I"F:/School/2_Sophomore/Winter/Embedded 2/Workspace/Lab8[Salsieder]/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


