# STM32F429 RTOS Porting
## Build:
1. $make

## Flash:
1. $make flash

## St flash tool:
1. Open STM32 ST-LINK Utility.exe
2. Choose file to flash. 
    - "File -> Open File...", select main.hex
3. Connect to MCU.(need plug USB first)
    - "Target -> Connect"
4. Flash image to MCU.
    - "Target -> Program..."

## St flash cmd:
1.st-flash write .\build\main.bin 0x8000000

## Wire connect:
| TTL pin | MCU pin |
|---------|---------|
|   RX    |   PD5   |
|   TX    |   PD6   |
|   GND   |   GND   |

## Uart protocol:
- Bard rate: 921600
- Data bit: 8
- Stop bit: 1
- Parity: None

## Note:
1. FreeRTOS adding printf to print variables causes kernel panic
    - arm-none-eabi-gcc defaults to using newlib to support the standard library, but its implementation uses dynamic memory allocation functions like malloc without any threading safety mechanism.
    - One solution is to use the heap implementation provided by (https://github.com/DRNadler/FreeRTOS_helpers) which includes memory lock/unlock mechanisms to protect dynamic memory.
    - If you don't want to modify your heap, you can add a line of printf with a fixed string at the beginning of each task to avoid potential issues.
    - If you need to print floating-point numbers, be mindful of the stack size(configMINIMAL_STACK_SIZE).