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
 */

#include "Esd_Context.h"
#include "Esd_Utility.h"

#include "Esd_GpuAlloc.h"
#include "Esd_LittleFS.h"
#include "Esd_Scissor.h"
#include "Esd_BitmapHandle.h"
#include "Esd_TouchTag.h"
#include "Esd_CoWidget.h"


//
// Globals
//
ESD_CORE_EXPORT Esd_Context *Esd_CurrentContext = NULL;
ESD_CORE_EXPORT EVE_HalContext *Esd_Host = NULL; // Pointer to current s_Host
ESD_CORE_EXPORT Esd_GpuAlloc *Esd_GAlloc = NULL; // Pointer to current s_GAlloc

#ifdef ESD_MEMORYPOOL_ALLOCATOR
ESD_CORE_EXPORT Esd_MemoryPool *Esd_MP = NULL;
#endif

//
// External definitions
//
#if defined(_DEBUG)
void Esd_CheckTypeSizes();
#endif

void Esd_CoWidget_Render();

// When not in the simulation, use the Esd_Main__Start etc symbols
// as exported by the single Application logic document included
#define Esd_IsRunning__ESD() true

//
// Constants
//
#define FT_WELCOME_MESSAGE "Copyright (C) Bridgetek Pte Ltd\n"

ESD_CORE_EXPORT void Esd_SetCurrent(Esd_Context *ec)
{
	Esd_CurrentContext = ec;
	Esd_Host = &ec->HalContext;
	Esd_GAlloc = &ec->GpuAlloc;
}

ESD_CORE_EXPORT void Esd_Defaults(Esd_Parameters *ep)
{
	memset(ep, 0, sizeof(Esd_Parameters));
#ifdef ESD_FLASH_FILES
#ifdef _WIN32
	wcscpy_s(ep->FlashFilePaths[ESD_FLASH_BT815], _countof(ep->FlashFilePaths[ESD_FLASH_BT815]), L"__Flash.bin");
#else
	strcpy(ep->FlashFilePaths[ESD_FLASH_BT815], "__Flash.bin");
#endif
#endif
#ifdef ESD_MEMORYPOOL_ALLOCATOR
	ep->MaxPoolMemory = 72456;
	ep->IdealPoolMemory = 36228;
#endif
}

bool cbCmdWait(struct EVE_HalContext *phost)
{
	Esd_Context *ec = (Esd_Context *)phost->UserContext;

	/* Loop an idle task instead of doing nothing */
	if (ec->Idle)
		ec->Idle(ec->UserContext);
	/* EVE_Hal_idle(&ec->HalContext); */ /* Already called by EVE HAL */
	ec->SwapIdled = true;

	return Esd_IsRunning__ESD() && !ec->RequestStop;
}

ESD_CORE_EXPORT void Esd_Initialize()
{
	EVE_Hal_initialize();

	eve_printf_debug(FT_WELCOME_MESSAGE);

#if defined(_DEBUG)
	Esd_CheckTypeSizes();
#endif
}


