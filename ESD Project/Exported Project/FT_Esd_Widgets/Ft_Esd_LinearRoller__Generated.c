/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_LinearRoller
C Source
*/

/*
Comment :
Introduction:
This widget lets user choose a value by rolling a group of sticks linearly.
The main usage is for seeking radio channel.
Touch input is supported.
*/

#include "Ft_Esd_LinearRoller.h"

#include "Esd_Context.h"

ESD_CORE_EXPORT void Esd_Noop(void *context);
int Ft_Esd_LinearRoller_Length__Default(void *context) { return 20L; }
ft_bool_t Ft_Esd_LinearRoller_Horizontal__Default(void *context) { return 1; }
int Ft_Esd_LinearRoller_MinValue__Default(void *context) { return 0L; }
int Ft_Esd_LinearRoller_Value__Default(void *context) { return 0L; }
int Ft_Esd_LinearRoller_MaxValue__Default(void *context) { return 100L; }
ft_bool_t Ft_Esd_LinearRoller_IsTrimToRange__Default(void *context) { return 1; }
ft_bool_t Ft_Esd_LinearRoller_ShowTrimRange__Default(void *context) { return 1; }
ft_bool_t Ft_Esd_LinearRoller_IsDisplayTick__Default(void *context) { return 1; }
ft_bool_t Ft_Esd_LinearRoller_IsDisplayMinor__Default(void *context) { return 1; }
ft_bool_t Ft_Esd_LinearRoller_IsDisplayAxis__Default(void *context) { return 1; }
int Ft_Esd_LinearRoller_MajorWidth__Default(void *context) { return 3L; }
int Ft_Esd_LinearRoller_MinorWidth__Default(void *context) { return 2L; }
int Ft_Esd_LinearRoller_TickWidth__Default(void *context) { return 1L; }
float Ft_Esd_LinearRoller_MajorLength__Default(void *context) { return 0.72f; }
float Ft_Esd_LinearRoller_MinorLength__Default(void *context) { return 0.6f; }
float Ft_Esd_LinearRoller_TickLength__Default(void *context) { return 0.56f; }
int Ft_Esd_LinearRoller_LabelPadding__Default(void *context) { return 30L; }

static int Ft_Esd_LinearRoller_TouchScroll_X__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_Y__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_Width__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_Height__Property(void *context);
static ft_bool_t Ft_Esd_LinearRoller_TouchScroll_EnableXScroll__Property(void *context);
static ft_bool_t Ft_Esd_LinearRoller_TouchScroll_EnableYScroll__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_MinX__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_DefaultX__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_MaxX__Property(void *context) { return 0L; }
static int Ft_Esd_LinearRoller_TouchScroll_MinY__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_DefaultY__Property(void *context);
static int Ft_Esd_LinearRoller_TouchScroll_MaxY__Property(void *context) { return 0L; }

static Ft_Esd_WidgetSlots s_Ft_Esd_LinearRoller__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_LinearRoller_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_LinearRoller_Update,
	(void(*)(void *))Ft_Esd_LinearRoller_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Widget_End,
};


void Ft_Esd_LinearRoller__TouchScroll__Initializer(Ft_Esd_LinearRoller *context)
{
	Ft_Esd_TouchScrollLogic *object = (Ft_Esd_TouchScrollLogic *)&context->TouchScroll;
	Ft_Esd_TouchScrollLogic__Initializer(object);
	object->Owner = (void *)context;
	object->X = Ft_Esd_LinearRoller_TouchScroll_X__Property;
	object->Y = Ft_Esd_LinearRoller_TouchScroll_Y__Property;
	object->Width = Ft_Esd_LinearRoller_TouchScroll_Width__Property;
	object->Height = Ft_Esd_LinearRoller_TouchScroll_Height__Property;
	object->EnableXScroll = Ft_Esd_LinearRoller_TouchScroll_EnableXScroll__Property;
	object->EnableYScroll = Ft_Esd_LinearRoller_TouchScroll_EnableYScroll__Property;
	object->MinX = Ft_Esd_LinearRoller_TouchScroll_MinX__Property;
	object->DefaultX = Ft_Esd_LinearRoller_TouchScroll_DefaultX__Property;
	object->MaxX = Ft_Esd_LinearRoller_TouchScroll_MaxX__Property;
	object->MinY = Ft_Esd_LinearRoller_TouchScroll_MinY__Property;
	object->DefaultY = Ft_Esd_LinearRoller_TouchScroll_DefaultY__Property;
	object->MaxY = Ft_Esd_LinearRoller_TouchScroll_MaxY__Property;
}

