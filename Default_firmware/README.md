```
 Copyright (c) Bridgetek Pte Ltd.                                               
                                                                                
 THIS SOFTWARE IS PROVIDED BY BRIDGETEK PTE LTD. ``AS IS'' AND ANY EXPRESS OR   
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF   
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO     
 EVENT SHALL BRIDGETEK PTE LTD BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,   
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, LOSS OF USE, DATA, OR PROFITS OR  
 BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER  
 IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE     
 POSSIBILITY OF SUCH DAMAGE.                                                    
```

# Overview

The "Default_firmware" folder includes reusable source code for applications, along with a sample application demonstrating a screensaver for reference purpose. 

# Folder introduction
```
📂 Default_firmware
    ├───eve_hal                        | Hardware abstraction layer for interfacing the FT903 platform with EVE FT811 control support
    ├───example_binary                 | A pre-compiled binary of this default firmware for reference
    ├───lib                            | Third party libraries
    │   ├──LCD                         | LCD support library
    │   ├──fatfs                       | fatfs library for SD card support
    │   ├──tinyprintf                  | tinyprintf library
    │   ├──usbdbg                      | Library for supporting the printing of USB debug information
    ├───.cproject                      | FT903 project file
    ├───.project                       | FT903 project file
    ├───Bridgetek_Logo_143x50_ARGB4.c  | Bridgetek logo image data used in the sample application
    ├───app.c                          | Sample application featuring FT903 and FT811 initialization, calibration, and screensaver functionality
    ├───app.h                          | Header file for sample application
```

# System diagram
Below diagram describe how this folder used in the program:
                     
                -------------------------------------------
                |             Main application            |
                -------------------------------------------
                     |                   |
                     |                   ▼
                     |        -----------------------
                     |        |          Lib        |
                     |        -----------------------
                     |                   |
                     ▼                   ▼
                -------------------------------------------
                |                  eve_hal                |
                -------------------------------------------
                                      |
                                      |
                                      ▼
                -------------------------------------------
                |             EVE ICs (FT81x)             |
                -------------------------------------------
                                      |
                                      |
                                      ▼   
                -------------------------------------------
                |               LCD, touch                | 
                -------------------------------------------

# Usage
IDP903-35PA is using EVE FT811 with FT903 host platform. Users are expected to be familiar with the FT81X programming guide and data sheet for EVE FT811 chip.

This folder does not include the toolchain for FT903. For information on downloading, installing, and using the toolchain, please visit https://brtchip.com/ft9xx-toolchain/. This folder used toolchain setup can be found at https://brtchip.com/wp-content/uploads/Support/SoftwareExample/FT9xx/FT9xx_Toolchain_Setup_2.8.0_rc2.exe

## Hardware requirement
* IDP903-35PA development board
* FTDI UMFTPD2A Module

![IDP903-35PA](https://github.com/user-attachments/assets/9ce471f0-070a-4161-aca9-e6e801a2688d)


## Build instruction
1. Install FT903 toolchain and download this folder

![image](https://github.com/user-attachments/assets/c2f67d4d-29cd-4d9d-9dbf-185caacc3c07)

![image](https://github.com/user-attachments/assets/8fd63ca3-9d13-4d78-8405-8987a9f5c2c4)

2. Launch 'Eclipse for FT9xx', and setup workspace

3. Import IDP903-35PA project

![image](https://github.com/user-attachments/assets/ed8766c1-4efd-440e-b507-c4edfc1a0e24)

![image](https://github.com/user-attachments/assets/68a45ff8-fefa-42bb-9c14-83e824533ba8)

![image](https://github.com/user-attachments/assets/00c903d3-386c-4d30-9e61-d1060c3148e7)

4. Setup building enviroment

![image](https://github.com/user-attachments/assets/1dc5e29a-554e-4f94-8b05-63d1995292c4)

![image](https://github.com/user-attachments/assets/b12c211c-8948-4d21-8c28-f5c389bb2374)

> If 'USB_DEBUG' is defined, the print information will be sent via USB; otherwise, it will be sent via UART0.

5. Build the project

![image](https://github.com/user-attachments/assets/bdecefd3-1aa3-47bd-9e6d-577adec14896)

6. The binary file will be in [YOURPATH]\IDP903-35PA\Default_firmware\FT90x_Debug\IDP903_35PA.bin

7. Program the above binary onto the IDP903-35PA development board (ensure the debug module is connected to the one-wire debug port as specified in the 'Hardware Requirements' section).

![image](https://github.com/user-attachments/assets/b71c12f4-a79f-47f3-a6fb-926f0665ccdb)

> The FT9XX programming utility will be installed along with the toolchain.

![image](https://github.com/user-attachments/assets/4a5c2fcf-4449-4ff5-bc9e-a2173af7b319)

![image](https://github.com/user-attachments/assets/b5b07444-7415-44af-9ebb-602419845ab2)

![image](https://github.com/user-attachments/assets/f8bf7657-44ae-4372-b6f1-485f758f840d)

8. Board will reboot and show the application

![image](https://github.com/user-attachments/assets/6c6fad4e-d9c1-4c97-a117-1cbf5d300a6d)

 

                                   【END】
