# IDP-3500-04A Board Support Package

## Introduction
This repository offers hardware support for the IDP-3500-04A platform. This BSP can function independently with a test application. A USB console is provided for displaying debug information.

## Hardware Features
- FT903 32-bit RISC microcontroller (MCU) with 100MHz system clock
- FT811 graphics controller with display, touch and audio functionality
- 3.5-inch TFT LCD with capacitive touch
- Integrated buzzer for audio notifications
- Powered by a 9V-24VDC source via an RJ45 port
- LED indicator
- ID switch for unique ID setting
- Hardware reset button
- Board temperature measurement based on the MAX31725 I2C sensor

## Software Features
The BSP is designed as a support package for devices. Sample usage can be found in *bsp_test.c*

1. The application calls the BSP’s ```init_bsp()```function to initialize interfaces and peripherals:
    - FT903 UART0 and USB console
    - rotary
    - LED
    - tempurature sensor
    - SD card device driver & FATFS filesystem library
    - FT811 EVE GPU device drivers 

2. By default, debug information is transmitted via USB because ```ENABLE_USBDBG``` is set to one in *eclipse->properties->C/C++ General->Paths and Symbols->Symbols*
. However, if ```ENABLE_USBDBG``` is se to 0, the debug information will be sent through UART0 instead. If the board is powered via RJ45 instead of USB, ```ENABLE_USBDBG``` must be set to 0.

3. To enable debug information in the eve_hal folder, set ```_DEBUG``` in *eclipse->properties->C/C++ General->Paths and Symbols->Symbols*

![image](https://github.com/user-attachments/assets/87f1897d-1178-4c3f-aeb9-b6054fb1e080)

### Folder introduction

```
📂 BSP
├── drivers          | collection of device drivers for IDP-3500-04A peripherals
│   ├── eve_hal      | EVE GPU device driver
│   ├── LCD          | KD2401 LCD controller
│   ├── rotary       | rotary driver
│   ├── sdcard       | SD card driver and FATFS filesystem library
│   ├── temp_sensor  | MAX31725 I2C temperature sensor
│   ├── tinyprintf   | tinyprintf library
│   └── usbdbg       | USB debug driver
├── example_binary   | A pre-compiled binary of this BSP for reference
├── include          | configuration and build-time parameters
├── .cproject        | FT903 project file
├── .project         | FT903 project file
├── bsp_test.c       | main initialization and tasks routines
├── README.md        | this README file

```

### Software requirement
This folder does not include the toolchain for FT903. For information on downloading, installing, and using the toolchain, please visit https://brtchip.com/ft9xx-toolchain/. This folder used toolchain setup can be found at https://brtchip.com/wp-content/uploads/Support/SoftwareExample/FT9xx/FT9xx_Toolchain_Setup_2.8.0_rc2.exe

### Build instruction
1. Install FT903 toolchain and download this folder

![image](https://github.com/user-attachments/assets/c2f67d4d-29cd-4d9d-9dbf-185caacc3c07)

![image](https://github.com/user-attachments/assets/a4cd04a5-7876-422a-b517-3b1860273202)

2. Launch 'Eclipse for FT9xx', and setup workspace

3. Import BSP_IDP-3500-04A project

![image](https://github.com/user-attachments/assets/ed8766c1-4efd-440e-b507-c4edfc1a0e24)

![image](https://github.com/user-attachments/assets/68a45ff8-fefa-42bb-9c14-83e824533ba8)

![image](https://github.com/user-attachments/assets/be3c5f7c-1b7a-472f-b562-f4b274ab1a0d)

4. Setup building enviroment

![image](https://github.com/user-attachments/assets/6de2647a-ef21-4ff0-b193-17cb1dc6e46d)

![image](https://github.com/user-attachments/assets/fe5a731f-0016-40d9-9252-730029af0ca2)

> [!CAUTION]
> If ```_DEBUG``` is defined, the print information will be sent for eve_hal.
> 
> If ```ENABLE_USBDBG``` is defined to 1, the print information will be sent via USB; If ```ENABLE_USBDBG``` is defined to 0, it will be sent via UART0. If the board is powered via RJ45 instead of USB, ```ENABLE_USBDBG``` must be set to 0.

5. Build the project

![image](https://github.com/user-attachments/assets/6ef8874c-5a38-4fb0-b171-74486d880234)

6. The binary file will be in *[YOURPATH]\IDP-3500-04A\source\BSP\FT90x_Debug\BSP_IDP-3500-04A.bin*

7. Program the above binary onto the IDP-3500-04A development board (ensure the debug module is connected to the one-wire debug port as following).

![IDP-3500-04A](https://github.com/user-attachments/assets/2e4747e1-46f4-41f1-8bae-bab1da674fc6)

![image](https://github.com/user-attachments/assets/b71c12f4-a79f-47f3-a6fb-926f0665ccdb)

> The FT9XX programming utility will be installed along with the toolchain.

![image](https://github.com/user-attachments/assets/4a5c2fcf-4449-4ff5-bc9e-a2173af7b319)

![image](https://github.com/user-attachments/assets/65f2d2c6-0058-472e-bfe3-88385fb33bad)

![image](https://github.com/user-attachments/assets/f8bf7657-44ae-4372-b6f1-485f758f840d)

8. Board will reboot and show calibration on screen


