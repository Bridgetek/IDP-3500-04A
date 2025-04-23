#include <stdio.h>
#include "bsp_debug.h"
#include "bsp_hwdefs.h"
#include "rotary.h"

uint8_t read_rotary(void)
{
	static bool rotsw_initialized = false;
	uint8_t	id = 0;
	if (!rotsw_initialized) {
		gpio_dir(SWITCH_ID0, pad_dir_input);
		gpio_dir(SWITCH_ID1, pad_dir_input);
		gpio_dir(SWITCH_ID2, pad_dir_input);
		gpio_dir(SWITCH_ID3, pad_dir_input);
		rotsw_initialized = true;
	}
	id = (uint8_t)((gpio_read(SWITCH_ID0)) | (gpio_read(SWITCH_ID1) << 1) | (gpio_read(SWITCH_ID2) << 2) | (gpio_read(SWITCH_ID3) << 3)) & 0xF;
	return id;
}