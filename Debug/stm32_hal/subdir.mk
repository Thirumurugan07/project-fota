################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pal/stm32_hal/pal.c \
../pal/stm32_hal/pal_ifx_i2c_config.c \
../pal/stm32_hal/pal_logger.c \
../pal/stm32_hal/pal_os_datastore.c \
../pal/stm32_hal/pal_os_event.c \
../pal/stm32_hal/pal_os_lock.c \
../pal/stm32_hal/pal_os_timer.c 

OBJS += \
./stm32_hal/pal.o \
./stm32_hal/pal_gpio.o \
./stm32_hal/pal_i2c.o \
./stm32_hal/pal_ifx_i2c_config.o \
./stm32_hal/pal_logger.o \
./stm32_hal/pal_os_datastore.o \
./stm32_hal/pal_os_event.o \
./stm32_hal/pal_os_lock.o \
./stm32_hal/pal_os_timer.o 

C_DEPS += \
./stm32_hal/pal.d \
./stm32_hal/pal_gpio.d \
./stm32_hal/pal_i2c.d \
./stm32_hal/pal_ifx_i2c_config.d \
./stm32_hal/pal_logger.d \
./stm32_hal/pal_os_datastore.d \
./stm32_hal/pal_os_event.d \
./stm32_hal/pal_os_lock.d \
./stm32_hal/pal_os_timer.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_hal/pal.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_gpio.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_gpio.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_i2c.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_i2c.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_ifx_i2c_config.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_ifx_i2c_config.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_logger.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_logger.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_os_datastore.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_os_datastore.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_os_event.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_os_event.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_os_lock.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_os_lock.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32_hal/pal_os_timer.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/pal/stm32_hal/pal_os_timer.c stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32_hal

clean-stm32_hal:
	-$(RM) ./stm32_hal/pal.cyclo ./stm32_hal/pal.d ./stm32_hal/pal.o ./stm32_hal/pal.su ./stm32_hal/pal_gpio.cyclo ./stm32_hal/pal_gpio.d ./stm32_hal/pal_gpio.o ./stm32_hal/pal_gpio.su ./stm32_hal/pal_i2c.cyclo ./stm32_hal/pal_i2c.d ./stm32_hal/pal_i2c.o ./stm32_hal/pal_i2c.su ./stm32_hal/pal_ifx_i2c_config.cyclo ./stm32_hal/pal_ifx_i2c_config.d ./stm32_hal/pal_ifx_i2c_config.o ./stm32_hal/pal_ifx_i2c_config.su ./stm32_hal/pal_logger.cyclo ./stm32_hal/pal_logger.d ./stm32_hal/pal_logger.o ./stm32_hal/pal_logger.su ./stm32_hal/pal_os_datastore.cyclo ./stm32_hal/pal_os_datastore.d ./stm32_hal/pal_os_datastore.o ./stm32_hal/pal_os_datastore.su ./stm32_hal/pal_os_event.cyclo ./stm32_hal/pal_os_event.d ./stm32_hal/pal_os_event.o ./stm32_hal/pal_os_event.su ./stm32_hal/pal_os_lock.cyclo ./stm32_hal/pal_os_lock.d ./stm32_hal/pal_os_lock.o ./stm32_hal/pal_os_lock.su ./stm32_hal/pal_os_timer.cyclo ./stm32_hal/pal_os_timer.d ./stm32_hal/pal_os_timer.o ./stm32_hal/pal_os_timer.su

.PHONY: clean-stm32_hal

