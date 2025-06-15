################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/comms/optiga_comms_ifx_i2c.c 

OBJS += \
./optiga/comms/optiga_comms_ifx_i2c.o 

C_DEPS += \
./optiga/comms/optiga_comms_ifx_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
optiga/comms/%.o optiga/comms/%.su optiga/comms/%.cyclo: ../optiga/comms/%.c optiga/comms/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-optiga-2f-comms

clean-optiga-2f-comms:
	-$(RM) ./optiga/comms/optiga_comms_ifx_i2c.cyclo ./optiga/comms/optiga_comms_ifx_i2c.d ./optiga/comms/optiga_comms_ifx_i2c.o ./optiga/comms/optiga_comms_ifx_i2c.su

.PHONY: clean-optiga-2f-comms

