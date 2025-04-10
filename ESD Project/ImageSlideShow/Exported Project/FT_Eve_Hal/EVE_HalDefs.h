/**
 * This source code ("the Software") is provided by Bridgetek Pte Ltd
 * ("Bridgetek") subject to the licence terms set out
 *   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
 * You must read the Licence Terms before downloading or using the Software.
 * By installing or using the Software you agree to the Licence Terms. If you
 * do not agree to the Licence Terms then do not download or use the Software.
 *
 * Without prejudice to the Licence Terms, here is a summary of some of the key
 * terms of the Licence Terms (and in the event of any conflict between this
 * summary and the Licence Terms then the text of the Licence Terms will
 * prevail).
 *
 * The Software is provided "as is".
 * There are no warranties (or similar) in relation to the quality of the
 * Software. You use it at your own risk.
 * The Software should not be used in, or for, any medical device, system or
 * appliance. There are exclusions of Bridgetek liability for certain types of loss
 * such as: special loss or damage; incidental loss or damage; indirect or
 * consequential loss or damage; loss of income; loss of business; loss of
 * profits; loss of revenue; loss of contracts; business interruption; loss of
 * the use of money or anticipated savings; loss of information; loss of
 * opportunity; loss of goodwill or reputation; and/or loss of, damage to or
 * corruption of data.
 * There is a monetary cap on Bridgetek's liability.
 * The Software may have subsequently been amended by another user and then
 * distributed by that other user ("Adapted Software").  If so that user may
 * have additional licence terms that apply to those amendments. However, Bridgetek
 * has no liability in relation to those amendments.
 *
 * File Description:
 *    This file defines the generic APIs of phost access layer for the FT800 or EVE compatible silicon.
 *    Application shall access FT800 or EVE resources over these APIs,regardless of I2C or SPI protocol.
 *    In addition, there are some helper functions defined for FT800 coprocessor engine as well as phost commands.
 *
 */

#ifndef EVE_HAL_INCL__H
#define EVE_HAL_INCL__H
#include "EVE_GpuTypes.h"

#include "ff.h"

/**********
** ENUMS **
**********/

typedef enum EVE_MODE_T
{
	EVE_MODE_UNKNOWN = 0,
	EVE_MODE_I2C,
	EVE_MODE_SPI,
} EVE_MODE_T;

typedef enum EVE_STATUS_T
{
	EVE_STATUS_CLOSED = 0,
	EVE_STATUS_OPENED,
	EVE_STATUS_READING,
	EVE_STATUS_WRITING,
	EVE_STATUS_ERROR,
} EVE_STATUS_T;

typedef enum EVE_TRANSFER_T
{
	EVE_TRANSFER_NONE = 0,
	EVE_TRANSFER_READ,
	EVE_TRANSFER_WRITE,
} EVE_TRANSFER_T;

typedef enum EVE_CHIPID_T
{
	EVE_CHIPID_FT800 = EVE_FT800,
	EVE_CHIPID_FT801 = EVE_FT801,
	EVE_CHIPID_FT810 = EVE_FT810,
	EVE_CHIPID_FT811 = EVE_FT811,
	EVE_CHIPID_FT812 = EVE_FT812,
	EVE_CHIPID_FT813 = EVE_FT813,
	EVE_CHIPID_BT880 = EVE_BT880,
	EVE_CHIPID_BT881 = EVE_BT881,
	EVE_CHIPID_BT882 = EVE_BT882,
	EVE_CHIPID_BT883 = EVE_BT883,
	EVE_CHIPID_BT815 = EVE_BT815,
	EVE_CHIPID_BT816 = EVE_BT816,
	EVE_CHIPID_BT817 = EVE_BT817,
	EVE_CHIPID_BT818 = EVE_BT818,
} EVE_CHIPID_T;

#define RAM_ERR_REPORT_MAX 128

/************
** STRUCTS **
************/

typedef struct EVE_HalContext EVE_HalContext;
typedef bool (*EVE_Callback)(EVE_HalContext *phost);

/* Hook into coprocessor commands. Return 1 to abort the command. Useful for an optimization routine */
typedef int (*EVE_CoCmdHook)(EVE_HalContext *phost, uint32_t cmd, uint32_t state);
/* Hook into coprocessor reset */
typedef void (*EVE_ResetCallback)(EVE_HalContext *phost, bool fault);


