# STM32F429 RTOS Porting
## Environment:
1. USB driver: st-link (https://www.st.com/en/development-tools/stsw-link009.html)
2. flash tool: st-link (https://www.st.com/en/development-tools/stsw-link007.html)
3. cross-compiler: gcc-arm-none-eabi (https://developer.arm.com/downloads/-/gnu-rm)
4. debug tool: openOCD (https://github.com/xpack-dev-tools/openocd-xpack/releases)

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
