################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/cmd/optiga_cmd.c 

OBJS += \
./optiga/cmd/optiga_cmd.o 

C_DEPS += \
./optiga/cmd/optiga_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
optiga/cmd/%.o optiga/cmd/%.su optiga/cmd/%.cyclo: ../optiga/cmd/%.c optiga/cmd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-optiga-2f-cmd

clean-optiga-2f-cmd:
	-$(RM) ./optiga/cmd/optiga_cmd.cyclo ./optiga/cmd/optiga_cmd.d ./optiga/cmd/optiga_cmd.o ./optiga/cmd/optiga_cmd.su

.PHONY: clean-optiga-2f-cmd