void Ft_Esd_LinearRoller__Initializer(Ft_Esd_LinearRoller *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_LinearRoller_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_LinearRoller__Slots;
	context->Widget.LocalX = 0;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 317;
	context->Widget.LocalHeight = 484;
	context->Length = Ft_Esd_LinearRoller_Length__Default;
	context->Major = 10L;
	context->Minor = 5L;
	context->ColorMin = 0xff10e3dcUL;
	context->Ft_Esd_LinearRoller_UpdateCenterValue = 0L;
	context->ColorMax = 0xfffd0606UL;
	context->Horizontal = Ft_Esd_LinearRoller_Horizontal__Default;
	context->centerValue = 0L;
	context->centerColor = 0xfffcfcfcUL;
	context->MinValue = Ft_Esd_LinearRoller_MinValue__Default;
	context->Ft_Esd_LinearRoller_InitializeCenterValueWithMinMax = 0L;
	context->Value = Ft_Esd_LinearRoller_Value__Default;
	context->MaxValue = Ft_Esd_LinearRoller_MaxValue__Default;
	context->MinVariable = 0L;
	context->MaxVariable = 0L;
	context->Font = 26;
	context->valueVariable = 0L;
	context->ColorAxis = 0xffafd6caUL;
	context->IsTrimToRange = Ft_Esd_LinearRoller_IsTrimToRange__Default;
	context->ShowTrimRange = Ft_Esd_LinearRoller_ShowTrimRange__Default;
	context->IsDisplayTick = Ft_Esd_LinearRoller_IsDisplayTick__Default;
	context->IsDisplayMinor = Ft_Esd_LinearRoller_IsDisplayMinor__Default;
	context->IsDisplayAxis = Ft_Esd_LinearRoller_IsDisplayAxis__Default;
	context->MajorWidth = Ft_Esd_LinearRoller_MajorWidth__Default;
	context->MinorWidth = Ft_Esd_LinearRoller_MinorWidth__Default;
	context->TickWidth = Ft_Esd_LinearRoller_TickWidth__Default;
	context->MajorLength = Ft_Esd_LinearRoller_MajorLength__Default;
	context->MinorLength = Ft_Esd_LinearRoller_MinorLength__Default;
	context->TickLength = Ft_Esd_LinearRoller_TickLength__Default;
	context->LabelPadding = Ft_Esd_LinearRoller_LabelPadding__Default;
	Ft_Esd_LinearRoller__TouchScroll__Initializer(context);
}

int Ft_Esd_LinearRoller_TickWidth(Ft_Esd_LinearRoller *context);
void Ft_Esd_LinearRoller_Draw(Ft_Esd_LinearRoller *context);
int Ft_Esd_LinearRoller_UpdateCenterValue(Ft_Esd_LinearRoller *context, ft_bool_t, int, int, ft_double_t);
int Ft_Esd_LinearRoller_InitializeCenterValueWithMinMax(Ft_Esd_LinearRoller *context, int, int, int, int);

void Ft_Esd_LinearRoller_Start(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_Start((Ft_Esd_Widget *)context);
	Ft_Esd_TouchScrollLogic_Start(&context->TouchScroll);
}

void Ft_Esd_LinearRoller_Update__Builtin(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchScrollLogic_Update(&context->TouchScroll);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context);
}

void Ft_Esd_LinearRoller_Update(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	ft_bool_t isTouched = context->TouchScroll.IsTouched;
	int ScrollX = Ft_Esd_TouchScrollLogic_ScrolledX(&context->TouchScroll);
	int ScrollY = Ft_Esd_TouchScrollLogic_ScrolledY(&context->TouchScroll);
	int tickWidth = Ft_Esd_LinearRoller_TickWidth(context);
	context->Ft_Esd_LinearRoller_UpdateCenterValue = Ft_Esd_LinearRoller_UpdateCenterValue(context, isTouched, ScrollX, ScrollY, tickWidth);
	int MinInput = context->MinValue(owner);
	int MinVariable_1 = context->MinVariable;
	int MaxInput = context->MaxValue(owner);
	int MaxVariable_1 = context->MaxVariable;
	context->Ft_Esd_LinearRoller_InitializeCenterValueWithMinMax = Ft_Esd_LinearRoller_InitializeCenterValueWithMinMax(context, MinInput, MinVariable_1, MaxInput, MaxVariable_1);
	Ft_Esd_LinearRoller_Update__Builtin(context);
}

