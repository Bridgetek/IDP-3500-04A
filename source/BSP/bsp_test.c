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
#include "rotary.h"
#include "max31725.h"

#define SW_BUILDDATE_STR __DATE__
#define SW_BUILDTIME_STR __TIME__
#define SW_TIMESTAMP_STR __DATE__ " " __TIME__
#define APP_TITLE_STR	 "IDP-3500-04A Application"

#define ENABLE_SD       1
#define ENABLE_EVE      1
#define ENABLE_LED      1
#define ENABLE_TEMP     1

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

	PR_INFO("rotary ID %d\n", read_rotary());

#if ENABLE_LED
	gpio_function(RGB_LED_RED_GPIO, pad_gpio57);
	gpio_dir(RGB_LED_RED_GPIO, pad_dir_output);
	gpio_pull(RGB_LED_RED_GPIO, pad_pull_none);
	gpio_write(RGB_LED_RED_GPIO, 1);
	gpio_function(RGB_LED_GREEN_GPIO, pad_gpio56);
	gpio_dir(RGB_LED_GREEN_GPIO, pad_dir_output);
	gpio_pull(RGB_LED_GREEN_GPIO, pad_pull_none);
	gpio_write(RGB_LED_GREEN_GPIO, 1);

	// red light
	gpio_write(RGB_LED_GREEN_GPIO, 1);
	gpio_write(RGB_LED_RED_GPIO, 0);
	PR_INFO("LED red light\n");
#endif

#if ENABLE_TEMP
	int err = 0;
	for (int i = 0; i < 3; i++) {
		err = max31725_init();
		if (err == 0)
			break;
	}
	if (err < 0) {
		PR_ERROR("Temperature sensor max31725_init(): err = %d\n", err);
	}
	else {
		PR_INFO("Temperature sensor initialised\n");
		float temp = max31725_deg_C();
		if (temp < -128.0) {
#if ENABLE_USBDBG
			PR_ERROR("ERROR: max31725_deg_C() = %ld deg\n", (uint32_t)temp); // Tinyprint not support %f
#else
			PR_ERROR("ERROR: max31725_deg_C() = %f deg\n", temp);
#endif
		}
		else {
#if ENABLE_USBDBG
			PR_INFO("max31725_deg_C() = %ld deg_C\n", (uint32_t)temp);
#else
			PR_INFO("max31725_deg_C() = %f deg_C\n", temp);
#endif
		}
	}
#endif

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

#if ENABLE_LED
	// green light
	gpio_write(RGB_LED_RED_GPIO, 1);
	gpio_write(RGB_LED_GREEN_GPIO, 0);
	PR_INFO("LED green light\n");
#endif
}

#if ENABLE_USBDBG
void tfp_putc(void* p, char c)
{
	(void)(p);
	usbdbg_write_byte(c);
}
#endif


