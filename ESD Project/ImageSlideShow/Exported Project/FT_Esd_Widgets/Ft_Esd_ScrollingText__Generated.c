/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_ScrollingText
C Source
*/

#include "Ft_Esd_ScrollingText.h"

#include "Esd_Context.h"
#include "Esd_BitmapHandle.h"

ESD_CORE_EXPORT void Esd_Noop(void *context);

static Ft_Esd_Theme * Ft_Esd_ScrollingText_ESD_Label_Theme__Property(void *context);
static uint8_t Ft_Esd_ScrollingText_ESD_Label_Font__Property(void *context);
static Esd_FontInfo * Ft_Esd_ScrollingText_ESD_Label_FontResource__Property(void *context);
static const char * Ft_Esd_ScrollingText_ESD_Label_Text__Property(void *context);
static ft_uint16_t Ft_Esd_ScrollingText_ESD_Label_AlignY__Property(void *context) { return OPT_ALIGN_CENTER; }

static Ft_Esd_WidgetSlots s_Ft_Esd_ScrollingText__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Widget_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_ScrollingText_Update,
	(void(*)(void *))Ft_Esd_Widget_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_ScrollingText_End,
};


void Ft_Esd_ScrollingText__Fixed_Positioning__Initializer(Ft_Esd_ScrollingText *context)
{
	Ft_Esd_Layout_Fixed *object = (Ft_Esd_Layout_Fixed *)&context->Fixed_Positioning;
	Ft_Esd_Layout_Fixed__Initializer(object);
	object->Owner = (void *)context;
	object->Widget.Active = 1;
	object->Widget.LocalX = 0;
	object->Widget.LocalY = 0;
	object->Widget.LocalWidth = 50;
	object->Widget.LocalHeight = 50;
	Ft_Esd_Widget_InsertBottom((Ft_Esd_Widget *)object, (Ft_Esd_Widget *)context);
}

void Ft_Esd_ScrollingText__ESD_Label__Initializer(Ft_Esd_ScrollingText *context)
{
	Ft_Esd_Label *object = (Ft_Esd_Label *)&context->ESD_Label;
	Ft_Esd_Label__Initializer(object);
	object->Owner = (void *)context;
	object->Widget.Active = 1;
	object->Widget.LocalX = 0;
	object->Widget.LocalY = 0;
	object->Widget.LocalWidth = 321;
	object->Widget.LocalHeight = 156;
	object->Theme = Ft_Esd_ScrollingText_ESD_Label_Theme__Property;
	object->Font = Ft_Esd_ScrollingText_ESD_Label_Font__Property;
	object->FontResource = Ft_Esd_ScrollingText_ESD_Label_FontResource__Property;
	object->Text = Ft_Esd_ScrollingText_ESD_Label_Text__Property;
	object->AlignY = Ft_Esd_ScrollingText_ESD_Label_AlignY__Property;
	Ft_Esd_Widget_InsertBottom((Ft_Esd_Widget *)object, (Ft_Esd_Widget *)&context->Fixed_Positioning);
}

void Ft_Esd_ScrollingText__Initializer(Ft_Esd_ScrollingText *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_ScrollingText_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_ScrollingText__Slots;
	context->Widget.LocalX = -2;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 320;
	context->Widget.LocalHeight = 37;
	context->GlobalX = 0L;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Variable_2 = 0L;
	context->Font_Resource = 0;
	context->Font = 28L;
	context->Text = "Welcome to EVE Screen Designer";
	context->Position = NONE;
	context->Speed = 1L;
	Ft_Esd_ScrollingText__Fixed_Positioning__Initializer(context);
	Ft_Esd_ScrollingText__ESD_Label__Initializer(context);
}

static uint16_t Ft_Esd_ScrollingText_Get_Font_X_Offset__return(Ft_Esd_ScrollingText *context);
static uint16_t Ft_Esd_ScrollingText_Get_Font_Height__return(Ft_Esd_ScrollingText *context);

ESD_CORE_EXPORT Esd_FontInfo *Esd_GetRomFont(uint8_t);
ESD_CORE_EXPORT uint16_t Esd_GetFontXOffset(Esd_FontInfo *);
ESD_CORE_EXPORT uint16_t Esd_GetFontBaseLine(Esd_FontInfo *);
ESD_CORE_EXPORT uint16_t Esd_GetFontHeight(Esd_FontInfo *);
int Ft_Esd_ScrollingTextCheckValue(Ft_Esd_ScrollingText *context, int, int, int, char *);

