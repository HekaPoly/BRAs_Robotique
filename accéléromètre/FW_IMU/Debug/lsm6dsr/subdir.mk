################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lsm6dsr/lsm6dsr.c \
../lsm6dsr/lsm6dsr_read_data.c 

OBJS += \
./lsm6dsr/lsm6dsr.o \
./lsm6dsr/lsm6dsr_read_data.o 

C_DEPS += \
./lsm6dsr/lsm6dsr.d \
./lsm6dsr/lsm6dsr_read_data.d 


# Each subdirectory must supply rules for building sources it contributes
lsm6dsr/%.o lsm6dsr/%.su lsm6dsr/%.cyclo: ../lsm6dsr/%.c lsm6dsr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lsm6dsr

clean-lsm6dsr:
	-$(RM) ./lsm6dsr/lsm6dsr.cyclo ./lsm6dsr/lsm6dsr.d ./lsm6dsr/lsm6dsr.o ./lsm6dsr/lsm6dsr.su ./lsm6dsr/lsm6dsr_read_data.cyclo ./lsm6dsr/lsm6dsr_read_data.d ./lsm6dsr/lsm6dsr_read_data.o ./lsm6dsr/lsm6dsr_read_data.su

.PHONY: clean-lsm6dsr

