# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
	$(wildcard ../base/*.c)

# Each subdirectory must supply rules for building sources it contributes
base/%.o: ../base/%.c
	@echo 'Building file: $<'
	arm-none-eabi-gcc -g \
		-D STM32F429_439xx -D STM32F429xx -D USE_HAL_DRIVER -D __VFP_FP__ \
		-I ../base \
		-I ../User_HandsOn/Inc \
		-I ../startup \
		-I ../stm32f4xx_hal_driver/Inc \
		-O0 \
		-ffunction-sections -fdata-sections \
		-Wall -std=gnu99 \
		--specs=nano.specs -u _printf_float \
		-Wa,-adhlns="$@.lst" \
		-c \
		-fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" \
		-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
