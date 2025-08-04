################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/common.c \
/Users/thirumurugans/Downloads/example_optiga_init_deinit.c \
/Users/thirumurugans/Downloads/example_optiga_util_read_data.c \
/Users/thirumurugans/Downloads/example_optiga_util_write_data.c \
../Core/Src/flash_if.c \
../Core/Src/ifx_i2c.c \
../Core/Src/ifx_i2c_config.c \
../Core/Src/ifx_i2c_data_link_layer.c \
../Core/Src/ifx_i2c_physical_layer.c \
../Core/Src/ifx_i2c_presentation_layer.c \
../Core/Src/ifx_i2c_transport_layer.c \
../Core/Src/main.c \
../Core/Src/menu.c \
../Core/Src/optiga_auth.c \
../optiga/cmd/optiga_cmd.c \
../optiga/comms/optiga_comms_ifx_i2c.c \
../optiga/crypt/optiga_crypt.c \
../optiga/common/optiga_lib_common.c \
../optiga/common/optiga_lib_logger.c \
../optiga/util/optiga_util.c \
../Core/Src/pal.c \
../Core/Src/pal_crypt_stub.c \
../Core/Src/pal_gpio.c \
../Core/Src/pal_i2c.c \
../Core/Src/pal_ifx_i2c_config.c \
../Core/Src/pal_logger.c \
../Core/Src/pal_os_datastore.c \
../Core/Src/pal_os_event.c \
../Core/Src/pal_os_lock.c \
../Core/Src/pal_os_memory.c \
../Core/Src/pal_os_timer.c \
../Core/Src/platform.c \
../Core/Src/platform_util.c \
../Core/Src/sha256.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/ymodem.c 

OBJS += \
./Core/Src/common.o \
./Core/Src/example_optiga_init_deinit.o \
./Core/Src/example_optiga_util_read_data.o \
./Core/Src/example_optiga_util_write_data.o \
./Core/Src/flash_if.o \
./Core/Src/ifx_i2c.o \
./Core/Src/ifx_i2c_config.o \
./Core/Src/ifx_i2c_data_link_layer.o \
./Core/Src/ifx_i2c_physical_layer.o \
./Core/Src/ifx_i2c_presentation_layer.o \
./Core/Src/ifx_i2c_transport_layer.o \
./Core/Src/main.o \
./Core/Src/menu.o \
./Core/Src/optiga_auth.o \
./Core/Src/optiga_cmd.o \
./Core/Src/optiga_comms_ifx_i2c.o \
./Core/Src/optiga_crypt.o \
./Core/Src/optiga_lib_common.o \
./Core/Src/optiga_lib_logger.o \
./Core/Src/optiga_util.o \
./Core/Src/pal.o \
./Core/Src/pal_crypt_stub.o \
./Core/Src/pal_gpio.o \
./Core/Src/pal_i2c.o \
./Core/Src/pal_ifx_i2c_config.o \
./Core/Src/pal_logger.o \
./Core/Src/pal_os_datastore.o \
./Core/Src/pal_os_event.o \
./Core/Src/pal_os_lock.o \
./Core/Src/pal_os_memory.o \
./Core/Src/pal_os_timer.o \
./Core/Src/platform.o \
./Core/Src/platform_util.o \
./Core/Src/sha256.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/ymodem.o 

