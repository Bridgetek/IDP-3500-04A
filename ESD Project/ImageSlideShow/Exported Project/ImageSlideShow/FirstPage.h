/*
This file is automatically generated
DO NOT MODIFY BY HAND
FirstPage
Header
*/

#ifndef FirstPage__H
#define FirstPage__H

#include "Esd_Base.h"
#include "Esd_BitmapInfo.h"
#include "Esd_Core.h"
#include "Esd_FontInfo.h"
#include "Ft_Esd.h"
#include "Ft_Esd_Image_SlideShow.h"
#include "Ft_Esd_Label.h"
#include "Ft_Esd_Layout_Fixed.h"
#include "Ft_Esd_PushButton.h"
#include "Ft_Esd_ScrollingText.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_Toggle.h"
#include "Ft_Esd_Widget.h"
#include "barbecue.h"
#include "chess.h"
#include "diveevo.h"
#include "fire.h"
#include "keyboard.h"
#include "locomotive.h"
#include "person.h"
#include "rose.h"
#include "seagull.h"

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

#define FirstPage_CLASSID 0x72AE16B4
ESD_SYMBOL(FirstPage_CLASSID, Type = esd_classid_t)

ESD_WIDGET(FirstPage, Include = "FirstPage.h", Callback, X = 0, Y = 0, Width = 400, Height = 300, Page)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	Ft_Esd_Layout_Fixed Fixed_Position;
	Ft_Esd_PushButton ESD_Push_Button;
	Ft_Esd_Toggle ESD_Toggle;
	Ft_Esd_ScrollingText ESD_Scrolling_Text;
	Ft_Esd_Image_SlideShow ESD_Image_SlideShow;
	Ft_Esd_Label ESD_Label;
} FirstPage;

void FirstPage__Initializer(FirstPage *context);

ESD_SLOT(End)
void FirstPage_End(FirstPage *context);

#endif /* FirstPage__H */

/* end of file */