typedef enum EVE_HOST_T
{
	EVE_HOST_UNKNOWN = 0,
	EVE_HOST_BT8XXEMU,
	EVE_HOST_FT4222,
	EVE_HOST_MPSSE,
	EVE_HOST_EMBEDDED,

	EVE_HOST_NB
} EVE_HOST_T;

typedef struct EVE_DeviceInfo
{
	char DisplayName[256];
	char SerialNumber[16];
	EVE_HOST_T Host;
	bool Opened;

} EVE_DeviceInfo;

/* Hal parameters */
typedef struct EVE_HalParameters
{
	void *UserContext;

	/* Called anytime the code is waiting during CMD write. Return false to abort wait */
	EVE_Callback CbCmdWait;





	uint32_t DeviceIdx;
	uint8_t SpiCsPin; /* SPI chip select number of FT8XX chip */


	uint8_t PowerDownPin; /* FT8XX power down pin number */


} EVE_HalParameters;

#if EVE_DL_OPTIMIZE || EVE_DL_CACHE_SCISSOR
#define EVE_DL_STATE phost->DlState[phost->DlStateIndex]
typedef struct EVE_HalDlState
{
	// Keep to a minimum
#if (EVE_DL_OPTIMIZE)
	uint32_t PaletteSource;
	uint32_t ColorRGB;
	int16_t LineWidth;
	int16_t PointSize;
#endif
#if (EVE_DL_CACHE_SCISSOR)
	uint16_t ScissorX;
	uint16_t ScissorY;
	uint16_t ScissorWidth;
	uint16_t ScissorHeight;
#endif
#if (EVE_DL_OPTIMIZE)
	uint8_t ColorA;
	uint8_t Handle; // Current handle
	uint8_t Cell; // Current cell
#endif
	uint8_t VertexFormat; // Current vertex format
#if (EVE_DL_OPTIMIZE)
	bool BitmapTransform; // BitmapTransform other than default is set
#endif
} EVE_HalDlState;
#endif

typedef struct EVE_HalContext
{
	/* Pointer to user context */
	void *UserContext;

	/* Pointer to a support library context (e.g. ESD Framework context) */
	void *LibraryContext;

	/* Called anytime the code is waiting during CMD write. Return false to abort wait */
	EVE_Callback CbCmdWait;
	/* Callback hook called anytime the coprocessor is reset through the EVE_Util interface */
	EVE_ResetCallback CbCoprocessorReset;

#if EVE_CMD_HOOKS
	/* Hook into coprocessor commands. Called when EVE_CoCmd interface is used. Return 1 to abort the command. Useful for an optimization routine */
	EVE_CoCmdHook CoCmdHook;
#endif

	EVE_STATUS_T Status;


	uint8_t PCLK;

	/* User space width and height,
	based on REG_HSIZE, REG_VSIZE and REG_ROTATE */
	uint32_t Width;
	uint32_t Height;

	/* Handles to external context */

	EVE_SPI_CHANNELS_T SpiChannels; /* Variable to contain single/dual/quad channels */
	uint8_t SpiDummyBytes; /* Number of dummy bytes as 1 or 2 for SPI read */

	uint8_t SpiCsPin; /* SPI chip select number of FT8XX chip */
	uint8_t PowerDownPin; /* FT8XX power down pin number */

	/* Write buffer to optimize writes into larger batches */

	/* Buffer cmd smaller than a full cmd command */
	uint8_t CmdBuffer[4];
	uint8_t CmdBufferIndex;

	uint16_t CmdSpace; /* Free space, cached value */

	/* Media FIFO state */
	uint32_t MediaFifoAddress;
	uint32_t MediaFifoSize;
	FIL LoadFileObj;
	ptrdiff_t LoadFileRemaining;

	/* Display list optimization and compatibility caches */
#if EVE_DL_OPTIMIZE || EVE_DL_CACHE_SCISSOR
	EVE_HalDlState DlState[EVE_DL_STATE_STACK_SIZE];
	uint8_t DlStateIndex;
#endif
#if (EVE_DL_OPTIMIZE)
	uint8_t DlPrimitive;
	uint32_t CoFgColor;
	uint32_t CoBgColor;
	bool CoBitmapTransform; /* BitmapTransform other than identity is set on the coprocessor */
#endif
	uint8_t CoScratchHandle;

#if defined(_DEBUG)
	bool DebugMessageVisible;
	uint8_t DebugBackup[RAM_ERR_REPORT_MAX];
#endif

	/* Status flags */
	bool CmdFunc; /* Flagged while transfer to cmd is kept open */
	bool CmdFault; /* Flagged when coprocessor is in fault mode and needs to be reset */
	bool CmdWaiting; /* Flagged while waiting for CMD write (to check during any function that may be called by CbCmdWait) */

} EVE_HalContext;

