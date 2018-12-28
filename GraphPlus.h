#pragma once
#include "TinyEngine\T_Graph.h"
class GraphPlus :
	public T_Graph
{
public:
	GraphPlus();
	~GraphPlus();
	static void PaintText(HDC hdc, RectF fontRect, wstring text,
		REAL fontSize, wstring fontName,
		Color fontColor = Color::White,
		FontStyle style = FontStyleBold,
		StringAlignment align = StringAlignmentCenter,int n = 10);
};

