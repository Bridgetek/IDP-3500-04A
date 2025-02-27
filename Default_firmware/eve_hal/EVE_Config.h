/**
 * @file EVE_Config.h
 * @brief This file processes the input definitions
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

#ifndef EVE_CONFIG__H
#define EVE_CONFIG__H

/*************
** INCLUDES **
*************/
#include "EVE_IntTypes.h"

/***********
** MARCOS **
***********/

/** Chip IDs with EVE generation */
#define EVE_FT811 0x20811

/** EVE generations */
#define EVE2 2 /**< FT810 to FT813, and BT880 to BT883 */

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
/** @attention

The following values are set based on the input definitions.
Do not set these values manually; instead, use the specific user definitions.

Graphics target:
- EVE_SUPPORT_CHIPID=EVE_FT811

Platform target:
- FT9XX_PLATFORM

Display resolution:
- DISPLAY_RESOLUTION_HVGA_PORTRAIT

Additionally, the following support flags are set:
- EVE_SUPPORT_VIDEO
- EVE_SUPPORT_CMDB
- EVE_SUPPORT_MEDIAFIFO
- EVE_SUPPORT_CAPACITIVE
- EVE_SUPPORT_RESISTIVE

*/
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/** @details
IDP903-35PA
*/
#define FT811_ENABLE
#define ENABLE_SPI_QUAD

#define DISPLAY_RESOLUTION_HVGA_PORTRAIT
#define ENABLE_KD2401

#define EVE_CHIPID EVE_FT811
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/** @name Feature support.
 * \n Allows disabling specific features for debugging purposes.
 */
///@{
#define EVE_SUPPORT_VIDEO
#define EVE_SUPPORT_CMDB
#define EVE_SUPPORT_MEDIAFIFO
#define EVE_SUPPORT_LARGEFONT
#define EVE_SUPPORT_CAPACITIVE
///@}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// Other options
#define EVE_DL_OPTIMIZE 1 /**< Keep cache of displaylist values that don't often change but are generally set by every widget to reduce display list size */
#define EVE_DL_CACHE_SCISSOR 1 /**< Keep cache of current scissor */
#define EVE_DL_END_PRIMITIVE 0 /**< Whether the END command is sent */
#define EVE_DL_STATE_STACK_SIZE 4
#define EVE_DL_STATE_STACK_MASK 3

#define EVE_CMD_HOOKS 0 /**< Allow adding a callback hook into EVE_CoCmd calls using CoCmdHook in EVE_HalContext */

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define eve_progmem __flash__ const
#define eve_progmem_const __flash__ const

typedef eve_progmem int8_t eve_prog_int8_t;
typedef eve_progmem uint8_t eve_prog_uint8_t;
typedef eve_progmem uint16_t eve_prog_uint16_t;

#ifndef EVE_TCHAR_DEFINED
#define EVE_TCHAR_DEFINED
typedef char eve_tchar_t;
#endif

/* strcpy_s is not available in GCC */
#define strcpy_s(dst, sz, src) strcpy(dst, src)
#define eve_pragma_warning(msg)
#define eve_pragma_error(msg)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/* Enable FatFS by default on supported platforms */
#ifndef EVE_ENABLE_FATFS
#define EVE_ENABLE_FATFS 1
#endif

#endif /* EVE_CONFIG__H */

/* end of file */
