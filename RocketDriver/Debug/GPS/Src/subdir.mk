################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPS/Src/GYNEO.c \
../GPS/Src/lwgps.c 

OBJS += \
./GPS/Src/GYNEO.o \
./GPS/Src/lwgps.o 

C_DEPS += \
./GPS/Src/GYNEO.d \
./GPS/Src/lwgps.d 


# Each subdirectory must supply rules for building sources it contributes
GPS/Src/%.o GPS/Src/%.su GPS/Src/%.cyclo: ../GPS/Src/%.c GPS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../BMP/Src -I../BMP/Inc -I../MPU/Src -I../MPU/Inc -I../GPS/Inc -I../GPS/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GPS-2f-Src

clean-GPS-2f-Src:
	-$(RM) ./GPS/Src/GYNEO.cyclo ./GPS/Src/GYNEO.d ./GPS/Src/GYNEO.o ./GPS/Src/GYNEO.su ./GPS/Src/lwgps.cyclo ./GPS/Src/lwgps.d ./GPS/Src/lwgps.o ./GPS/Src/lwgps.su

.PHONY: clean-GPS-2f-Src