void Ft_Esd_ScrollingText_Update__Builtin(Ft_Esd_ScrollingText *context)
{
	void *owner = context->Owner;
	uint16_t update_variable = Ft_Esd_ScrollingText_Get_Font_Height__return(context);
	Ft_Esd_Widget_SetHeight((Ft_Esd_Widget *)context, update_variable);
	ft_int16_t update_variable_1 = context->Widget.GlobalX;
	context->GlobalX = update_variable_1;
	int left = context->Variable_2;
	int left_1 = context->Position;
	int right_1 = context->Speed;
	int right = left_1 * right_1;
	int update_variable_2 = left + right;
	Ft_Esd_Widget_SetX((Ft_Esd_Widget *)&context->ESD_Label, update_variable_2);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context);
}

void Ft_Esd_ScrollingText_End(Ft_Esd_ScrollingText *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
	Ft_Esd_Widget_Detach((Ft_Esd_Widget *)&context->Fixed_Positioning); 
	Ft_Esd_Widget_Detach((Ft_Esd_Widget *)&context->ESD_Label); 
}

void Ft_Esd_ScrollingText_Update(Ft_Esd_ScrollingText *context)
{
	void *owner = context->Owner;
	ft_int16_t x = context->ESD_Label.Widget.LocalX;
	uint16_t left_2 = Ft_Esd_ScrollingText_Get_Font_X_Offset__return(context);
	Esd_FontInfo * if_1 = context->Font_Resource;
	Esd_FontInfo *fontInfo;
	if (if_1)
	{
		fontInfo = context->Font_Resource;
	}
	else
	{
		int i = context->Font;
		fontInfo = Esd_GetRomFont(i);
	}
	uint16_t right_2 = Esd_GetFontBaseLine(fontInfo);
	int fontBaseLine = left_2 + right_2;
	uint16_t left_3 = Ft_Esd_ScrollingText_Get_Font_X_Offset__return(context);
	uint16_t right_3 = Ft_Esd_ScrollingText_Get_Font_Height__return(context);
	int fontHeight = left_3 + right_3;
	const char * str = context->ESD_Label.Text(context->ESD_Label.Owner);
	int set_variable_3 = Ft_Esd_ScrollingTextCheckValue(context, x, fontBaseLine, fontHeight, str);
	context->Variable_2 = set_variable_3;
	Ft_Esd_ScrollingText_Update__Builtin(context);
}

uint16_t Ft_Esd_ScrollingText_Get_Font_X_Offset__return(Ft_Esd_ScrollingText *context)
{
	void *owner = context->Owner;
	Esd_FontInfo * if_2 = context->Font_Resource;
	Esd_FontInfo *fontInfo_1;
	if (if_2)
	{
		fontInfo_1 = context->Font_Resource;
	}
	else
	{
		int i_1 = context->Font;
		fontInfo_1 = Esd_GetRomFont(i_1);
	}
	return Esd_GetFontXOffset(fontInfo_1);
}

uint16_t Ft_Esd_ScrollingText_Get_Font_Height__return(Ft_Esd_ScrollingText *context)
{
	void *owner = context->Owner;
	Esd_FontInfo * if_3 = context->Font_Resource;
	Esd_FontInfo *fontInfo_2;
	if (if_3)
	{
		fontInfo_2 = context->Font_Resource;
	}
	else
	{
		int i_2 = context->Font;
		fontInfo_2 = Esd_GetRomFont(i_2);
	}
	return Esd_GetFontHeight(fontInfo_2);
}

Ft_Esd_Theme * Ft_Esd_ScrollingText_ESD_Label_Theme__Property(void *c)
{
	Ft_Esd_ScrollingText *context = (Ft_Esd_ScrollingText *)c;
	void *owner = context->Owner;
	return context->Theme;
}

uint8_t Ft_Esd_ScrollingText_ESD_Label_Font__Property(void *c)
{
	Ft_Esd_ScrollingText *context = (Ft_Esd_ScrollingText *)c;
	void *owner = context->Owner;
	return context->Font;
}

Esd_FontInfo * Ft_Esd_ScrollingText_ESD_Label_FontResource__Property(void *c)
{
	Ft_Esd_ScrollingText *context = (Ft_Esd_ScrollingText *)c;
	void *owner = context->Owner;
	return context->Font_Resource;
}

const char * Ft_Esd_ScrollingText_ESD_Label_Text__Property(void *c)
{
	Ft_Esd_ScrollingText *context = (Ft_Esd_ScrollingText *)c;
	void *owner = context->Owner;
	return context->Text;
}


/* end of file */
