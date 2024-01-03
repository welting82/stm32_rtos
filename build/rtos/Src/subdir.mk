# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
	$(wildcard ../rtos/Src/*.c)

# Each subdirectory must supply rules for building sources it contributes
rtos/Src/%.o: ../rtos/Src/%.c
	@echo 'Building file: $<'
	arm-none-eabi-gcc -g \
		-D STM32F429_439xx -D STM32F429xx -D __VFP_FP__ \
		-I ../rtos/Inc \
		-I ../stm32f4xx_hal_driver/Inc \
		-I ../base \
		-O0 \
		-ffunction-sections -fdata-sections \
		--specs=nano.specs -u _printf_float \
		-Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c \
		-fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" \
		-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
