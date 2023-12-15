# ref: https://gcc.gnu.org/onlinedocs/gcc/Option-Index.html

######################################
# target
######################################
TARGET = main


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
	$(wildcard base/*.c) \
	$(wildcard rtos/Src/*.c) \
	$(wildcard User_HandsOn/Src/*.c) \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_adc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_adc_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_can.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_cec.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_cortex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_crc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_cryp.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_cryp_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dac.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dac_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dcmi.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dcmi_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dfsdm.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dma.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dma2d.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dma_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_dsi.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_eth.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_exti.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash_ramfunc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_fmpi2c.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_fmpi2c_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_fmpsmbus.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_fmpsmbus_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_hash.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_hash_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_hcd.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_i2c.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_i2c_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_i2s.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_i2s_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_irda.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_iwdg.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_lptim.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_ltdc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_ltdc_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_mmc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_nand.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_nor.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_pccard.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_pcd.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_pcd_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_pwr.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_pwr_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_qspi.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_rng.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_rtc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_rtc_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_sai.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_sai_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_sd.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_sdram.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_smartcard.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_smbus.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_spdifrx.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_spi.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_sram.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim_ex.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_uart.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_usart.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_hal_wwdg.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_adc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_crc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_dac.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_dma.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_dma2d.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_exti.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_fmc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_fmpi2c.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_fsmc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_gpio.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_i2c.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_lptim.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_pwr.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_rcc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_rng.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_rtc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_sdmmc.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_spi.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_tim.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_usart.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_usb.c \
	stm32f4xx_hal_driver/Src/stm32f4xx_ll_utils.c 

# ASM sources
ASM_SOURCES =  \
startup/startup_stm32f429_439xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
	-D STM32F429_439xx \
	-D STM32F429xx \
	-D USE_HAL_DRIVER \
	-D __VFP_FP__ 


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
	-I base \
	-I rtos/Inc \
	-I User_HandsOn/Inc \
	-I startup \
	-I stm32f4xx_hal_driver/Inc 


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -std=gnu99 -fmessage-length=0

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -std=gnu99 -fmessage-length=0

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = startup/STM32F429ZI_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@
	
$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
ifeq ($(OS),Windows_NT)
	del /q $(BUILD_DIR)
else ifeq ($(shell uname), Darwin)
	rm -rf $(BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif

#######################################
# flash to mcu
#######################################
flash: build/main.bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean dependents
