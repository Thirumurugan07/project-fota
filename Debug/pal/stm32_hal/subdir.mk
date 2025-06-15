################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pal/stm32_hal/pal.c \
../pal/stm32_hal/pal_gpio.c \
../pal/stm32_hal/pal_i2c.c \
../pal/stm32_hal/pal_ifx_i2c_config.c \
../pal/stm32_hal/pal_logger.c \
../pal/stm32_hal/pal_os_datastore.c \
../pal/stm32_hal/pal_os_event.c \
../pal/stm32_hal/pal_os_lock.c \
../pal/stm32_hal/pal_os_timer.c 

OBJS += \
./pal/stm32_hal/pal.o \
./pal/stm32_hal/pal_gpio.o \
./pal/stm32_hal/pal_i2c.o \
./pal/stm32_hal/pal_ifx_i2c_config.o \
./pal/stm32_hal/pal_logger.o \
./pal/stm32_hal/pal_os_datastore.o \
./pal/stm32_hal/pal_os_event.o \
./pal/stm32_hal/pal_os_lock.o \
./pal/stm32_hal/pal_os_timer.o 

C_DEPS += \
./pal/stm32_hal/pal.d \
./pal/stm32_hal/pal_gpio.d \
./pal/stm32_hal/pal_i2c.d \
./pal/stm32_hal/pal_ifx_i2c_config.d \
./pal/stm32_hal/pal_logger.d \
./pal/stm32_hal/pal_os_datastore.d \
./pal/stm32_hal/pal_os_event.d \
./pal/stm32_hal/pal_os_lock.d \
./pal/stm32_hal/pal_os_timer.d 


# Each subdirectory must supply rules for building sources it contributes
pal/stm32_hal/%.o pal/stm32_hal/%.su pal/stm32_hal/%.cyclo: ../pal/stm32_hal/%.c pal/stm32_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-pal-2f-stm32_hal

clean-pal-2f-stm32_hal:
	-$(RM) ./pal/stm32_hal/pal.cyclo ./pal/stm32_hal/pal.d ./pal/stm32_hal/pal.o ./pal/stm32_hal/pal.su ./pal/stm32_hal/pal_gpio.cyclo ./pal/stm32_hal/pal_gpio.d ./pal/stm32_hal/pal_gpio.o ./pal/stm32_hal/pal_gpio.su ./pal/stm32_hal/pal_i2c.cyclo ./pal/stm32_hal/pal_i2c.d ./pal/stm32_hal/pal_i2c.o ./pal/stm32_hal/pal_i2c.su ./pal/stm32_hal/pal_ifx_i2c_config.cyclo ./pal/stm32_hal/pal_ifx_i2c_config.d ./pal/stm32_hal/pal_ifx_i2c_config.o ./pal/stm32_hal/pal_ifx_i2c_config.su ./pal/stm32_hal/pal_logger.cyclo ./pal/stm32_hal/pal_logger.d ./pal/stm32_hal/pal_logger.o ./pal/stm32_hal/pal_logger.su ./pal/stm32_hal/pal_os_datastore.cyclo ./pal/stm32_hal/pal_os_datastore.d ./pal/stm32_hal/pal_os_datastore.o ./pal/stm32_hal/pal_os_datastore.su ./pal/stm32_hal/pal_os_event.cyclo ./pal/stm32_hal/pal_os_event.d ./pal/stm32_hal/pal_os_event.o ./pal/stm32_hal/pal_os_event.su ./pal/stm32_hal/pal_os_lock.cyclo ./pal/stm32_hal/pal_os_lock.d ./pal/stm32_hal/pal_os_lock.o ./pal/stm32_hal/pal_os_lock.su ./pal/stm32_hal/pal_os_timer.cyclo ./pal/stm32_hal/pal_os_timer.d ./pal/stm32_hal/pal_os_timer.o ./pal/stm32_hal/pal_os_timer.su

.PHONY: clean-pal-2f-stm32_hal

