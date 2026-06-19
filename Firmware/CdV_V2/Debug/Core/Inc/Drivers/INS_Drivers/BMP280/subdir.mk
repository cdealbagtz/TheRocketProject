################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.c 

OBJS += \
./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.o 

C_DEPS += \
./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Drivers/INS_Drivers/BMP280/%.o Core/Inc/Drivers/INS_Drivers/BMP280/%.su Core/Inc/Drivers/INS_Drivers/BMP280/%.cyclo: ../Core/Inc/Drivers/INS_Drivers/BMP280/%.c Core/Inc/Drivers/INS_Drivers/BMP280/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Drivers-2f-INS_Drivers-2f-BMP280

clean-Core-2f-Inc-2f-Drivers-2f-INS_Drivers-2f-BMP280:
	-$(RM) ./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.cyclo ./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.d ./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.o ./Core/Inc/Drivers/INS_Drivers/BMP280/BMP280.su

.PHONY: clean-Core-2f-Inc-2f-Drivers-2f-INS_Drivers-2f-BMP280

