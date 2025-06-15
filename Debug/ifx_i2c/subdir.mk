################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/comms/ifx_i2c/ifx_i2c.c \
../optiga/comms/ifx_i2c/ifx_i2c_config.c \
../optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.c \
../optiga/comms/ifx_i2c/ifx_i2c_physical_layer.c \
../optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.c \
../optiga/comms/ifx_i2c/ifx_i2c_transport_layer.c 

OBJS += \
./ifx_i2c/ifx_i2c.o \
./ifx_i2c/ifx_i2c_config.o \
./ifx_i2c/ifx_i2c_data_link_layer.o \
./ifx_i2c/ifx_i2c_physical_layer.o \
./ifx_i2c/ifx_i2c_presentation_layer.o \
./ifx_i2c/ifx_i2c_transport_layer.o 

C_DEPS += \
./ifx_i2c/ifx_i2c.d \
./ifx_i2c/ifx_i2c_config.d \
./ifx_i2c/ifx_i2c_data_link_layer.d \
./ifx_i2c/ifx_i2c_physical_layer.d \
./ifx_i2c/ifx_i2c_presentation_layer.d \
./ifx_i2c/ifx_i2c_transport_layer.d 


# Each subdirectory must supply rules for building sources it contributes
ifx_i2c/ifx_i2c.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ifx_i2c/ifx_i2c_config.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c_config.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ifx_i2c/ifx_i2c_data_link_layer.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ifx_i2c/ifx_i2c_physical_layer.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ifx_i2c/ifx_i2c_presentation_layer.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ifx_i2c/ifx_i2c_transport_layer.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.c ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ifx_i2c

clean-ifx_i2c:
	-$(RM) ./ifx_i2c/ifx_i2c.cyclo ./ifx_i2c/ifx_i2c.d ./ifx_i2c/ifx_i2c.o ./ifx_i2c/ifx_i2c.su ./ifx_i2c/ifx_i2c_config.cyclo ./ifx_i2c/ifx_i2c_config.d ./ifx_i2c/ifx_i2c_config.o ./ifx_i2c/ifx_i2c_config.su ./ifx_i2c/ifx_i2c_data_link_layer.cyclo ./ifx_i2c/ifx_i2c_data_link_layer.d ./ifx_i2c/ifx_i2c_data_link_layer.o ./ifx_i2c/ifx_i2c_data_link_layer.su ./ifx_i2c/ifx_i2c_physical_layer.cyclo ./ifx_i2c/ifx_i2c_physical_layer.d ./ifx_i2c/ifx_i2c_physical_layer.o ./ifx_i2c/ifx_i2c_physical_layer.su ./ifx_i2c/ifx_i2c_presentation_layer.cyclo ./ifx_i2c/ifx_i2c_presentation_layer.d ./ifx_i2c/ifx_i2c_presentation_layer.o ./ifx_i2c/ifx_i2c_presentation_layer.su ./ifx_i2c/ifx_i2c_transport_layer.cyclo ./ifx_i2c/ifx_i2c_transport_layer.d ./ifx_i2c/ifx_i2c_transport_layer.o ./ifx_i2c/ifx_i2c_transport_layer.su

.PHONY: clean-ifx_i2c