typedef struct EVE_HalPlatform
{
	uint32_t OpenedDevices;

} EVE_HalPlatform;

/*********
** INIT **
*********/

/* Initialize HAL platform */
EVE_HAL_EXPORT EVE_HalPlatform *EVE_Hal_initialize();

/* Release HAL platform */
EVE_HAL_EXPORT void EVE_Hal_release();

/* List the available devices */
EVE_HAL_EXPORT size_t EVE_Hal_list();

/* Get info of the specified device. Devices of type EVE_HOST_UNKNOWN should be ignored */
EVE_HAL_EXPORT void EVE_Hal_info(EVE_DeviceInfo *deviceInfo, size_t deviceIdx);

/* Check whether the context is the specified device */
EVE_HAL_EXPORT bool EVE_Hal_isDevice(EVE_HalContext *phost, size_t deviceIdx);

/* Get the default configuration parameters */
EVE_HAL_EXPORT void EVE_Hal_defaults(EVE_HalParameters *parameters);

/* Get the default configuration parameters.
Use `deviceIdx` to choose the connected device, or set to -1 to get the first available device. */
EVE_HAL_EXPORT void EVE_Hal_defaultsEx(EVE_HalParameters *parameters, size_t deviceIdx);

/* Opens a new HAL context using the specified parameters */
EVE_HAL_EXPORT bool EVE_Hal_open(EVE_HalContext *phost, const EVE_HalParameters *parameters);

/* Close a HAL context */
EVE_HAL_EXPORT void EVE_Hal_close(EVE_HalContext *phost);

/* Idle. Call regularly to update frequently changing internal state.
This is also called while waiting for cmd, in addition to the user idle callback */
EVE_HAL_EXPORT void EVE_Hal_idle(EVE_HalContext *phost);

/*************
** TRANSFER **
*************/

EVE_HAL_EXPORT void EVE_Hal_startTransfer(EVE_HalContext *phost, EVE_TRANSFER_T rw, uint32_t addr);
EVE_HAL_EXPORT uint8_t EVE_Hal_transfer8(EVE_HalContext *phost, uint8_t value);
EVE_HAL_EXPORT uint16_t EVE_Hal_transfer16(EVE_HalContext *phost, uint16_t value);
EVE_HAL_EXPORT uint32_t EVE_Hal_transfer32(EVE_HalContext *phost, uint32_t value);
EVE_HAL_EXPORT void EVE_Hal_transferMem(EVE_HalContext *phost, uint8_t *result, const uint8_t *buffer, uint32_t size);
EVE_HAL_EXPORT void EVE_Hal_transferProgMem(EVE_HalContext *phost, uint8_t *result, eve_progmem_const uint8_t *buffer, uint32_t size);
EVE_HAL_EXPORT uint32_t EVE_Hal_transferString(EVE_HalContext *phost, const char *str, uint32_t index, uint32_t size, uint32_t padMask);
EVE_HAL_EXPORT void EVE_Hal_endTransfer(EVE_HalContext *phost);

/* Flush any pending write transfers */
EVE_HAL_EXPORT void EVE_Hal_flush(EVE_HalContext *phost);

/*********************
** TRANSFER HELPERS **
*********************/

EVE_HAL_EXPORT uint8_t EVE_Hal_rd8(EVE_HalContext *phost, uint32_t addr);
EVE_HAL_EXPORT uint16_t EVE_Hal_rd16(EVE_HalContext *phost, uint32_t addr);
EVE_HAL_EXPORT uint32_t EVE_Hal_rd32(EVE_HalContext *phost, uint32_t addr);
EVE_HAL_EXPORT void EVE_Hal_rdMem(EVE_HalContext *phost, uint8_t *result, uint32_t addr, uint32_t size);

