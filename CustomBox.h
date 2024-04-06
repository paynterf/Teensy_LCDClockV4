#pragma once

#ifndef _ILI9341_t3NH_	
#include <ILI9341_t3n.h>
#endif // !_ILI9341_t3NH_

class CustomBox
{
public:
	int x;
	int y;
private:
	int w;
	int h;
	int color;
public:
	CustomBox(int in_x, int in_y, int in_w, int in_h, int in_color);
	CustomBox(int in_w, int in_h, int in_color);
	void Draw(ILI9341_t3n* disp);
	void Draw(ILI9341_t3n* disp, char c, int txtcolor, int size);
	void Draw(ILI9341_t3n* disp, char c, int txtcolor, ILI9341_t3_font_t font, bool centered = false);
	void Draw(ILI9341_t3n* disp, String txt, int txtcolor, ILI9341_t3_font_t font, bool centered = false);
	void Draw(ILI9341_t3n* disp, String txt, int size);
	void Draw(ILI9341_t3n* disp, char* buff, int size);
	void Draw(ILI9341_t3n* disp, int color);
	bool TouchHit(int in_x, int in_y);
};


CustomBox::CustomBox(int in_w, int in_h, int in_color)
{
	x = 0;
	y = 0;
	w = in_w;
	h = in_h;
	color = in_color;
}

CustomBox::CustomBox(int in_x, int in_y, int in_w, int in_h, int in_color)
{
	x = in_x;
	y = in_y;
	w = in_w;
	h = in_h;
	color = in_color;
}

inline void CustomBox::Draw(ILI9341_t3n* disp)
{
	disp->fillRect(x, y, w, h, color);
}

inline void CustomBox::Draw(ILI9341_t3n* disp, char c, int txtcolor, ILI9341_t3_font_t font, bool centered)
{
	int txt_x = x;
	int txt_y = y;
	disp->setFont(font);
	if (centered)
	{
		txt_x = x + round((float)(w / 2.));
		txt_y = y + round((float)(h / 2.));
	}

	Serial.printf("txt cursor set to (%d,%d)\n", txt_x, txt_y);
	disp->fillRect(x, y, w, h, color);
	disp->setTextColor(txtcolor);
	disp->setCursor(txt_x, txt_y, centered);
	disp->print(c);
}

inline void CustomBox::Draw(ILI9341_t3n* disp, String txt, int txtcolor, ILI9341_t3_font_t font, bool centered)
{
	int txt_x = x;
	int txt_y = y;
	disp->setFont(font);
	if (centered)
	{
		txt_x = x + round((float)(w / 2.));
		txt_y = y + round((float)(h / 2.));
	}

	//Serial.printf("txt cursor set to (%d,%d)\n", txt_x, txt_y);
	disp->fillRect(x, y, w, h, color);
	disp->setTextColor(txtcolor);
	disp->setCursor(txt_x, txt_y, centered);
	disp->print(txt);
}


//class CustomBoxWithText :CustomBox
//{
//private:
//	char boxtext[6];
//public:
//	CustomBoxWithText(int in_x, int in_y, int in_w, int in_h, int in_color, char* txt);
//};
//
//
//CustomBox::CustomBox(int in_x, int in_y, int in_w, int in_h, int in_color)
//{
//	x = in_x;
//	y = in_y;
//	w = in_w;
//	h = in_h;
//	color = in_color;
//}

inline void CustomBox::Draw(ILI9341_t3n* disp, char c, int txtcolor, int size = 0)
{
	disp->fillRect(x, y, w, h, color);
	if (size==0)
	{
		size = round((float)h / 10.);
	}
	int char_x = x + round((float)w / 4.);
	//int char_x = x;
	disp->setCursor(char_x, y+size);
	disp->setTextSize(size);
	disp->setTextColor(txtcolor);
	disp->print(c);
}

inline void CustomBox::Draw(ILI9341_t3n* disp, String txt, int size)
{
	disp->fillRect(x, y, w, h, color);
	disp->setCursor(x, y);
	disp->setTextSize(size);
	disp->print(txt);
}

inline void CustomBox::Draw(ILI9341_t3n* disp, char* buff, int size)
{
	Serial.printf("In Draw() with buff = %s\n", buff);
	disp->fillRect(x, y, w, h, color);
	//disp->setCursor(x, y);
	disp->setTextSize(size);
	//disp->setTextDatum(MC_DATUM);
	//disp->drawString1(buff, strlen(buff), x, y);
	disp->drawString(buff, strlen(buff), x, y); //03/09/21 in latest library version drawString1 was made into an overload of drawString
}

inline void CustomBox::Draw(ILI9341_t3n* disp, int newcolor)
{
	disp->fillRect(x, y, w, h, newcolor);
}

inline bool CustomBox::TouchHit(int in_x, int in_y)
{
	//Purpose:  Determine if input coordinates are within a specified box
	//Inputs:
	//  in_x, in_y = integers denoting mapped touch coordinates
	//  box location & dimensions
	//Outputs:
	//  true if (in_x, in_y) falls within box region.  Othewise, false

	//Serial.printf("TouchHit(%d,%d), box (x,y,w,h) = (%d,%d,%d,%d)\n",
	//	in_x, in_y, x, y, w, h);

	return (in_x > x && in_y > y && in_x < x + w && in_y < y + h);
}
