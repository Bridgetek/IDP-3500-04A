/**
 * @file EVE_CoCmd_IO.c
 * @brief EVE's co-processor IO commmands
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

#include "EVE_Platform.h"

bool EVE_CoCmd_memCrc(EVE_HalContext *phost, uint32_t ptr, uint32_t num, uint32_t *result)
{
	uint16_t resAddr;

#if EVE_CMD_HOOKS
	if (phost->CoCmdHook && phost->CoCmdHook(phost, CMD_MEMCRC, 0))
		return false;
#endif

	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_MEMCRC);
	EVE_Cmd_wr32(phost, ptr);
	EVE_Cmd_wr32(phost, num);
	resAddr = EVE_Cmd_moveWp(phost, 4);
	EVE_Cmd_endFunc(phost);

	/* Read result */
	if (result)
	{
		if (!EVE_Cmd_waitFlush(phost))
			return false;
		*result = EVE_Hal_rd32(phost, RAM_CMD + resAddr);
	}
	return true;
}

bool EVE_CoCmd_regRead(EVE_HalContext *phost, uint32_t ptr, uint32_t *result)
{
	uint16_t resAddr;

#if EVE_CMD_HOOKS
	if (phost->CoCmdHook && phost->CoCmdHook(phost, CMD_REGREAD, 0))
		return false;
#endif

	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_REGREAD);
	EVE_Cmd_wr32(phost, ptr);
	resAddr = EVE_Cmd_moveWp(phost, 4);
	EVE_Cmd_endFunc(phost);

	/* Read result */
	if (result)
	{
		if (!EVE_Cmd_waitFlush(phost))
			return false;
		*result = EVE_Hal_rd32(phost, RAM_CMD + resAddr);
	}
	return true;
}

void EVE_CoCmd_memWrite(EVE_HalContext *phost, uint32_t ptr, uint32_t num)
{
	EVE_CoCmd_ddd(phost, CMD_MEMWRITE, ptr, num);
}

/**
 * @brief Send CMD_MEMWRITE, followed by a single 32-bit value.
 *
 * Convenience function to write one 32-bit value through the coprocessor.
 * Useful in combination with EVE_Cmd_waitRead32 to add synchronization points into the command buffer.
 *
 * @param phost Pointer to Hal context
 * @param ptr Destination on RAM_G
 * @param value Value to write
 */
void EVE_CoCmd_memWrite32(EVE_HalContext *phost, uint32_t ptr, uint32_t value)
{
	EVE_CoCmd_dddd(phost, CMD_MEMWRITE, ptr, 4, value);
}

/**
 * @brief Send CMD_MEMSET
 *
 * @param phost Pointer to Hal context
 * @param ptr starting address of the memory block
 * @param value value to be written to memory
 * @param num number of bytes in the memory block
 */
void EVE_CoCmd_memSet(EVE_HalContext *phost, uint32_t ptr, uint32_t value, uint32_t num)
{
	EVE_CoCmd_dddd(phost, CMD_MEMSET, ptr, value, num);
}

/**
 * @brief Send CMD_MEMZERO
 *
 * @param phost Pointer to Hal context
 * @param ptr Destination on RAM_G
 * @param num number of bytes to clear
 */
void EVE_CoCmd_memZero(EVE_HalContext *phost, uint32_t ptr, uint32_t num)
{
	EVE_CoCmd_ddd(phost, CMD_MEMZERO, ptr, num);
}

/**
 * @brief Send CMD_MEMCPY
 *
 * @param phost Pointer to Hal context
 * @param dest address of the destination memory block
 * @param src address of the source memory block
 * @param num number of bytes to copy
 */
void EVE_CoCmd_memCpy(EVE_HalContext *phost, uint32_t dest, uint32_t src, uint32_t num)
{
	EVE_CoCmd_dddd(phost, CMD_MEMCPY, dest, src, num);
}

/**
 * @brief Send CMD_APPEND
 *
 * @param phost  Pointer to Hal context
 * @param ptr Start of source commands in main memory
 * @param num Number of bytes to copy. This must be a multiple of 4
 */
void EVE_CoCmd_append(EVE_HalContext *phost, uint32_t ptr, uint32_t num)
{
	EVE_CoCmd_ddd(phost, CMD_APPEND, ptr, num);
}

/**
 * @brief Send CMD_SNAPSHOT
 *
 * @param phost Pointer to Hal context
 * @param ptr Snapshot destination address, in RAM_G
 */
void EVE_CoCmd_snapshot(EVE_HalContext *phost, uint32_t ptr)
{
	EVE_CoCmd_dd(phost, CMD_SNAPSHOT, ptr);
}

/**
 * @brief Send CMD_INFLATE. Data must follow this command
 *
 * @param phost Pointer to Hal context
 * @param ptr Destination address
 */
void EVE_CoCmd_inflate(EVE_HalContext *phost, uint32_t ptr)
{
	EVE_CoCmd_dd(phost, CMD_INFLATE, ptr);
}

