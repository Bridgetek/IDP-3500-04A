/**
 * @file EVE_Hal.h
 * @brief Main file to include the EVE HAL in your applications
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

#ifndef EVE_HAL__H
#define EVE_HAL__H

/*************
** INCLUDES **
*************/
#include "EVE_Platform.h"

/**********************
** GLOBAL PROTOTYPES **
**********************/

/** @name INIT */
///@{
/**
 * @brief Eve_Hal framework initialization
 *
 * @return EVE_HalPlatform* Poniter to EVE_HalPlatform struct
 */
EVE_HalPlatform *EVE_Hal_initialize();

/**
 * @brief Close Eve_Hal framework
 *
 */
void EVE_Hal_release();

/**
 * @brief Setup default parameters for Eve_Hal framework
 *
 * @param parameters Pointer to EVE_HalParameters
 */
void EVE_Hal_defaults(EVE_HalParameters *parameters);

/**
 * @brief Setup default parameters for Eve_Hal framework
 *
 * @param parameters Pointer to EVE_HalParameters
 * @param deviceIdx
 */
void EVE_Hal_defaultsEx(EVE_HalParameters *parameters, size_t deviceIdx);

/**
 * @brief Open the Eve_Hal framework
 *
 * @param phost Pointer to Hal context
 * @param parameters Pointer to EVE_HalParameters
 * @return true True if ok
 * @return false False if error
 */
bool EVE_Hal_open(EVE_HalContext *phost, const EVE_HalParameters *parameters);

/**
 * @brief Close the Eve_Hal framework
 *
 * @param phost Pointer to Hal context
 */
void EVE_Hal_close(EVE_HalContext *phost);

/**
 * @brief Idle handler for Eve_Hal framework
 *
 * @param phost Pointer to Hal context
 */
void EVE_Hal_idle(EVE_HalContext *phost);

///@}

/** @name TRANSFER HELPERS */
///@{

/**
 * @brief Read 8 bits from Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be read
 * @return uint8_t Data from Coprocessor
 */
uint8_t EVE_Hal_rd8(EVE_HalContext *phost, uint32_t addr);

/**
 * @brief Read 2 bytes from Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be read
 * @return uint16_t Data from Coprocessor
 */
uint16_t EVE_Hal_rd16(EVE_HalContext *phost, uint32_t addr);

/**
 * @brief Read 4 bytes from Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be read
 * @return uint16_t Data from Coprocessor
 */
uint32_t EVE_Hal_rd32(EVE_HalContext *phost, uint32_t addr);
/**
 * @brief Read a block data from Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param result Buffer where data write to
 * @param addr Address to bbe read
 * @param size Size to be read
 */
void EVE_Hal_rdMem(EVE_HalContext *phost, uint8_t *result, uint32_t addr, uint32_t size);

/**
 * @brief Write 8 bits to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param v Value to write
 */
void EVE_Hal_wr8(EVE_HalContext *phost, uint32_t addr, uint8_t v);

/**
 * @brief Write 2 bytes to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param v Value to write
 */
void EVE_Hal_wr16(EVE_HalContext *phost, uint32_t addr, uint16_t v);

/**
 * @brief Write 4 bytes to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param v Value to write
 */
void EVE_Hal_wr32(EVE_HalContext *phost, uint32_t addr, uint32_t v);

/**
 * @brief Write a buffer to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param buffer Data to be write
 * @param size Size of buffer
 */
void EVE_Hal_wrMem(EVE_HalContext *phost, uint32_t addr, const uint8_t *buffer, uint32_t size);

/**
 * @brief Write a buffer in ProgMem to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param buffer Data to be write
 * @param size Size of buffer
 */
void EVE_Hal_wrProgMem(EVE_HalContext *phost, uint32_t addr, eve_progmem_const uint8_t *buffer, uint32_t size);

/**
 * @brief Write a string to Coprocessor's memory
 *
 * @param phost Pointer to Hal context
 * @param addr Address to be write
 * @param str String to be write
 * @param index Start postion in the string
 * @param size Size of the string
 * @param padMask Padding mask
 */
void EVE_Hal_wrString(EVE_HalContext *phost, uint32_t addr, const char *str, uint32_t index, uint32_t size, uint32_t padMask);
///@}

/** @name HOST */
///@{

/**
 * @brief Select clock source for Coprocessor
 *
 * @param phost Pointer to Hal context
 * @param pllsource Clock source
 */
void EVE_Host_clockSelect(EVE_HalContext *phost, EVE_PLL_SOURCE_T pllsource);

/**
 * @brief Select system clock for Coprocessor
 *
 * @param phost Pointer to Hal context
 * @param freq Frequency to set
 */
void EVE_Host_pllFreqSelect(EVE_HalContext *phost, EVE_PLL_FREQ_T freq);

/**
 * @brief Switch power mode for Coprocessor
 *
 * @param phost Pointer to Hal context
 * @param pwrmode Power mode
 */
void EVE_Host_powerModeSwitch(EVE_HalContext *phost, EVE_POWER_MODE_T pwrmode);

/**
 * @brief Send reset signal to Coprocessor
 *
 * @param phost Pointer to Hal context
 */
void EVE_Host_coreReset(EVE_HalContext *phost);

/**
 * @brief Set system clock for Coprocessor
 * This API can only be called when PLL is stopped(SLEEP mode).
 * For compatibility, set frequency to the EVE_GPU_12MHZ option in the EVE_SETPLLSP1_T table.
 *
 * @param phost Pointer to Hal context
 * @param freq Frequency to set
 */
void EVE_Host_selectSysClk(EVE_HalContext *phost, EVE_81X_PLL_FREQ_T freq);

/**
 * @brief Power off a component
 *
 * @param phost Pointer to Hal context
 * @param val Component number
 */
void EVE_Host_powerOffComponents(EVE_HalContext *phost, uint8_t val);

/**
 * @brief Set the drive strength for various pins
 * This API sets the current strength of supported GPIO/IO group(s)
 *
 * @param phost Pointer to Hal context
 * @param strength Drive strength
 * @param group Pin group to set
 */
void EVE_Host_padDriveStrength(EVE_HalContext *phost, EVE_81X_GPIO_DRIVE_STRENGTH_T strength, EVE_81X_GPIO_GROUP_T group);

/**
 * @brief Hold the device in reset state
 * This API will hold the system reset active, EVE_Host_resetRemoval() must be called to release the system reset.
 *
 * @param phost Pointer to Hal context
 */
void EVE_Host_resetActive(EVE_HalContext *phost);

/**
 * @brief Exit reset state, Eve will power on and enter into its default state
 * This API will release the system reset,and the system will exit reset and behave 
 * as after POR, settings done through SPI commands will not be affected.
 *
 * @param phost Pointer to Hal context
 */
void EVE_Host_resetRemoval(EVE_HalContext *phost);
///@}

/** @name DEBUG */
///@{

/** Display a fullscreen debug message using TEXT8X8.
Uses the back of RAM_G. */
void EVE_Hal_displayMessage(EVE_HalContext *phost, const char *str, uint16_t size);
///@}

#endif /* #ifndef EVE_HAL__H */

/* end of file */
