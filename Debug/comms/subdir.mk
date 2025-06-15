################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/comms/optiga_comms_ifx_i2c.c 

OBJS += \
./comms/optiga_comms_ifx_i2c.o 

C_DEPS += \
./comms/optiga_comms_ifx_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
comms/optiga_comms_ifx_i2c.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/optiga_comms_ifx_i2c.c comms/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-comms

clean-comms:
	-$(RM) ./comms/optiga_comms_ifx_i2c.cyclo ./comms/optiga_comms_ifx_i2c.d ./comms/optiga_comms_ifx_i2c.o ./comms/optiga_comms_ifx_i2c.su

.PHONY: clean-comms

