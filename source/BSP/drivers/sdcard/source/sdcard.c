/**
 * @file sdcard.c
 * @brief sd card API
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
#include "bsp_hwdefs.h"
#include "ff.h"

#define MOUNT_POINT ""

static bool s_FatFSLoaded = false;
static FATFS s_FatFS;

void initSdHost(void)
{
	/* All SD Host pins except CLK need a pull-up to work. The MM900EV*A module does not have external pull-up, so enable internal one */
	gpio_function(GPIO_SD_CLK, pad_sd_clk);
	gpio_pull(GPIO_SD_CLK, pad_pull_none);
	gpio_function(GPIO_SD_CMD, pad_sd_cmd);
	gpio_pull(GPIO_SD_CMD, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT3, pad_sd_data3);
	gpio_pull(GPIO_SD_DAT3, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT2, pad_sd_data2);
	gpio_pull(GPIO_SD_DAT2, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT1, pad_sd_data1);
	gpio_pull(GPIO_SD_DAT1, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT0, pad_sd_data0);
	gpio_pull(GPIO_SD_DAT0, pad_pull_pullup);
	gpio_function(GPIO_SD_CD, pad_sd_cd);
	gpio_pull(GPIO_SD_CD, pad_pull_pullup);
	gpio_function(GPIO_SD_WP, pad_sd_wp);
	gpio_pull(GPIO_SD_WP, pad_pull_pullup);

	/* Start up the SD Card */
	sys_enable(sys_device_sd_card);
	sdhost_init();
}

/**
 * @brief Mount the SDcard
 *
 * @param phost Pointer to Hal context
 * @return true True if ok
 * @return false False if error
 */
bool loadSdCard(void)
{
	SDHOST_STATUS status = sdhost_card_detect();
	if (status == SDHOST_CARD_INSERTED)
	{
		if (!s_FatFSLoaded && (f_mount(&s_FatFS, MOUNT_POINT, 1) != FR_OK))
		{
			printf("FatFS SD card mount failed\n");
		}
		else
		{
			printf("FatFS SD card mounted successfully\n");
			s_FatFSLoaded = true;
		}
	}
	else
	{
		printf("SD card not detected\n");
		s_FatFSLoaded = false;
	}
	return s_FatFSLoaded;
}

bool sdCardReady(void)
{
	return s_FatFSLoaded;
}

size_t readFile(uint8_t *buffer, size_t size, const char *filename)
{
	// Read up to `size` number of bytes from the file into `buffer`, then return the number of read bytes
	FRESULT fResult;
	FIL InfSrc;

	if (!s_FatFSLoaded)
	{
		printf("SD card not ready\n");
		return false;
	}

	fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	if (fResult == FR_DISK_ERR)
	{
		printf("Re-mount SD card\n");
		s_FatFSLoaded = false;
		sdhost_init();
		loadSdCard();
		fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	}
	if (fResult == FR_OK)
	{
		size_t read;
		fResult = f_read(&InfSrc, buffer, size, &read);
		f_close(&InfSrc);
		return read;
	}
	else
	{
		printf("Unable to open file: \"%s\"\n", filename);
		return 0;
	}
}

/* end of file */
