################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/common/optiga_lib_common.c \
../optiga/common/optiga_lib_logger.c 

OBJS += \
./common/optiga_lib_common.o \
./common/optiga_lib_logger.o 

C_DEPS += \
./common/optiga_lib_common.d \
./common/optiga_lib_logger.d 


# Each subdirectory must supply rules for building sources it contributes
common/optiga_lib_common.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/common/optiga_lib_common.c common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/optiga_lib_logger.o: /Users/thirumurugans/Developer/Projects/FOTA/OPTIGA/optiga/common/optiga_lib_logger.c common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -I../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common

clean-common:
	-$(RM) ./common/optiga_lib_common.cyclo ./common/optiga_lib_common.d ./common/optiga_lib_common.o ./common/optiga_lib_common.su ./common/optiga_lib_logger.cyclo ./common/optiga_lib_logger.d ./common/optiga_lib_logger.o ./common/optiga_lib_logger.su

.PHONY: clean-common