void Ft_Esd_LinearRoller_Render(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	Ft_Esd_LinearRoller_Draw(context);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

int Ft_Esd_LinearRoller_CenterValue(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	return context->centerValue;
}

ft_argb32_t Ft_Esd_LinearRoller_CenterColor(Ft_Esd_LinearRoller *context)
{
	void *owner = context->Owner;
	return context->centerColor;
}

int Ft_Esd_LinearRoller_TouchScroll_X__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	return context->Widget.GlobalX;
}

int Ft_Esd_LinearRoller_TouchScroll_Y__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	return context->Widget.GlobalY;
}

int Ft_Esd_LinearRoller_TouchScroll_Width__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	return context->Widget.GlobalWidth;
}

int Ft_Esd_LinearRoller_TouchScroll_Height__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	return context->Widget.GlobalHeight;
}

ft_bool_t Ft_Esd_LinearRoller_TouchScroll_EnableXScroll__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	return context->Horizontal(owner);
}

ft_bool_t Ft_Esd_LinearRoller_TouchScroll_EnableYScroll__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	ft_bool_t value = context->Horizontal(owner);
	return !value;
}

int Ft_Esd_LinearRoller_TouchScroll_MinX__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	int left_2 = context->MinValue(owner);
	int right = context->MaxValue(owner);
	ft_float_t left_1 = left_2 - right;
	ft_bool_t if_1 = context->Horizontal(owner);
	int left_3;
	if (if_1)
	{
		left_3 = context->Widget.LocalWidth;
	}
	else
	{
		left_3 = context->Widget.LocalHeight;
	}
	int right_2 = context->Length(owner);
	ft_double_t right_1 = left_3 / right_2;
	ft_double_t left = left_1 * right_1;
	ft_double_t right_3 = 0.5;
	return left - right_3;
}

int Ft_Esd_LinearRoller_TouchScroll_DefaultX__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	int left_6 = context->MinValue(owner);
	int value_1 = context->Value(owner);
	int min = context->MinValue(owner);
	int max = context->MaxValue(owner);
	ft_int32_t right_4 = Ft_Esd_Int32_ClampedValue(value_1, min, max);
	int left_5 = left_6 - right_4;
	ft_bool_t if_2 = context->Horizontal(owner);
	int left_7;
	if (if_2)
	{
		left_7 = context->Widget.LocalWidth;
	}
	else
	{
		left_7 = context->Widget.LocalHeight;
	}
	int right_6 = context->Length(owner);
	ft_double_t right_5 = left_7 / right_6;
	ft_double_t left_4 = left_5 * right_5;
	ft_double_t right_7 = 0.5;
	return left_4 - right_7;
}

int Ft_Esd_LinearRoller_TouchScroll_MinY__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	int left_10 = context->MinValue(owner);
	int right_8 = context->MaxValue(owner);
	ft_float_t left_9 = left_10 - right_8;
	ft_bool_t if_3 = context->Horizontal(owner);
	int left_11;
	if (if_3)
	{
		left_11 = context->Widget.LocalWidth;
	}
	else
	{
		left_11 = context->Widget.LocalHeight;
	}
	int right_10 = context->Length(owner);
	ft_double_t right_9 = left_11 / right_10;
	ft_double_t left_8 = left_9 * right_9;
	ft_double_t right_11 = 0.5;
	return left_8 - right_11;
}

int Ft_Esd_LinearRoller_TouchScroll_DefaultY__Property(void *c)
{
	Ft_Esd_LinearRoller *context = (Ft_Esd_LinearRoller *)c;
	void *owner = context->Owner;
	int left_14 = context->MinValue(owner);
	int value_2 = context->Value(owner);
	int min_1 = context->MinValue(owner);
	int max_1 = context->MaxValue(owner);
	ft_int32_t right_12 = Ft_Esd_Int32_ClampedValue(value_2, min_1, max_1);
	int left_13 = left_14 - right_12;
	ft_bool_t if_4 = context->Horizontal(owner);
	int left_15;
	if (if_4)
	{
		left_15 = context->Widget.LocalWidth;
	}
	else
	{
		left_15 = context->Widget.LocalHeight;
	}
	int right_14 = context->Length(owner);
	ft_double_t right_13 = left_15 / right_14;
	ft_double_t left_12 = left_13 * right_13;
	ft_double_t right_15 = 0.5;
	return left_12 - right_15;
}


/* end of file */
