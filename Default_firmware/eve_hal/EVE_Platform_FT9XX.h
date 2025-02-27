/**
 * @file EVE_Platform_FT9XX.h
 * @brief EVE platform for FT9XX
 *
 * @author Bridgetek
 *
 * @date 2018
 *
 * MIT License
 *
 * Copyright (c) [2019] [Bridgetek Pte Ltd (BRTChip)]
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

#ifndef EVE_PLATFORM_FT900__H
#define EVE_PLATFORM_FT900__H
/*********************
 *      INCLUDES
 *********************/
#include "EVE_Config.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

/* FT900 libraries */
#include "ft900_uart_simple.h"
#include "ft900_sdhost.h"
#include "ft900_spi.h"
#include "ft900_gpio.h"
#include "ft900_rtc.h"
#include "ft900_interrupt.h"
#include "ft900_i2cm.h"
#include "ft900.h"
#include "ft900_delay.h"

/**********************
 *      MACROS
 **********************/

#define GPIO_UART0_TX (48)
#define GPIO_UART0_RX (49)
#define GPIO_UART1_TX (52)
#define GPIO_UART1_RX (53)

#define GPIO_SPIM_CLK (27)
#define GPIO_SPIM_SS0 (28)
#define GPIO_SPIM_MOSI (29)
#define GPIO_SPIM_MISO (30)

#define GPIO_SPIM_IO2 (31)
#define GPIO_SPIM_IO3 (32)

#define GPIO_SPIM_SS1 (33)
#define GPIO_SPIM_SS2 (34)

#define GPIO_FT800_INT (0)
#define GPIO_FT800_PWD (1)

#ifdef ENABLE_KD2401
#define GPIO_KD2401_CS1 (33)
#define GPIO_KD2401_DCX (34)
#define pad_kd2401_dcx (pad_func_0)
#define pad_kd2401_cs1 (pad_func_0)
#endif

#define GPIO_SD_CLK (19)
#define GPIO_SD_CMD (20)
#define GPIO_SD_DAT3 (21)
#define GPIO_SD_DAT2 (22)
#define GPIO_SD_DAT1 (23)
#define GPIO_SD_DAT0 (24)
#define GPIO_SD_CD (25)
#define GPIO_SD_WP (26)

/* Timer 1 is been utilized in case of FT900 platform */
#define FT900_FT_MILLIS_TIMER (timer_select_b)
#define FT900_TIMER_MAX_VALUE (65536L)
#define FT900_TIMER_PRESCALE_VALUE (100)
#define FT900_TIMER_OVERFLOW_VALUE (1000)

#ifndef RTC_PRESENT
#ifdef FT900_PLATFORM_RTC_I2C
#define RTC_PRESENT (1)
#endif
#endif /* RTC_PRESENT */

/* Standard C libraries */
#define ESD_USING_NEW_LIB /**< Using NewLib C Library for runtime */

#if defined(USB_DEBUG)
#define eve_printf(fmt, ...)      \
	do                                  \
	{                                   \
		tfp_printf(fmt, ##__VA_ARGS__); \
		usbdbg_try_to_send();           \
	} while (false)
#else
#define eve_printf(fmt, ...) iprintf(fmt, ##__VA_ARGS__)
#endif
#define eve_sprintf(str, fmt, ...) siprintf(str, fmt, ##__VA_ARGS__)

#endif

/* end of file */
