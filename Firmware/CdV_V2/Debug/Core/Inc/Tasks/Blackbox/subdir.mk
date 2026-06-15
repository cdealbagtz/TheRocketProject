################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Tasks/Blackbox/Blackbox.c 

OBJS += \
./Core/Inc/Tasks/Blackbox/Blackbox.o 

C_DEPS += \
./Core/Inc/Tasks/Blackbox/Blackbox.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Tasks/Blackbox/%.o Core/Inc/Tasks/Blackbox/%.su Core/Inc/Tasks/Blackbox/%.cyclo: ../Core/Inc/Tasks/Blackbox/%.c Core/Inc/Tasks/Blackbox/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Tasks-2f-Blackbox

clean-Core-2f-Inc-2f-Tasks-2f-Blackbox:
	-$(RM) ./Core/Inc/Tasks/Blackbox/Blackbox.cyclo ./Core/Inc/Tasks/Blackbox/Blackbox.d ./Core/Inc/Tasks/Blackbox/Blackbox.o ./Core/Inc/Tasks/Blackbox/Blackbox.su

.PHONY: clean-Core-2f-Inc-2f-Tasks-2f-Blackbox

