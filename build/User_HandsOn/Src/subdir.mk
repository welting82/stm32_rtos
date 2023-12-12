# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
	$(wildcard ../User_HandsOn/Src/*.c)

# Each subdirectory must supply rules for building sources it contributes
User_HandsOn/Src/%.o: ../User_HandsOn/Src/%.c
	@echo 'Building file: $<'
	arm-none-eabi-gcc -g\
		-D STM32F429_439xx -D STM32F429xx -D __VFP_FP__ \
		-I ../base \
		-I ../startup \
		-I ../stm32f4xx_hal_driver/Inc \
		-I ../rtos/Inc \
		-I ../User_HandsOn/Inc \
		-O0 -ffunction-sections -fdata-sections \
		-Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '