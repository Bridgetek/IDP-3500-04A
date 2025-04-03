/*
 * bsp_hwdefs.h.h
 *
 */
#ifndef _BSP_HWDEFS_H_
#define _BSP_HWDEFS_H_

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

#define GPIO_KD2401_CS1 (33)
#define GPIO_KD2401_DCX (34)
#define pad_kd2401_dcx (pad_func_0)
#define pad_kd2401_cs1 (pad_func_0)

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

#endif // _BSP_HWDEFS_H_