================================================================================
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
================================================================================
# Overview

The "Default_firmware" folder includes reusable source code for applications, along with a sample application demonstrating a screensaver. 

# Folder introduction
```
📂 Default_firmware
    ├───eve_hal                        | Hardware abstraction layer for interfacing the FT903 platform with EVE FT811 control support
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



                                   【END】