EVE_HAL_EXPORT void EVE_Hal_wr8(EVE_HalContext *phost, uint32_t addr, uint8_t v);
EVE_HAL_EXPORT void EVE_Hal_wr16(EVE_HalContext *phost, uint32_t addr, uint16_t v);
EVE_HAL_EXPORT void EVE_Hal_wr32(EVE_HalContext *phost, uint32_t addr, uint32_t v);
EVE_HAL_EXPORT void EVE_Hal_wrMem(EVE_HalContext *phost, uint32_t addr, const uint8_t *buffer, uint32_t size);
EVE_HAL_EXPORT void EVE_Hal_wrProgMem(EVE_HalContext *phost, uint32_t addr, eve_progmem_const uint8_t *buffer, uint32_t size);
EVE_HAL_EXPORT void EVE_Hal_wrString(EVE_HalContext *phost, uint32_t addr, const char *str, uint32_t index, uint32_t size, uint32_t padMask);

/*********
** CAPS **
*********/

/* Screen based on chip id. This function compiles as a constant on single supported chipid target */
static inline bool EVE_Hal_isScreenCapacitive(EVE_HalContext *phost)
{
	return (EVE_CHIPID & 0x01) == 0x01;
}

/* Screen based on chip id. This function compiles as a constant on single supported chipid target */
static inline bool EVE_Hal_isScreenResistive(EVE_HalContext *phost)
{
	return !EVE_Hal_isScreenCapacitive(phost);
}

static inline bool EVE_Hal_supportHsf(EVE_HalContext *phost)
{
	return false;
}

static inline bool EVE_Hal_supportFlash(EVE_HalContext *phost)
{
	return false;
}

static inline bool EVE_Hal_supportCmdB(EVE_HalContext *phost)
{
	return EVE_CHIPID >= EVE_FT810;
}

static inline bool EVE_Hal_supportMediaFifo(EVE_HalContext *phost)
{
	return EVE_CHIPID >= EVE_FT810;
}

static inline bool EVE_Hal_supportVideo(EVE_HalContext *phost)
{
	return EVE_CHIPID >= EVE_FT810;
}

static inline bool EVE_Hal_supportLargeFont(EVE_HalContext *phost)
{
	return false;
}

/// Include the EVE generation in the chip ID value to simplify feature set comparisons (BT880 support)
static inline EVE_CHIPID_T EVE_extendedChipId(int chipId)
{
	switch (chipId & 0xFFFF)
	{
	case EVE_FT800 & 0xFFFF:
	case EVE_FT801 & 0xFFFF:
		return (EVE_CHIPID_T)((chipId & 0xFFFF) | 0x10000);
	case EVE_FT810 & 0xFFFF:
	case EVE_FT811 & 0xFFFF:
	case EVE_FT812 & 0xFFFF:
	case EVE_FT813 & 0xFFFF:
	case EVE_BT880 & 0xFFFF:
	case EVE_BT881 & 0xFFFF:
	case EVE_BT882 & 0xFFFF:
	case EVE_BT883 & 0xFFFF:
		return (EVE_CHIPID_T)((chipId & 0xFFFF) | 0x20000);
	case EVE_BT815 & 0xFFFF:
	case EVE_BT816 & 0xFFFF:
		return (EVE_CHIPID_T)((chipId & 0xFFFF) | 0x30000);
	case EVE_BT817 & 0xFFFF:
	case EVE_BT818 & 0xFFFF:
		return (EVE_CHIPID_T)((chipId & 0xFFFF) | 0x40000);
	default:
		break;
	}
	return (EVE_CHIPID_T)(chipId & 0xFFFF);
}

/// Remove EVE generation from the chip ID
static inline int EVE_shortChipId(EVE_CHIPID_T chipId)
{
	return chipId & 0xFFFF;
}

