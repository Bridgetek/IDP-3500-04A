/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Gradient
Header
*/

#ifndef Ft_Esd_Gradient__H
#define Ft_Esd_Gradient__H

#include "Esd_Base.h"
#include "Esd_Core.h"
#include "Esd_TouchTag.h"
#include "Ft_Esd.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_RenderForwarder.h"
#include "Ft_Esd_TouchTag.h"
#include "Ft_Esd_Widget.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_ARRAY_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

#define Ft_Esd_Gradient_CLASSID 0xF4349E12
ESD_SYMBOL(Ft_Esd_Gradient_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_Gradient, Include = "Ft_Esd_Gradient.h", Callback, DisplayName = "ESD Gradient Widget", Category = EsdWidgets, Icon = ":/icons/gradient.png", X = 0, Y = 0, Width = 400, Height = 300)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_INPUT(color1, DisplayName = "start color", Type = ft_argb32_t, Default = #fa9943)
	ft_argb32_t(* color1)(void *context);
	ESD_INPUT(color2, DisplayName = "end color", Type = ft_argb32_t, Default = #29a123)
	ft_argb32_t(* color2)(void *context);
	ESD_INPUT(direction, Type = int, Default = 78)
	int(* direction)(void *context);
	ESD_INPUT(Perpendicular, DisplayName = "Perpendicular Style", Type = Esd_PerpendicularGradientStyle, Default = ESD_PERPENDICULAR_STYLE_OFF)
	ft_uint8_t(* Perpendicular)(void *context);
	ESD_INPUT(Manual, DisplayName = "Manual", Type = bool, Default = false)
	bool(* Manual)(void *context);
	ESD_VARIABLE(HideCursor, DisplayName = "HideCursor", Type = ft_bool_t, Default = true, Public)
	ft_bool_t HideCursor;
	ESD_VARIABLE(Point_1_X, DisplayName = "Point_1_X", Type = int, Default = 100, Public)
	int Point_1_X;
	ESD_VARIABLE(Point_1_Y, DisplayName = "Point_1_Y", Type = int, Default = 100, Public)
	int Point_1_Y;
	ESD_VARIABLE(Point_2_X, DisplayName = "Point_2_X", Type = int, Default = 200, Public)
	int Point_2_X;
	ESD_VARIABLE(Point_2_Y, DisplayName = "Point_2_Y", Type = int, Default = 200, Public)
	int Point_2_Y;
	Esd_TouchTag TouchTag;
	Ft_Esd_TouchTag TouchTag_2;
	Ft_Esd_RenderForwarder Render_Forwarder;
} Ft_Esd_Gradient;

void Ft_Esd_Gradient__Initializer(Ft_Esd_Gradient *context);

ESD_SLOT(Start)
void Ft_Esd_Gradient_Start(Ft_Esd_Gradient *context);

ESD_SLOT(Update)
void Ft_Esd_Gradient_Update(Ft_Esd_Gradient *context);

ESD_SLOT(Render)
void Ft_Esd_Gradient_Render(Ft_Esd_Gradient *context);

ESD_SLOT(End)
void Ft_Esd_Gradient_End(Ft_Esd_Gradient *context);

#endif /* Ft_Esd_Gradient__H */

/* end of file */
