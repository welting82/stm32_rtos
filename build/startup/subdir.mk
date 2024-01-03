# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
	../startup/startup_stm32f429_439xx.s

# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	arm-none-eabi-gcc -x assembler-with-cpp -g \
		-D STM32F429_439xx -D STM32F429xx -D __VFP_FP__ \
		-I ../base \
		-I ../User_HandsOn/Inc \
		-I ../startup \
		-I ../stm32f4xx_hal_driver/Inc \
		--specs=nano.specs -u _printf_float \
		-Wa,-adhlns="$@.lst" -c -fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" \
		-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
