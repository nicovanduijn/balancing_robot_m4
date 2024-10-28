################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/main.c \
../Src/stm32mp1xx_hal_msp.c \
../Src/stm32mp1xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/gpio.o \
./Src/main.o \
./Src/stm32mp1xx_hal_msp.o \
./Src/stm32mp1xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/gpio.d \
./Src/main.d \
./Src/stm32mp1xx_hal_msp.d \
./Src/stm32mp1xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Fxx -c -I../Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32MP1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32mp1xx_hal_msp.cyclo ./Src/stm32mp1xx_hal_msp.d ./Src/stm32mp1xx_hal_msp.o ./Src/stm32mp1xx_hal_msp.su ./Src/stm32mp1xx_it.cyclo ./Src/stm32mp1xx_it.d ./Src/stm32mp1xx_it.o ./Src/stm32mp1xx_it.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

