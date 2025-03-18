/*
ESD Framework
Copyright (C) 2022  Bridgetek Pte Lte
Author: Jan Boon <jan.boon@kaetemi.be>
*/

#include "Esd_AnimationInfo.h"
#include "Esd_Context.h"

#include "Esd_BitmapInfo.h"

#define ESD_ANIMATIONINFO_DEBUG_DEV

#define esd_animationinfo_printf_dev(fmt, ...) eve_printf(fmt, ##__VA_ARGS__)

#ifndef NDEBUG
#define ESD_ANIMATIONINFO_DEBUG
#endif

#ifdef ESD_ANIMATIONINFO_DEBUG
#define esd_animationinfo_printf(fmt, ...) eve_printf(fmt, ##__VA_ARGS__)
#else
#define esd_animationinfo_printf(fmt, ...) \
	do                                     \
	{                                      \
	} while (false)
#endif

extern ESD_CORE_EXPORT EVE_HalContext *Esd_Host;
extern ESD_CORE_EXPORT Esd_GpuAlloc *Esd_GAlloc;

#define ESD_NUMFRAMES_INVALID (-1)

#define ESD_METADATA_FRAMESPTR (ESD_METADATA_DATA + 0)
#define ESD_METADATA_FRAMESSIZE (ESD_METADATA_DATA + 4)
#define ESD_METADATA_ATLASBITMAPSOURCE (ESD_METADATA_DATA + 8)
#define ESD_METADATA_ATLASSIZE (ESD_METADATA_DATA + 12)
#define ESD_METADATA_RECTX (ESD_METADATA_DATA + 16)
#define ESD_METADATA_RECTY (ESD_METADATA_DATA + 18)
#define ESD_METADATA_RECTWIDTH (ESD_METADATA_DATA + 20)
#define ESD_METADATA_RECTHEIGHT (ESD_METADATA_DATA + 22)
#define ESD_METADATA_END (ESD_METADATA_DATA + 24)

/*

Animation metadata format (little-endian):

0 uint32 framesPtr; // The address of the frames file that the object file was built with
4 uint32 framesSize; // Size of the display list frames file, if 0 both frames and atlas files are ignored
8 uint32 atlasBitmapSource; // The address in bitmap source display list format of the atlas file that the frames file was built with
12 uint32 atlasSize; // Size of the ASTC bitmap atlas file, if 0 the atlas file is ignored
16 int16 rectX; // Display list bounds of the display list frames
18 int16 rectY; // Display list bounds of the display list frames
20 int16 rectWidth; // Display list bounds of the display list frames
22 int16 rectHeight; // Display list bounds of the display list frames

esdSignature must match "ANI"
version must be 1
size must match ESD_METADATA_END

*/

ESD_CORE_EXPORT uint32_t Esd_LoadAnimation(Esd_AnimationInfo *animationInfo)
{
	eve_printf("Animation not available on this target platform\n");
	return GA_INVALID;
}

ESD_CORE_EXPORT void Esd_FreeAnimation(Esd_AnimationInfo *animationInfo)
{
	Esd_FreeResource(&animationInfo->Object);
	Esd_FreeResource(&animationInfo->Frames);
	Esd_FreeResource(&animationInfo->Atlas);
	animationInfo->NumFrames = 0;
}

/* end of file */
