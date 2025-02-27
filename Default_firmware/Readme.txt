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

This main folder contains reusable source code for applications. It contains 2 folder: 

1. EVE_HAL: Contains the HAL (Hardware Abstraction Layer) source code, it provide 
APIs to control (FT811) from FT90X platform.

2. LIB: Contains the third party libraries.
                     
Below diagram describe how common folder used in the program:
                     
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
                |               LCD, speaker              | 
                -------------------------------------------



                                   【END】