ESD_CORE_EXPORT bool Esd_Open(Esd_Context *ec, Esd_Parameters *ep)
{
	EVE_HalContext *phost;
	EVE_CHIPID_T chipId;
	size_t deviceIdx;

	memset(ec, 0, sizeof(Esd_Context));
	ec->ClearColor = 0x212121;
	ec->Start = ep->Start;
	ec->Update = ep->Update;
	ec->Render = ep->Render;
	ec->Idle = ep->Idle;
	ec->End = ep->End;
	ec->UserContext = ep->UserContext;

	ec->MediaFifoHandle = GA_HANDLE_INVALID;
	Esd_SetCurrent(ec);


	/* Interactive device selection */
	EVE_Util_selectDeviceInteractive(&chipId, &deviceIdx);

	{
		EVE_HalParameters params;
#ifdef ESD_FLASH_FILES
		bool updateFlash = false;
		bool updateFlashFirmware = false;
		eve_tchar_t flashPath[260];
		flashPath[0] = '\0';
#endif

		EVE_Hal_defaultsEx(&params, deviceIdx);
		params.UserContext = ec;
		params.CbCmdWait = cbCmdWait;

#ifdef ESD_FLASH_FILES
		if (chipId >= EVE_BT815 || (chipId <= 0 && ep->FlashFilePaths[EVE_gen(chipId) - EVE3][0]))
		{
			EVE_Util_selectFlashFileInteractive(flashPath, sizeof(flashPath) / sizeof(flashPath[0]), &updateFlash, &updateFlashFirmware, &params, ep->FlashFilePaths[(chipId > 0) ? (EVE_gen(chipId) - EVE3) : 0]); /* FIXME: EVE_Util_selectFlashFileInteractive needs to take all the options, as it detects chipId as well */
		}
#endif


		if (!EVE_Hal_open(&ec->HalContext, &params))
			return false;

#ifdef ESD_FLASH_FILES
		if (updateFlash && flashPath[0])
			EVE_Util_uploadFlashFileInteractive(&ec->HalContext, flashPath, updateFlashFirmware);
#endif
	}

	phost = &ec->HalContext;
	if (!(EVE_Util_bootupConfigInteractive(phost, EVE_DISPLAY_DEFAULT)))
	{
		EVE_Hal_close(&ec->HalContext);
		return false;
	}

	{
		// TODO: Store calibration somewhere
		if (!Esd_Calibrate())
		{
			eve_printf_debug("Calibrate failed\n");
		}
	}

	esd_scope()
	{
		/* Show spinner at startup */
		EVE_CoCmd_dlStart(phost);
		EVE_CoDl_clearColorRgb_ex(phost, ec->ClearColor); // Set CLEAR_COLOR_RGB from user var
		EVE_CoDl_clearTag(phost, 255); // Always default to 255, so no touch = 0, touch non-tag = 255
		EVE_CoDl_clear(phost, true, true, true);
		EVE_CoDl_colorRgb_ex(phost, ~(ec->ClearColor));
		Esd_CoWidget_Spinner(Esd_Update, phost->Width >> 1, phost->Height >> 1, 0, 0);
		ec->SpinnerPopup = false;
		ec->SpinnerPopped = true;
	}

	ec->GpuAlloc.RamGSize = RAM_G_SIZE;
	Esd_GpuAlloc_Reset(&ec->GpuAlloc);

#ifdef ESD_MEMORYPOOL_ALLOCATOR
	eve_printf_debug("[Esd MemoryPool] use user config mem allocation, config as max %d, ideal %d\n",
	    (int)ep->MaxPoolMemory, ep->IdealPoolMemory < ep->MaxPoolMemory ? (int)ep->IdealPoolMemory : (int)ep->MaxPoolMemory);
	Esd_MP = Esd_MemoryPool_Init(
	    ep->MaxPoolMemory, ep->IdealPoolMemory < ep->MaxPoolMemory ? ep->IdealPoolMemory : ep->MaxPoolMemory);
#endif

	Esd_BitmapHandle_Initialize();

	return true;
}

ESD_CORE_EXPORT void Esd_Close(Esd_Context *ec)
{
	Esd_ProcessFree();
#ifdef ESD_LITTLEFS_FLASH
	Esd_LittleFS_Unmount();
#endif
	EVE_Hal_close(&ec->HalContext);

#ifdef ESD_MEMORYPOOL_ALLOCATOR
	Esd_MemoryPool_Destroy(Esd_MP);
	eve_printf_debug("[Esd MemoryPool] esd close, memory usage is %d\n", Esd_MemoryPool_GetTotalUsed(Esd_MP));
#endif

	memset(ec, 0, sizeof(Esd_Context));
	Esd_CurrentContext = NULL;
	Esd_Host = NULL;
	Esd_GAlloc = NULL;
}

ESD_CORE_EXPORT void Esd_Release()
{
	EVE_Hal_release();
}

