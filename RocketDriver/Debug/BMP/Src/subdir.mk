################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BMP/Src/BMP280.c 

OBJS += \
./BMP/Src/BMP280.o 

C_DEPS += \
./BMP/Src/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
BMP/Src/%.o BMP/Src/%.su BMP/Src/%.cyclo: ../BMP/Src/%.c BMP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../BMP/Src -I../BMP/Inc -I../MPU/Src -I../MPU/Inc -I../GPS/Inc -I../GPS/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BMP-2f-Src

clean-BMP-2f-Src:
	-$(RM) ./BMP/Src/BMP280.cyclo ./BMP/Src/BMP280.d ./BMP/Src/BMP280.o ./BMP/Src/BMP280.su

.PHONY: clean-BMP-2f-Src