C_DEPS += \
./Core/Src/common.d \
./Core/Src/example_optiga_init_deinit.d \
./Core/Src/example_optiga_util_read_data.d \
./Core/Src/example_optiga_util_write_data.d \
./Core/Src/flash_if.d \
./Core/Src/ifx_i2c.d \
./Core/Src/ifx_i2c_config.d \
./Core/Src/ifx_i2c_data_link_layer.d \
./Core/Src/ifx_i2c_physical_layer.d \
./Core/Src/ifx_i2c_presentation_layer.d \
./Core/Src/ifx_i2c_transport_layer.d \
./Core/Src/main.d \
./Core/Src/menu.d \
./Core/Src/optiga_auth.d \
./Core/Src/optiga_cmd.d \
./Core/Src/optiga_comms_ifx_i2c.d \
./Core/Src/optiga_crypt.d \
./Core/Src/optiga_lib_common.d \
./Core/Src/optiga_lib_logger.d \
./Core/Src/optiga_util.d \
./Core/Src/pal.d \
./Core/Src/pal_crypt_stub.d \
./Core/Src/pal_gpio.d \
./Core/Src/pal_i2c.d \
./Core/Src/pal_ifx_i2c_config.d \
./Core/Src/pal_logger.d \
./Core/Src/pal_os_datastore.d \
./Core/Src/pal_os_event.d \
./Core/Src/pal_os_lock.d \
./Core/Src/pal_os_memory.d \
./Core/Src/pal_os_timer.d \
./Core/Src/platform.d \
./Core/Src/platform_util.d \
./Core/Src/sha256.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/ymodem.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/example_optiga_init_deinit.o: /Users/thirumurugans/Downloads/example_optiga_init_deinit.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/example_optiga_util_read_data.o: /Users/thirumurugans/Downloads/example_optiga_util_read_data.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/example_optiga_util_write_data.o: /Users/thirumurugans/Downloads/example_optiga_util_write_data.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_cmd.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/cmd/optiga_cmd.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_comms_ifx_i2c.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/comms/optiga_comms_ifx_i2c.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_crypt.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/crypt/optiga_crypt.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_lib_common.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/common/optiga_lib_common.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_lib_logger.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/common/optiga_lib_logger.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/optiga_util.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/util/optiga_util.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/common.cyclo ./Core/Src/common.d ./Core/Src/common.o ./Core/Src/common.su ./Core/Src/example_optiga_init_deinit.cyclo ./Core/Src/example_optiga_init_deinit.d ./Core/Src/example_optiga_init_deinit.o ./Core/Src/example_optiga_init_deinit.su ./Core/Src/example_optiga_util_read_data.cyclo ./Core/Src/example_optiga_util_read_data.d ./Core/Src/example_optiga_util_read_data.o ./Core/Src/example_optiga_util_read_data.su ./Core/Src/example_optiga_util_write_data.cyclo ./Core/Src/example_optiga_util_write_data.d ./Core/Src/example_optiga_util_write_data.o ./Core/Src/example_optiga_util_write_data.su ./Core/Src/flash_if.cyclo ./Core/Src/flash_if.d ./Core/Src/flash_if.o ./Core/Src/flash_if.su ./Core/Src/ifx_i2c.cyclo ./Core/Src/ifx_i2c.d ./Core/Src/ifx_i2c.o ./Core/Src/ifx_i2c.su ./Core/Src/ifx_i2c_config.cyclo ./Core/Src/ifx_i2c_config.d ./Core/Src/ifx_i2c_config.o ./Core/Src/ifx_i2c_config.su ./Core/Src/ifx_i2c_data_link_layer.cyclo ./Core/Src/ifx_i2c_data_link_layer.d ./Core/Src/ifx_i2c_data_link_layer.o ./Core/Src/ifx_i2c_data_link_layer.su ./Core/Src/ifx_i2c_physical_layer.cyclo ./Core/Src/ifx_i2c_physical_layer.d ./Core/Src/ifx_i2c_physical_layer.o ./Core/Src/ifx_i2c_physical_layer.su ./Core/Src/ifx_i2c_presentation_layer.cyclo ./Core/Src/ifx_i2c_presentation_layer.d ./Core/Src/ifx_i2c_presentation_layer.o ./Core/Src/ifx_i2c_presentation_layer.su ./Core/Src/ifx_i2c_transport_layer.cyclo ./Core/Src/ifx_i2c_transport_layer.d ./Core/Src/ifx_i2c_transport_layer.o ./Core/Src/ifx_i2c_transport_layer.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/menu.cyclo ./Core/Src/menu.d ./Core/Src/menu.o ./Core/Src/menu.su ./Core/Src/optiga_auth.cyclo ./Core/Src/optiga_auth.d ./Core/Src/optiga_auth.o ./Core/Src/optiga_auth.su ./Core/Src/optiga_cmd.cyclo ./Core/Src/optiga_cmd.d ./Core/Src/optiga_cmd.o ./Core/Src/optiga_cmd.su ./Core/Src/optiga_comms_ifx_i2c.cyclo ./Core/Src/optiga_comms_ifx_i2c.d ./Core/Src/optiga_comms_ifx_i2c.o ./Core/Src/optiga_comms_ifx_i2c.su ./Core/Src/optiga_crypt.cyclo ./Core/Src/optiga_crypt.d ./Core/Src/optiga_crypt.o ./Core/Src/optiga_crypt.su ./Core/Src/optiga_lib_common.cyclo ./Core/Src/optiga_lib_common.d ./Core/Src/optiga_lib_common.o ./Core/Src/optiga_lib_common.su ./Core/Src/optiga_lib_logger.cyclo ./Core/Src/optiga_lib_logger.d ./Core/Src/optiga_lib_logger.o ./Core/Src/optiga_lib_logger.su ./Core/Src/optiga_util.cyclo ./Core/Src/optiga_util.d ./Core/Src/optiga_util.o ./Core/Src/optiga_util.su ./Core/Src/pal.cyclo ./Core/Src/pal.d ./Core/Src/pal.o ./Core/Src/pal.su ./Core/Src/pal_crypt_stub.cyclo ./Core/Src/pal_crypt_stub.d ./Core/Src/pal_crypt_stub.o ./Core/Src/pal_crypt_stub.su ./Core/Src/pal_gpio.cyclo ./Core/Src/pal_gpio.d ./Core/Src/pal_gpio.o ./Core/Src/pal_gpio.su ./Core/Src/pal_i2c.cyclo ./Core/Src/pal_i2c.d ./Core/Src/pal_i2c.o ./Core/Src/pal_i2c.su ./Core/Src/pal_ifx_i2c_config.cyclo ./Core/Src/pal_ifx_i2c_config.d ./Core/Src/pal_ifx_i2c_config.o ./Core/Src/pal_ifx_i2c_config.su ./Core/Src/pal_logger.cyclo ./Core/Src/pal_logger.d ./Core/Src/pal_logger.o ./Core/Src/pal_logger.su ./Core/Src/pal_os_datastore.cyclo ./Core/Src/pal_os_datastore.d ./Core/Src/pal_os_datastore.o ./Core/Src/pal_os_datastore.su ./Core/Src/pal_os_event.cyclo ./Core/Src/pal_os_event.d ./Core/Src/pal_os_event.o ./Core/Src/pal_os_event.su ./Core/Src/pal_os_lock.cyclo ./Core/Src/pal_os_lock.d ./Core/Src/pal_os_lock.o ./Core/Src/pal_os_lock.su ./Core/Src/pal_os_memory.cyclo ./Core/Src/pal_os_memory.d ./Core/Src/pal_os_memory.o ./Core/Src/pal_os_memory.su ./Core/Src/pal_os_timer.cyclo ./Core/Src/pal_os_timer.d ./Core/Src/pal_os_timer.o ./Core/Src/pal_os_timer.su ./Core/Src/platform.cyclo ./Core/Src/platform.d ./Core/Src/platform.o ./Core/Src/platform.su ./Core/Src/platform_util.cyclo ./Core/Src/platform_util.d ./Core/Src/platform_util.o ./Core/Src/platform_util.su ./Core/Src/sha256.cyclo ./Core/Src/sha256.d ./Core/Src/sha256.o ./Core/Src/sha256.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/ymodem.cyclo ./Core/Src/ymodem.d ./Core/Src/ymodem.o ./Core/Src/ymodem.su

.PHONY: clean-Core-2f-Src