bool EVE_CoCmd_inflate_progMem(EVE_HalContext *phost, uint32_t dst, eve_progmem_const uint8_t *src, uint32_t size)
{
	if (!EVE_Cmd_waitFlush(phost))
		return false; // Coprocessor must be ready
	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_INFLATE);
	EVE_Cmd_wr32(phost, dst);
	EVE_Cmd_wrProgMem(phost, src, (size + 3) & ~0x3UL);
	EVE_Cmd_endFunc(phost);
	return EVE_Cmd_waitFlush(phost); // Resource failed to load
}

/** @brief Get the end memory address of data inflated by CMD_INFLATE and CMD_INFLATE2
 * At API level 2, the allocation pointer is also advanced by:
 *  - cmd_loadimage
 *  - cmd_playvideo
 *  - cmd_videoframe
 *  - cmd_endlist
 */
bool EVE_CoCmd_getPtr(EVE_HalContext *phost, uint32_t *result)
{
	uint16_t resAddr;

#if EVE_CMD_HOOKS
	if (phost->CoCmdHook && phost->CoCmdHook(phost, CMD_GETPTR, 0))
		return false;
#endif

	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_GETPTR);
	resAddr = EVE_Cmd_moveWp(phost, 4); // move write pointer to result location
	EVE_Cmd_endFunc(phost);

	/* Read result */
	if (result)
	{
		if (!EVE_Cmd_waitFlush(phost))
			return false;
		*result = EVE_Hal_rd32(phost, RAM_CMD + resAddr);
	}
	return true;
}

void EVE_CoCmd_loadImage(EVE_HalContext *phost, uint32_t ptr, uint32_t options)
{
	EVE_CoCmd_ddd(phost, CMD_LOADIMAGE, ptr, options);
}

bool EVE_CoCmd_loadImage_progMem(EVE_HalContext *phost, uint32_t dst, eve_progmem_const uint8_t *src, uint32_t size, uint32_t *format)
{
#if EVE_CMD_HOOKS
	if (phost->CoCmdHook && phost->CoCmdHook(phost, CMD_LOADIMAGE, dst))
		return false;
#endif

	if (!EVE_Cmd_waitFlush(phost))
		return false; // Coprocessor must be ready
	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_LOADIMAGE);
	EVE_Cmd_wr32(phost, dst);
	EVE_Cmd_wr32(phost, OPT_NODL);
	EVE_Cmd_wrProgMem(phost, src, (size + 3) & ~0x3UL);
	EVE_Cmd_endFunc(phost);
	if (!EVE_Cmd_waitFlush(phost))
		return false; // Image failed to load
	if (format)
		*format = EVE_Hal_rd32(phost, 0x3097e8);
	return true;
}

bool EVE_CoCmd_getProps(EVE_HalContext *phost, uint32_t *ptr, uint32_t *w, uint32_t *h)
{
	uint16_t resAddr;

#if EVE_CMD_HOOKS
	if (phost->CoCmdHook && phost->CoCmdHook(phost, CMD_GETPROPS, 0))
		return false;
#endif

	EVE_Cmd_startFunc(phost);
	EVE_Cmd_wr32(phost, CMD_GETPROPS);
	resAddr = EVE_Cmd_moveWp(phost, 12);
	EVE_Cmd_endFunc(phost);

	/* Read result */
	if (ptr || w || h)
	{
		if (!EVE_Cmd_waitFlush(phost))
			return false;
		if (ptr)
			*ptr = EVE_Hal_rd32(phost, RAM_CMD + resAddr);
		if (w)
			*w = EVE_Hal_rd32(phost, RAM_CMD + resAddr + 4);
		if (h)
			*h = EVE_Hal_rd32(phost, RAM_CMD + resAddr + 8);
	}
	return true;
}

void EVE_CoCmd_snapshot2(EVE_HalContext *phost, uint32_t fmt, uint32_t ptr, int16_t x, int16_t y, int16_t w, int16_t h)
{
	EVE_CoCmd_dddwwww(phost, CMD_SNAPSHOT2, fmt, ptr, x, y, w, h);
}

void EVE_CoCmd_mediaFifo(EVE_HalContext *phost, uint32_t ptr, uint32_t size)
{
	EVE_CoCmd_ddd(phost, CMD_MEDIAFIFO, ptr, size);
}

void EVE_CoCmd_videoStart(EVE_HalContext *phost)
{
	EVE_CoCmd_d(phost, CMD_VIDEOSTART);
}

void EVE_CoCmd_videoFrame(EVE_HalContext *phost, uint32_t dst, uint32_t ptr)
{
	EVE_CoCmd_ddd(phost, CMD_VIDEOFRAME, dst, ptr);
}

void EVE_CoCmd_playVideo(EVE_HalContext *phost, uint32_t options)
{
	EVE_CoCmd_dd(phost, CMD_PLAYVIDEO, options);

#if (EVE_DL_OPTIMIZE)
	phost->DlPrimitive = 0;
#endif

	if (options & OPT_MEDIAFIFO)
	{
		EVE_CoCmd_memCpy(phost, 0, 0, 1);
	}
}

/* end of file */
