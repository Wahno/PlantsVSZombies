#include "GraphPlus.h"



GraphPlus::GraphPlus()
{
}


GraphPlus::~GraphPlus()
{
}

void GraphPlus::PaintText(HDC hdc, RectF fontRect, wstring text, REAL fontSize, wstring fontName, Color fontColor, FontStyle style, StringAlignment align,int n)
{
	//使用GDI方法进行绘制
	Gdiplus::Graphics graph(hdc);
	FontFamily fontFamily(fontName.c_str());
	Font font(&fontFamily, fontSize, style, UnitPoint);

	StringFormat format;
	format.SetLineAlignment(StringAlignmentCenter);
	format.SetAlignment(align);
	SolidBrush  solidBrush1(fontColor);

	graph.SetTextRenderingHint(TextRenderingHintAntiAlias);
	if (n == 0) {
		n = 10;
	}
	wstring temp = L"";
	for (int i = 0; i < text.length() / n + 1; i++)
		// temp = text.substr((i-1)*n,i * n);
		if ((text.length()- i* n) / n > 0)
		{
			temp = text.substr(i*n, i * n - 1);	
			fontRect.Width = n * 20;
			graph.DrawString(temp.c_str(), n, &font, fontRect, &format, &solidBrush1);
			fontRect.Y = fontRect.Y + 20;
		}	
		else
		{
			temp = text.substr(i*n, text.length());
			/*for (int j = 0; j < n - temp.length(); j++)
			{
				temp = temp + L" ";
			}*/
			T_Graph::PaintText(hdc,fontRect,temp,fontSize,fontName,fontColor,style,align);
		//	graph.DrawString(temp.c_str(),  n, &font, fontRect, &format, &solidBrush1);
			fontRect.Y = fontRect.Y + 20;
		}
	graph.ReleaseHDC(hdc);
}
