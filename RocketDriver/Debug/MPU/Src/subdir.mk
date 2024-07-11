################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MPU/Src/MPU6050.c 

OBJS += \
./MPU/Src/MPU6050.o 

C_DEPS += \
./MPU/Src/MPU6050.d 


# Each subdirectory must supply rules for building sources it contributes
MPU/Src/%.o MPU/Src/%.su MPU/Src/%.cyclo: ../MPU/Src/%.c MPU/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../BMP/Src -I../BMP/Inc -I../MPU/Src -I../MPU/Inc -I../GPS/Inc -I../GPS/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MPU-2f-Src

clean-MPU-2f-Src:
	-$(RM) ./MPU/Src/MPU6050.cyclo ./MPU/Src/MPU6050.d ./MPU/Src/MPU6050.o ./MPU/Src/MPU6050.su

.PHONY: clean-MPU-2f-Src