static inline int EVE_gen(EVE_CHIPID_T chipId)
{
	switch (chipId)
	{
	case EVE_FT800:
	case EVE_FT801:
		return EVE1;
	case EVE_FT810:
	case EVE_FT811:
	case EVE_FT812:
	case EVE_FT813:
	case EVE_BT880:
	case EVE_BT881:
	case EVE_BT882:
	case EVE_BT883:
		return EVE2;
	case EVE_BT815:
	case EVE_BT816:
		return EVE3;
	case EVE_BT817:
	case EVE_BT818:
		return EVE4;
	default:
		break;
	}
	return 0;
}

/************
** UTILITY **
************/

EVE_HAL_EXPORT void EVE_Hal_hostCommand(EVE_HalContext *phost, uint8_t cmd);

/* This API sends a 3byte command to the phost */
EVE_HAL_EXPORT void EVE_Hal_hostCommandExt3(EVE_HalContext *phost, uint32_t cmd);

/* Toggle PD_N pin of FT800 board for a power cycle. Returns false on failure */
EVE_HAL_EXPORT bool EVE_Hal_powerCycle(EVE_HalContext *phost, bool up);

/* Switch EVE to different SPI channel mode */
EVE_HAL_EXPORT void EVE_Hal_setSPI(EVE_HalContext *phost, EVE_SPI_CHANNELS_T numchnls, uint8_t numdummy);

/* Restore platform to previously configured EVE SPI channel mode */
EVE_HAL_EXPORT void EVE_Hal_restoreSPI(EVE_HalContext *phost);

EVE_HAL_EXPORT uint32_t EVE_Hal_currentFrequency(EVE_HalContext *phost);

EVE_HAL_EXPORT int32_t EVE_Hal_clockTrimming(EVE_HalContext *phost, uint32_t lowFreq);

/*********
** HOST **
*********/

EVE_HAL_EXPORT void EVE_Host_clockSelect(EVE_HalContext *phost, EVE_PLL_SOURCE_T pllsource);
EVE_HAL_EXPORT void EVE_Host_pllFreqSelect(EVE_HalContext *phost, EVE_PLL_FREQ_T freq);
EVE_HAL_EXPORT void EVE_Host_powerModeSwitch(EVE_HalContext *phost, EVE_POWER_MODE_T pwrmode);
EVE_HAL_EXPORT void EVE_Host_coreReset(EVE_HalContext *phost);

/* This API can only be called when PLL is stopped(SLEEP mode).
For compatibility, set frequency to the EVE_GPU_12MHZ option in the EVE_SETPLLSP1_T table. */
EVE_HAL_EXPORT void EVE_Host_selectSysClk(EVE_HalContext *phost, EVE_81X_PLL_FREQ_T freq);

/* Power down or up ROMs and ADCs.*/
EVE_HAL_EXPORT void EVE_Host_powerOffComponents(EVE_HalContext *phost, uint8_t val);

/* This API sets the current strength of supported GPIO/IO group(s) */
EVE_HAL_EXPORT void EVE_Host_padDriveStrength(EVE_HalContext *phost, EVE_81X_GPIO_DRIVE_STRENGTH_T strength, EVE_81X_GPIO_GROUP_T group);

/* This API will hold the system reset active,
EVE_Host_resetRemoval() must be called to release the system reset. */
EVE_HAL_EXPORT void EVE_Host_resetActive(EVE_HalContext *phost);

/* This API will release the system reset,
and the system will exit reset and behave as after POR,
settings done through SPI commands will not be affected. */
EVE_HAL_EXPORT void EVE_Host_resetRemoval(EVE_HalContext *phost);

/**********
** DEBUG **
**********/

/* Display a fullscreen debug message using TEXT8X8.
Uses the back of RAM_G. */
EVE_HAL_EXPORT void EVE_Hal_displayMessage(EVE_HalContext *phost, const char *str, uint16_t size);

/* Display a fullscreen debug message using TEXT8X8.
Uses the back of RAM_G. */
#define EVE_Hal_displayMessageZ(phost, str) EVE_Hal_displayMessage((phost), (str), (uint16_t)strlen((str)))

/*********
** MISC **
*********/

EVE_HAL_EXPORT uint32_t EVE_millis();
EVE_HAL_EXPORT uint64_t EVE_millis64();
EVE_HAL_EXPORT void EVE_sleep(uint32_t ms);

#endif /* #ifndef EVE_HAL_INCL__H */

/* end of file */
