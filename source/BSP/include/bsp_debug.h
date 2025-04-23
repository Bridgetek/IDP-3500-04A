#ifndef _BSP_DEBUG_H_
#define _BSP_DEBUG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "usbdbg.h"
#include "tinyprintf.h"

#if ENABLE_USBDBG
#define PR_ERROR(fmt, ...)              \
	do                                  \
	{                                   \
        tfp_printf("[ERROR]");          \
		tfp_printf(fmt, ##__VA_ARGS__); \
		usbdbg_try_to_send();           \
	} while (false)

#define PR_WARN(fmt, ...)               \
	do                                  \
	{                                   \
        tfp_printf("[WARNING]");        \
		tfp_printf(fmt, ##__VA_ARGS__); \
		usbdbg_try_to_send();           \
	} while (false)

#define PR_INFO(fmt, ...)               \
	do                                  \
	{                                   \
        tfp_printf("[INFO]");           \
		tfp_printf(fmt, ##__VA_ARGS__); \
		usbdbg_try_to_send();           \
	} while (false)


#define eve_printf(fmt, ...)      \
	do                                  \
	{                                   \
		tfp_printf(fmt, ##__VA_ARGS__); \
		usbdbg_try_to_send();           \
	} while (false)

#else
#define PR_ERROR(fmt, ...) iprintf(fmt, ##__VA_ARGS__)
#define PR_WARN(fmt, ...) iprintf(fmt, ##__VA_ARGS__)
#define PR_INFO(fmt, ...) iprintf(fmt, ##__VA_ARGS__)
#define eve_printf(fmt, ...) iprintf(fmt, ##__VA_ARGS__)
#endif
#define eve_sprintf(str, fmt, ...) siprintf(str, fmt, ##__VA_ARGS__)
#endif /* _BSP_DEBUG_H_ */
