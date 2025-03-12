/*
This file is automatically generated
chess
Header
*/

#ifndef chess__H
#define chess__H

#ifndef ESD_FUNCTION
#define ESD_FUNCTION(name, ...)
#endif

#include "Ft_DataTypes.h"
#include "Ft_Esd_BitmapInfo.h"

Ft_Esd_BitmapCell chess(ft_uint16_t cell);

extern Ft_Esd_BitmapInfo chess__Info;

ESD_FUNCTION(chess_0, Type = Ft_Esd_BitmapCell, DisplayName = "chess", Include = "chess.h", Category = _GroupUserResources, Icon = ":/icons/image.png", Macro)
#define chess_0() ((Ft_Esd_BitmapCell){ .Info = &chess__Info, .Cell = 0 })

#endif /* chess__H */

/* end of file */
