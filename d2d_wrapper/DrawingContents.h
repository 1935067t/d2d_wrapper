#pragma once
#include<d2d1.h>
#include<string>

struct FILLED_RECT
{
	D2D1_RECT_F rect;
};

struct FRAME_RECT
{
	D2D1_RECT_F rect;
	float strokeWidth = 1.0f;
};

struct FILLED_ROUNDEDRECT
{
	D2D1_ROUNDED_RECT roundedRect;
};

struct FRAME_ROUNDEDRECT
{
	D2D1_ROUNDED_RECT roundedRect;
	float strokeWidth = 1.0f;
};

struct FILLED_ELLIPSE
{
	D2D1_ELLIPSE ellipse;
};

struct FRAME_ELLIPSE
{
	D2D1_ELLIPSE ellipse;
	float strokeWidth = 1.0f;
};

struct LINE
{
	D2D1_POINT_2F start;
	D2D1_POINT_2F end;
	float strokeWidth = 1.0f;
};

struct TEXTFORMAT
{
	std::wstring fontname;
	FLOAT fontsize;
};