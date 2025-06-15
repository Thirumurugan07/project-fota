################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../optiga/common/optiga_lib_common.c \
../optiga/common/optiga_lib_logger.c 

OBJS += \
./optiga/common/optiga_lib_common.o \
./optiga/common/optiga_lib_logger.o 

C_DEPS += \
./optiga/common/optiga_lib_common.d \
./optiga/common/optiga_lib_logger.d 


# Each subdirectory must supply rules for building sources it contributes
optiga/common/%.o optiga/common/%.su optiga/common/%.cyclo: ../optiga/common/%.c optiga/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../optiga/include -I../optiga/include/optiga/cmd -I../optiga/include/optiga/common -I../optiga/include/optiga/comms -I../optiga/include/optiga/pal -I../optiga/include/optiga/ifx_i2c -I../../pal/stm32_hal -O0 -ffunction-sections -fdata-sections -Wall -DUSE_HAL_DRIVER -DSTM32F401xE -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-optiga-2f-common

clean-optiga-2f-common:
	-$(RM) ./optiga/common/optiga_lib_common.cyclo ./optiga/common/optiga_lib_common.d ./optiga/common/optiga_lib_common.o ./optiga/common/optiga_lib_common.su ./optiga/common/optiga_lib_logger.cyclo ./optiga/common/optiga_lib_logger.d ./optiga/common/optiga_lib_logger.o ./optiga/common/optiga_lib_logger.su

.PHONY: clean-optiga-2f-common

