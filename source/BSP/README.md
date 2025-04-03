# IDP-3500-04A Board Support Package

## Introduction
This repository offers hardware support for the IDP-3500-04A platform. This BSP can function independently with a test application. A USB console is provided for diplaying debug information.

## Hardware Features
- FT903 32-bit RISC microcontroller (MCU) with 100MHz system clock
- FT811 graphics controller with display, touch and audio functionality
- 3.5-inch TFT LCD with capacitive touch
- Integrated buzzer for audio notifications
- Powered by a 9V-24VDC source vis an RJ45 port

## Software Features
The BSP is designed as a support package for devices. Sample usage can be found in *bsp_test.c*

1. The application calls the BSP’s ```init_bsp()```function to initialize interfaces and peripherals:
    - FT903 UART0 and USB console
    - SD card device driver & FATFS filesystem library
    - FT811 EVE GPU device drivers 

2. By default, debug information is transmitted via USB because ```ENABLE_USBDBG``` is set to one in *bsp_debug.h*. However, if ```ENABLE_USBDBG``` is disabled, the debug information will be sent through UART0 instead. 

3. To enable debug information in the eve_hal folder, set ```_DEBUG``` in *eclipse->properties->C/C++ General->Paths and Symbols->Symbols*

### Folder instroduction

```
📂 BSP
├── drivers          | collection of device drivers for IDP-1000-04A peripherals
│   ├── eve_hal      | EVE GPU device driver
│   ├── LCD          | KD2401 LCD controller
│   ├── sdcard       | SD card driver and FATFS filesystem library
│   ├── tinyprintf   | tinyprintf library
│   └── usbdbg       | USB debug driver
├── example_binary   | A pre-compiled binary of this BSP for reference
├── extras           | CLI debug terminal sources
├── include          | configuration and build-time parameters
├── bsp_test.c       | main initialization and tasks routines
├── .cproject        | FT903 project file
├── .project         | FT903 project file
├── README.md        | this README file

```

### Software requirement
This folder does not include the toolchain for FT903. For information on downloading, installing, and using the toolchain, please visit https://brtchip.com/ft9xx-toolchain/. This folder used toolchain setup can be found at https://brtchip.com/wp-content/uploads/Support/SoftwareExample/FT9xx/FT9xx_Toolchain_Setup_2.8.0_rc2.exe

### Build instruction
1. Install FT903 toolchain and download this folder

![image](https://github.com/user-attachments/assets/c2f67d4d-29cd-4d9d-9dbf-185caacc3c07)



2. Launch 'Eclipse for FT9xx', and setup workspace

3. Import BSP_IDP-3500-04A project

![image](https://github.com/user-attachments/assets/ed8766c1-4efd-440e-b507-c4edfc1a0e24)

![image](https://github.com/user-attachments/assets/68a45ff8-fefa-42bb-9c14-83e824533ba8)



4. Setup building enviroment



> If '_DEBUG' is defined, the print information will be sent for eve_hal.

5. Build the project



6. The binary file will be in [YOURPATH]\IDP-3500-04A\source\BSP\FT90x_Debug\BSP_IDP-3500-04A.bin

7. Program the above binary onto the BSP_IDP-3500-04A development board (ensure the debug module is connected to the one-wire debug port as following).

![IDP-3500-04A](https://github.com/user-attachments/assets/2e4747e1-46f4-41f1-8bae-bab1da674fc6)

![image](https://github.com/user-attachments/assets/b71c12f4-a79f-47f3-a6fb-926f0665ccdb)

> The FT9XX programming utility will be installed along with the toolchain.

![image](https://github.com/user-attachments/assets/4a5c2fcf-4449-4ff5-bc9e-a2173af7b319)



![image](https://github.com/user-attachments/assets/f8bf7657-44ae-4372-b6f1-485f758f840d)

8. Board will reboot and show calibration on screen


