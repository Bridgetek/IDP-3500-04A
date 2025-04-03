/**
 * @file bsp_test.c
 * @brief Sample usage of IDP-3500-04A BSP
 *
 * @author Bridgetek
 *
 * @date 2025
 * 
 * MIT License
 *
 * Copyright (c) [2025] [Bridgetek Pte Ltd (BRTChip)]
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "eve_app.h"
#include "sdcard.h"

#define SW_BUILDDATE_STR __DATE__
#define SW_BUILDTIME_STR __TIME__
#define SW_TIMESTAMP_STR __DATE__ " " __TIME__
#define APP_TITLE_STR	 "IDP-3500-04A Application"

#define ENABLE_SD       1
#define ENABLE_EVE      1

void init_bsp(void);
#if ENABLE_USBDBG
void tfp_putc(void* p, char c);
#endif

int main()
{
	init_bsp();

	while (true) {
		;
	}
}

void init_bsp(void)
{
	sys_reset_all();

	interrupt_enable_globally();

	sys_enable(sys_device_uart0);
	gpio_function(GPIO_UART0_TX, pad_uart0_txd); /* UART0 TXD */
	gpio_function(GPIO_UART0_RX, pad_uart0_rxd); /* UART0 RXD */
	uart_open(UART0, /* Device */
		1, /* Prescaler = 1 */
		UART_DIVIDER_115200_BAUD, /* Divider = 1302 */
		uart_data_bits_8, /* No. Data Bits */
		uart_parity_none, /* Parity */
		uart_stop_bits_1); /* No. Stop Bits */

#if ENABLE_USBDBG
	/* Init the tinyprintf module */
	init_printf(NULL, tfp_putc);
	/* Initialize the USB Debugging */
	usbdbg_init();
	delayms(1000);
#endif

	PR_INFO("\n%s\n", APP_TITLE_STR);
	PR_INFO("Build date: %s, %s\n", SW_BUILDDATE_STR, SW_BUILDTIME_STR);

#if ENABLE_SD
	initSdHost();
	if (!loadSdCard()) {
		PR_WARN("FATFS mount fail\n");
	}
	else {
		PR_INFO("FATFS mounted\n");
	}
#endif /* ENABLE_SD */

#if ENABLE_EVE
	if (!Gpu_Init())
	{
		PR_WARN("EVE initial fail\n");
	}
	else {
		PR_INFO("EVE initialised\n");
	}

	Eve_Calibrate();
#endif /* ENABLE_EVE */
}

#if ENABLE_USBDBG
void tfp_putc(void* p, char c)
{
	(void)(p);
	usbdbg_write_byte(c);
}
#endif


