# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
	../rtos/Src/croutine.c \
	../rtos/Src/event_groups.c \
	../rtos/Src/list.c \
	../rtos/Src/queue.c \
	../rtos/Src/stream_buffer.c \
	../rtos/Src/tasks.c \
	../rtos/Src/timers.c \
	../rtos/Src/port.c \
	../rtos/Src/heap_1.c

# Each subdirectory must supply rules for building sources it contributes
rtos/Src/%.o: ../rtos/Src/%.c
	@echo 'Building file: $<'
	arm-none-eabi-gcc \
		-D STM32F429_439xx -D STM32F429xx -D __VFP_FP__ \
		-I ../rtos/Inc \
		-I ../stm32f4xx_hal_driver/Inc \
		-I ../base \
		-O0 \
		-ffunction-sections -fdata-sections \
		-Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c \
		-fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" \
		-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
