################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FC_RC/Protocol/PPM.c \
../Core/Src/FC_RC/Protocol/SRXL2.c \
../Core/Src/FC_RC/Protocol/SRXL_testing.c 

OBJS += \
./Core/Src/FC_RC/Protocol/PPM.o \
./Core/Src/FC_RC/Protocol/SRXL2.o \
./Core/Src/FC_RC/Protocol/SRXL_testing.o 

C_DEPS += \
./Core/Src/FC_RC/Protocol/PPM.d \
./Core/Src/FC_RC/Protocol/SRXL2.d \
./Core/Src/FC_RC/Protocol/SRXL_testing.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FC_RC/Protocol/%.o Core/Src/FC_RC/Protocol/%.su Core/Src/FC_RC/Protocol/%.cyclo: ../Core/Src/FC_RC/Protocol/%.c Core/Src/FC_RC/Protocol/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FC_RC-2f-Protocol

clean-Core-2f-Src-2f-FC_RC-2f-Protocol:
	-$(RM) ./Core/Src/FC_RC/Protocol/PPM.cyclo ./Core/Src/FC_RC/Protocol/PPM.d ./Core/Src/FC_RC/Protocol/PPM.o ./Core/Src/FC_RC/Protocol/PPM.su ./Core/Src/FC_RC/Protocol/SRXL2.cyclo ./Core/Src/FC_RC/Protocol/SRXL2.d ./Core/Src/FC_RC/Protocol/SRXL2.o ./Core/Src/FC_RC/Protocol/SRXL2.su ./Core/Src/FC_RC/Protocol/SRXL_testing.cyclo ./Core/Src/FC_RC/Protocol/SRXL_testing.d ./Core/Src/FC_RC/Protocol/SRXL_testing.o ./Core/Src/FC_RC/Protocol/SRXL_testing.su

.PHONY: clean-Core-2f-Src-2f-FC_RC-2f-Protocol