ESD_CORE_EXPORT void Esd_Loop(Esd_Context *ec)
{
	EVE_HalContext *phost = &ec->HalContext;
	Esd_SetCurrent(ec);
	(void)phost;

	if (!Esd_IsRunning__ESD() || ec->RequestStop)
		return;

	Esd_Start(ec);

	while (Esd_IsRunning__ESD() && !ec->RequestStop)
	{
		Esd_Update(ec);
		Esd_Render(ec);
		Esd_WaitSwap(ec);
	}

	Esd_Stop(ec);
}

ESD_CORE_EXPORT void Esd_Start(Esd_Context *ec)
{
	Esd_SetCurrent(ec);

	// Initialize framework
	ec->Frame = 0;
	ec->Millis = EVE_millis();

	// Initialize storage
	EVE_Util_loadSdCard(&ec->HalContext);

	// Initialize application
	if (ec->Start)
	{
		ec->Start(ec->UserContext);
	}
}

ESD_CORE_EXPORT void Esd_Update(Esd_Context *ec)
{
	uint32_t ms;

	EVE_HalContext *phost = &ec->HalContext;
	Esd_SetCurrent(ec);

	// Restore initial frame values
	// EVE_CoCmd_loadIdentity(phost); // ?
	Esd_ProcessFree();
	Esd_BitmapHandle_FrameStart(&ec->HandleState);

	if (ec->ShowLogo)
		return;
	if (ec->ShowingLogo)
		ec->Millis = EVE_millis(); // Reset time

	// Verify initialization
	EVE_Util_loadSdCard(phost); // Does this really need phost???

	// Idle at least once every frame
	ec->LoopState = ESD_LOOPSTATE_IDLE;
	if (!ec->SwapIdled)
	{
		if (ec->Idle)
			ec->Idle(ec->UserContext);
		EVE_Hal_idle(phost);
	}

	// Update GUI state before render
	ec->LoopState = ESD_LOOPSTATE_UPDATE;
	ms = EVE_millis(); // Calculate frame time delta
	ec->DeltaMs = ms - ec->Millis;
	ec->Millis = ms;
	Esd_GpuAlloc_Update(Esd_GAlloc); // Run GC
	Esd_TouchTag_Update(NULL); // Update touch
	if (ec->AnimationChannelsSetup)
		ec->AnimationChannelsActive = EVE_Hal_rd32(phost, REG_ANIM_ACTIVE);
	else
		ec->AnimationChannelsActive = 0;
	if (ec->Update)
		ec->Update(ec->UserContext);
		// Esd_Timer_UpdateGlobal(); // TODO

#ifdef ESD_MEMORYPOOL_ALLOCATOR
	eve_printf_debug_once("[Esd MemoryPool] esd update, memory usage is %d\n", Esd_MemoryPool_GetTotalUsed(Esd_MP));
#endif

	// Return to idle state inbetween
	ec->LoopState = ESD_LOOPSTATE_IDLE;
}

