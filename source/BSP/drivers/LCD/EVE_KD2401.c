/*

Copyright (c) Future Technology Devices International 2014

THIS SOFTWARE IS PROVIDED BY FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FTDI DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON FTDI PARTS.

FTDI DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE INFORMATION IS NOT MODIFIED.

IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED, IT IS THE
RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES AND SUBSEQUENT WHQL
RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.

Author : Bridgetek
Abstract: KD2401 driver source

Revision History:
0.1 - date 2015.05.08 - Initial Version

*/

#include "EVE_KD2401.h"

void write_data(unsigned char w)
{
	unsigned char i;

	KD2401_CS_LOW;
	KD2401_CLK_LOW;
	KD2401_MOSI_HIGH;
	usleep(1);
	KD2401_CLK_HIGH;
	for (i = 0; i < 8; i++)
	{
		KD2401_CLK_LOW;
		usleep(1);

		if (w&0x80)
		{
			KD2401_MOSI_HIGH;
		}
		else
		{
			KD2401_MOSI_LOW;
		}
		KD2401_CLK_HIGH;
		usleep(1);
		w=w<<1;
	}
	KD2401_CS_HIGH;
}

void write_command(unsigned char y)
{
	unsigned char i;

	KD2401_CS_LOW;
	KD2401_CLK_LOW;
	KD2401_MOSI_LOW;
	usleep(1);
	KD2401_CLK_HIGH;
	for (i = 0; i < 8; i++)
	{
		KD2401_CLK_LOW;
		usleep(1);

		if (y&0x80)
		{
			KD2401_MOSI_HIGH;
		}
		else
		{
			KD2401_MOSI_LOW;
		}
		KD2401_CLK_HIGH;
		usleep(1);
		y=y<<1;
	}
	KD2401_CS_HIGH;
}

void KD2401_Bootup()
{
	/* TODO - use the method exposed by EVE HAL library and panlbsp for setting the
	 * eve and eflash into default states - mainly the CS to be high */
	/* KD2401 driver - configure pins for bit bang */
	gpio_function(27, pad_gpio27);
	gpio_function(28, pad_gpio28); //cs0 for eve
	gpio_function(29, pad_gpio29);
	gpio_function(30, pad_gpio30);
	gpio_function(33, pad_gpio33); //ss1 for KD2401
	gpio_function(35, pad_gpio35); //ss3 for eflash
	gpio_function(1, pad_gpio1); //power down of FT81x

	gpio_dir(27, pad_dir_output);//gpios for ili9488 - spim clock
	gpio_dir(28, pad_dir_output); //cs0 for eve
	gpio_dir(29, pad_dir_output);//gpios for ili9488 - spim mosi
	gpio_dir(30, pad_dir_input);//gpios for ili9488 - spim miso
	gpio_dir(33, pad_dir_output);//gpios for ili9488 - cs1#
	gpio_dir(35, pad_dir_output);//gpios for eflash - ss3#
	gpio_dir(1, pad_dir_output);//power down

#if 1
	/* Set the default state of the GPIO */
	gpio_write(28, 1);
	gpio_write(33, 1);
	gpio_write(35, 1);
	gpio_write(1, 1);
	gpio_write(28, 1);
    gpio_write(1, 1);
	gpio_write(33, 1);
	gpio_write(35, 1);
#endif


	//display driver bring up
	{
		/***************************************/
		write_command(0xC0);
		write_data(0x17);
		write_data(0x17);

		write_command(0xC1);
		write_data(0x44);

		write_command(0xC5);
		write_data(0x00);
		write_data(0x3A);//
		write_data(0x80);

		write_command(0x36);
		write_data(0x48);

		write_command(0x3A); //Interface Mode Control
		write_data(0x60);

		write_command(0xB1);   //Frame rate 70HZ
		write_data(0xA0);

		write_command(0xB4);
		write_data(0x02);

		write_command(0xB7);
		write_data(0xC6);

		write_command(0xE9);
		write_data(0x00);

		write_command(0XF7);
		write_data(0xA9);
		write_data(0x51);
		write_data(0x2C);
		write_data(0x82);

		write_command(0xE0);
		write_data(0x01);
		write_data(0x13);
		write_data(0x1E);
		write_data(0x00);
		write_data(0x0D);
		write_data(0x03);
		write_data(0x3D);
		write_data(0x55);
		write_data(0x4F);
		write_data(0x06);
		write_data(0x10);
		write_data(0x0B);
		write_data(0x2C);
		write_data(0x32);
		write_data(0x0F);

		write_command(0xE1);
		write_data(0x08);
		write_data(0x10);
		write_data(0x15);
		write_data(0x03);
		write_data(0x0E);
		write_data(0x03);
		write_data(0x32);
		write_data(0x34);
		write_data(0x44);
		write_data(0x07);
		write_data(0x10);
		write_data(0x0E);
		write_data(0x23);
		write_data(0x2E);
		write_data(0x0F);

		/**********set rgb interface mode******************/
		write_command(0xB6);
		write_data(0x30); //set rgb
		write_data(0x02); //GS,SS
		write_data(0x3B);

		write_command(0XB0);  //Interface Mode Control
		write_data(0x00);
		 /**************************************************/
		write_command(0x2A); //Frame rate control
		write_data(0x00);
		write_data(0x00);
		write_data(0x01);
		write_data(0x3F);

		write_command(0x2B); //Display function control
		write_data(0x00);
		write_data(0x00);
		write_data(0x01);
		write_data(0xDF);

		write_command(0x21);

		write_command(0x11);
		delayms(120);
		write_command(0x29); //display on
		write_command(0x2c);

#if 0
		write_command (0x11);
		delayms(150);
		write_command (0x29);
		delayms(50);
#endif
    }
}
