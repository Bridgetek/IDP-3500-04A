
#include "Esd_Utility.h"

#include "Esd_Base.h"
#include "Esd_Scissor.h"
#include "Esd_GpuAlloc.h"
#include "Esd_TouchTag.h"
#include "Esd_Context.h"

extern ESD_CORE_EXPORT Esd_GpuAlloc *Esd_GAlloc;


#define ESD_AttachFlashFast() eve_noop()

ESD_CORE_EXPORT void Esd_BeginLogo()
{
	/* ---- */
	/* NOTE: Bypassed CoDl optimizer on purpose due to coprocessor logo behaviour */
	/* ---- */

	EVE_HalContext *phost = Esd_GetHost();
	Esd_GpuAlloc_Reset(Esd_GAlloc);
	Esd_GpuAlloc_Alloc(Esd_GAlloc, RAM_G_SIZE, 0); // Block allocation
	EVE_CoCmd_dlStart(phost);
	EVE_CoCmd_dl(phost, CLEAR_COLOR_RGB(255, 255, 255));
	EVE_CoCmd_dl(phost, CLEAR(1, 0, 0));
	EVE_CoCmd_dl(phost, DISPLAY());
	EVE_CoCmd_swap(phost);
	EVE_CoCmd_dlStart(phost);
	EVE_CoCmd_dl(phost, CLEAR_COLOR_RGB(255, 255, 255));
	EVE_CoCmd_dl(phost, CLEAR(1, 0, 0));
	EVE_CoCmd_dl(phost, DISPLAY());
	EVE_CoCmd_swap(phost);
	EVE_CoCmd_dlStart(phost);
	EVE_CoCmd_dl(phost, CLEAR_COLOR_RGB(255, 255, 255));
	EVE_CoCmd_dl(phost, CLEAR(1, 0, 0));
	EVE_CoCmd_dl(phost, DISPLAY());
	// EVE_CoCmd_memSet(Esd_Host, 0, 0xFF, RAM_G_SIZE);
	EVE_Cmd_waitFlush(phost);
	EVE_CoCmd_logo(phost);
	EVE_Cmd_waitLogo(phost);
	EVE_sleep(3000);
}

ESD_CORE_EXPORT void Esd_EndLogo()
{
	EVE_HalContext *phost = Esd_GetHost();
	EVE_CoCmd_dlStart(phost);
	EVE_CoCmd_dl(phost, CLEAR_COLOR_RGB(255, 255, 255));
	EVE_CoCmd_dl(phost, CLEAR(1, 0, 0));
	EVE_CoCmd_dl(phost, DISPLAY());
	EVE_CoCmd_swap(phost);
	EVE_Cmd_waitFlush(phost);
	Esd_GpuAlloc_Reset(Esd_GAlloc);
}

ESD_CORE_EXPORT void Esd_ShowLogo()
{
	Esd_CurrentContext->ShowLogo = true;
}

/// Run calibrate procedure
ESD_CORE_EXPORT bool Esd_Calibrate()
{
	EVE_HalContext *phost = Esd_GetHost();
	uint32_t result;
	uint32_t transMatrix[6];

#if defined(EVE_SCREEN_CAPACITIVE)
	EVE_Hal_wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
#endif

	eve_printf_debug("Esd_Calibrate: Start Frame\n");

	EVE_CoCmd_dlStart(phost);
	EVE_CoDl_clearColorRgb(phost, 64, 64, 64);
	EVE_CoDl_clear(phost, true, true, true);
	EVE_CoDl_colorRgb(phost, 0xff, 0xff, 0xff);

	// EVE_CoCmd_text(phost, (Esd_Host->Parameters.Display.Width / 2), (Esd_Host->Parameters.Display.Height / 2), 27, OPT_CENTER, "Please Tap on the dot");

	result = EVE_CoCmd_calibrate(phost);

	eve_printf_debug("Esd_Calibrate: End Frame\n");

	// Print the configured values
	EVE_Hal_rdMem(phost, (uint8_t *)transMatrix, REG_TOUCH_TRANSFORM_A, 4 * 6); // read all the 6 coefficients
	eve_printf_debug("Touch screen transform values are A 0x%lx,B 0x%lx,C 0x%lx,D 0x%lx,E 0x%lx, F 0x%lx\n",
	    (unsigned long)transMatrix[0], (unsigned long)transMatrix[1], (unsigned long)transMatrix[2],
	    (unsigned long)transMatrix[3], (unsigned long)transMatrix[4], (unsigned long)transMatrix[5]);

	return result != 0;
}

ESD_CORE_EXPORT void Esd_DeferredFree(void *ptr)
{
	// eve_printf_debug("Request free\n");
	(*(void **)ptr) = Esd_CurrentContext->DeferredFree;
	Esd_CurrentContext->DeferredFree = ptr;
}

ESD_CORE_EXPORT void Esd_ProcessFree()
{
	void *current = Esd_CurrentContext->DeferredFree;
	Esd_CurrentContext->DeferredFree = NULL;
	while (current)
	{
		void *next = (*(void **)current);
		// eve_printf_debug("Free deferred\n");
		esd_free(current);
		current = next;
	}
}

/* end of file */