ESD_CORE_EXPORT void Esd_Render(Esd_Context *ec)
{
	EVE_HalContext *phost = &ec->HalContext;
	Esd_SetCurrent(ec);

	if (ec->ShowLogo)
	{
		ec->ShowLogo = false;
		ec->ShowingLogo = true;
		Esd_BeginLogo();
		return;
	}

	if (ec->ShowingLogo)
	{
		ec->ShowingLogo = false;
		Esd_EndLogo();
	}

	if (ec->HalContext.CmdFault)
	{
		/* Don't process render if update faulted */
		return;
	}

	// DEBUG: Reset bitmap handles to always setup bitmap handles on every frame
	// Esd_BitmapHandle_Reset(&ec->HandleState);

	// Process all coprocessor commands
	ec->LoopState = ESD_LOOPSTATE_RENDER;
#if defined(_DEBUG)
	// This will cause a dark red screen in case background video incorrectly swaps the display
	EVE_Hal_startTransfer(phost, EVE_TRANSFER_WRITE, RAM_DL);
	EVE_Hal_transfer32(phost, CLEAR_COLOR_RGB(0x40, 0x00, 0x20));
	EVE_Hal_transfer32(phost, CLEAR(1, 1, 1));
	EVE_Hal_transfer32(phost, DISPLAY());
	EVE_Hal_endTransfer(phost);
#endif
	EVE_CoCmd_dlStart(phost);
	Esd_CoWidget_Render();
	EVE_CoDl_clearColorRgb_ex(phost, ec->ClearColor); // Set CLEAR_COLOR_RGB from user var
	EVE_CoDl_clearTag(phost, 255); // Always default to 255, so no touch = 0, touch non-tag = 255
	EVE_CoDl_clear(phost, true, true, true);
	if (ec->Render)
		ec->Render(ec->UserContext);

	if (ec->SpinnerPopup)
	{
		// Spinner used for switching longer loading pages with bitmaps etc
		EVE_CoDl_colorRgb_ex(phost, ~(ec->ClearColor));
		Esd_CoWidget_Spinner(Esd_Update, phost->Width >> 1, phost->Height >> 1, 0, 0);
		ec->SpinnerPopup = false;
		ec->SpinnerPopped = true;
	}
	else if (ec->SpinnerPopped)
	{
		Esd_CoWidget_Stop(Esd_Update);
		ec->SpinnerPopped = false;
	}

	if (!ec->SpinnerPopped)
	{
		EVE_CoDl_display(phost);
		EVE_CoDl_display(phost); //Issue 1100, appending one extra DISPLAY instruction to avoid potential bitmap corruption issue on BT81x
		EVE_CoCmd_swap(phost);
	}

	// Replacement for Ft_Gpu_Hal_WaitCmdfifo_empty(phost); with idle function
	ec->LoopState = ESD_LOOPSTATE_IDLE;

	// Advance frame count
	++ec->Frame;
}

ESD_CORE_EXPORT bool Esd_WaitSwap(Esd_Context *ec)
{
	EVE_HalContext *phost = &ec->HalContext;
	Esd_SetCurrent(ec);
	(void)phost;

	ec->SwapIdled = false;
	EVE_Cmd_waitFlush(&ec->HalContext);
	ec->HasReset = false;

	/* Reset the coprocessor in case of fault */
	if (ec->HalContext.CmdFault)
	{
#if defined(_DEBUG)
		/* Show error for a while */
		EVE_sleep(1000);
#endif

		/* TODO: Create a utility function that resets the coprocessor and all cached state */
		EVE_Util_resetCoprocessor(&ec->HalContext);
		Esd_BitmapHandle_Reset(&ec->HandleState);
		ec->AnimationChannelsSetup = 0;
#ifdef ESD_LITTLEFS_FLASH
		if (ec->LfsUnflushed)
		{
			ec->LfsCmdFault = true;
			Esd_GpuAlloc_Free(Esd_GAlloc, ec->LfsEraseHandle);
		}
#endif
		ec->HasReset = true;

		return false;
	}

	while (EVE_Hal_rd8(phost, REG_DLSWAP) != 0)
		; // TODO: Handle wait abort

	return true;
}

ESD_CORE_EXPORT void Esd_Stop(Esd_Context *ec)
{
	Esd_SetCurrent(ec);

	// Cleanup application (generally unreachable)
	ec->LoopState = ESD_LOOPSTATE_NONE;
	// Esd_Timer_CancelGlobal(); // TODO
	if (ec->End)
		ec->End(ec->UserContext);
}

/* Implements a generic main function, for reference only */
/*
int Esd_Main(int argc, char *argv[])
{
    Esd_Initialize();

    Esd_Parameters ep;
    Esd_Defaults(&ep);
    ep.Start = Main_Start;
    ep.Update = Main_Update;
    ep.Render = Main_Render;
    ep.Idle = Main_Idle;
    ep.End = Main_End;
    Esd_Context ec;

    Esd_Open(&ec, &ep);
    Esd_Loop(&ec);
    Esd_Close(&ec);

    Esd_Release();
    return EXIT_SUCCESS;
}
*/

/* end of file */
