/*
This file is automatically generated
seagull
Header
*/

#ifndef seagull__H
#define seagull__H

#ifndef ESD_FUNCTION
#define ESD_FUNCTION(name, ...)
#endif

#include "Ft_DataTypes.h"
#include "Ft_Esd_BitmapInfo.h"

Ft_Esd_BitmapCell seagull(ft_uint16_t cell);

extern Ft_Esd_BitmapInfo seagull__Info;

ESD_FUNCTION(seagull_0, Type = Ft_Esd_BitmapCell, DisplayName = "seagull", Include = "seagull.h", Category = _GroupUserResources, Icon = ":/icons/image.png", Macro)
#define seagull_0() ((Ft_Esd_BitmapCell){ .Info = &seagull__Info, .Cell = 0 })

#endif /* seagull__H */

/* end of file */
