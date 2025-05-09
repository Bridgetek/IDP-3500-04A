/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Gradient
C Source
*/

/*
Comment :
Introduction:
This widget draws a two-color gradient rectangle.
The gradient angle is based on "direct" property.

*/

#include "Ft_Esd_Gradient.h"

#include "Esd_Context.h"
#include "Ft_Esd_Primitives.h"

ESD_CORE_EXPORT void Esd_Noop(void *context);
ft_argb32_t Ft_Esd_Gradient_color1__Default(void *context) { return 0xfffa9943UL; }
ft_argb32_t Ft_Esd_Gradient_color2__Default(void *context) { return 0xff29a123UL; }
int Ft_Esd_Gradient_direction__Default(void *context) { return 78L; }
ft_uint8_t Ft_Esd_Gradient_Perpendicular__Default(void *context) { return ESD_PERPENDICULAR_STYLE_OFF; }
bool Ft_Esd_Gradient_Manual__Default(void *context) { return 0; }


static Ft_Esd_WidgetSlots s_Ft_Esd_Gradient__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Gradient_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_Gradient_Update,
	(void(*)(void *))Ft_Esd_Gradient_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Gradient_End,
};

static void Ft_Esd_Gradient_Render_Forwarder_ForwardRender__Signal(void *context);

void Ft_Esd_Gradient__TouchTag__Initializer(Ft_Esd_Gradient *context)
{
	Esd_TouchTag *object = (Esd_TouchTag *)&context->TouchTag;
	Esd_TouchTag__Initializer(object);
	object->Owner = (void *)context;
}

void Ft_Esd_Gradient__TouchTag_2__Initializer(Ft_Esd_Gradient *context)
{
	Ft_Esd_TouchTag *object = (Ft_Esd_TouchTag *)&context->TouchTag_2;
	Ft_Esd_TouchTag__Initializer(object);
	object->Owner = (void *)context;
}

void Ft_Esd_Gradient__Render_Forwarder__Initializer(Ft_Esd_Gradient *context)
{
	Ft_Esd_RenderForwarder *object = (Ft_Esd_RenderForwarder *)&context->Render_Forwarder;
	Ft_Esd_RenderForwarder__Initializer(object);
	object->Owner = (void *)context;
	object->Widget.Active = 1;
	object->Widget.LocalX = 0;
	object->Widget.LocalY = 0;
	object->Widget.LocalWidth = 50;
	object->Widget.LocalHeight = 50;
	object->ForwardRender = Ft_Esd_Gradient_Render_Forwarder_ForwardRender__Signal;
	Ft_Esd_Widget_InsertBottom((Ft_Esd_Widget *)object, (Ft_Esd_Widget *)context);
}

void Ft_Esd_Gradient__Initializer(Ft_Esd_Gradient *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_Gradient_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_Gradient__Slots;
	context->Widget.LocalX = 0;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 400;
	context->Widget.LocalHeight = 300;
	context->color1 = Ft_Esd_Gradient_color1__Default;
	context->color2 = Ft_Esd_Gradient_color2__Default;
	context->direction = Ft_Esd_Gradient_direction__Default;
	context->Perpendicular = Ft_Esd_Gradient_Perpendicular__Default;
	context->Manual = Ft_Esd_Gradient_Manual__Default;
	context->HideCursor = 1;
	context->Point_1_X = 100L;
	context->Point_1_Y = 100L;
	context->Point_2_X = 200L;
	context->Point_2_Y = 200L;
	Ft_Esd_Gradient__TouchTag__Initializer(context);
	Ft_Esd_Gradient__TouchTag_2__Initializer(context);
	Ft_Esd_Gradient__Render_Forwarder__Initializer(context);
}

void GradientManual_PeriodicUpdate(Ft_Esd_Gradient *context, ft_argb32_t, ft_argb32_t);
void Ft_Esd_GradientManual_TouchTracker(Ft_Esd_Gradient *context);

void Ft_Esd_Gradient_Start(Ft_Esd_Gradient *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_Start((Ft_Esd_Widget *)context);
	Esd_TouchTag_Start(&context->TouchTag);
	Ft_Esd_TouchTag_Start(&context->TouchTag_2);
}

void Ft_Esd_Gradient_Update(Ft_Esd_Gradient *context)
{
	void *owner = context->Owner;
	Esd_TouchTag_Update(&context->TouchTag);
	Ft_Esd_TouchTag_Update(&context->TouchTag_2);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context);
}

void Ft_Esd_Gradient_Render(Ft_Esd_Gradient *context)
{
	void *owner = context->Owner;
	ft_int16_t x = context->Widget.GlobalX;
	ft_int16_t y = context->Widget.GlobalY;
	bool if_1 = context->Manual(owner);
	int width;
	if (if_1)
	{
		width = 0L;
	}
	else
	{
		width = context->Widget.GlobalWidth;
	}
	bool if_2 = context->Manual(owner);
	int height;
	if (if_2)
	{
		height = 0L;
	}
	else
	{
		height = context->Widget.GlobalHeight;
	}
	ft_argb32_t color1_1 = context->color1(owner);
	ft_argb32_t color2_1 = context->color2(owner);
	int direction_1 = context->direction(owner);
	ft_uint8_t style = context->Perpendicular(owner);
	Ft_Esd_Render_Rectangle_Gradient(x, y, width, height, color1_1, color2_1, direction_1, style);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context);
}

void Ft_Esd_Gradient_End(Ft_Esd_Gradient *context)
{
	void *owner = context->Owner;
	Esd_TouchTag_End(&context->TouchTag);
	Ft_Esd_TouchTag_End(&context->TouchTag_2);
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
	Ft_Esd_Widget_Detach((Ft_Esd_Widget *)&context->Render_Forwarder); 
}

void Ft_Esd_Gradient_Render_Forwarder_ForwardRender__Signal(void *c)
{
	Ft_Esd_Gradient *context = (Ft_Esd_Gradient *)c;
	void *owner = context->Owner;
	ft_argb32_t color1_2 = context->color1(owner);
	ft_argb32_t color2_2 = context->color2(owner);
	GradientManual_PeriodicUpdate(context, color1_2, color2_2);
	Ft_Esd_GradientManual_TouchTracker(context);
}


/* end of file */
