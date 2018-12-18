//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Graph.h"
#include "T_Config.h"

// T_Graph类默认构造函数
//
T_Graph::T_Graph()
{
	hBmp = NULL;
}

// T_Graph类构造函数，使用指定的文件来创建一个HBITMAP对象
T_Graph::T_Graph(wstring fileName)
{
	LoadImageFile(fileName);
}

// T_Graph类析构函数
T_Graph::~T_Graph()
{
	Destroy();
}

// T_Graph类释放资源的方法
void T_Graph::Destroy()
{
	GdiFlush();
	if(hBmp)
	{
		DeleteObject(hBmp);
		hBmp = NULL;
	}
}

bool T_Graph::LoadImageFile(wstring path)
{
	Bitmap* pBmp = Bitmap::FromFile(path.c_str());
	if(!pBmp) return false;

	ImageWidth = pBmp->GetWidth();
	ImageHeight = pBmp->GetHeight();

	if(ImageHeight==0 || ImageWidth==0) return false;

	Status status = pBmp->GetHBITMAP(NULL, &hBmp);
	if(pBmp) 
	{
		delete pBmp;
		pBmp = NULL;
	}
	if(status == S_OK) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

HBITMAP T_Graph::CreateBlankBitmap(int width, int height, COLORREF color)
{
	BYTE* pBits = NULL;
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = width * height * 4;
	HBITMAP blankBmp = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pBits, NULL, NULL);
	PaintBlank(blankBmp, width, height, color);
	return blankBmp;
}

////////////////////////////////////////////////////////////////////////////////////
// 从第一参数指定的HBITMAP拷贝数据创建一个Bitmap类的指针对象
////////////////////////////////////////////////////////////////////////////////////
Bitmap* T_Graph::HBITMAP_To_Bitmap(HBITMAP hbmp, HDC hdc)
{
	BITMAP bmp;
	int width, height;

	// 根据位图句柄获取BITMAP结构体对象的数据
	memset((void*)&bmp, 0, sizeof(BITMAP));
	GetObject(hbmp, sizeof(BITMAP), (void*)&bmp);
	width = bmp.bmWidth;
	height = bmp.bmHeight;
	byte* bmpBytes = (byte*)bmp.bmBits;

	if(width<=0 && height<=0) return NULL;

	// 根据位图宽高新建一个PixelFormat32bppPARGB格式的Bitmap对象
	Bitmap* BmpCpy = new Bitmap(width, height, PixelFormat32bppPARGB);

	// 采用LockBits函数为位图像素数据拷贝准备内存缓冲区
	BitmapData bmpData;
	Rect rect(0, 0, width, height);
	BmpCpy->LockBits(&rect, ImageLockModeWrite, PixelFormat32bppPARGB, &bmpData);

	// 计算出位图每行像素数，并将指针指向首行
	int lineSize = width * 4;
	byte* cpyBytes = (byte*)(bmpData.Scan0);
	// 按照位图的高逐行拷贝像素数据至缓冲区
	for (int y = 0; y < height; y++)
	{
		memcpy((y * lineSize)+cpyBytes, 
			((height - y -1) * lineSize)+bmpBytes, 
			lineSize);
	}
	// 解锁内存缓冲区
	BmpCpy->UnlockBits(&bmpData);

	return BmpCpy;
}


void T_Graph::PaintImage(HDC hdc, int x, int y)
{
	//创建帧图的内存设备
	HDC memDC = CreateCompatibleDC(hdc);
	//将空白的帧图选进内存设备
	HBITMAP OldFrameBmp = (HBITMAP)SelectObject(memDC, hBmp);
	//以下使用GDI的BitBlt绘制,由于直接内存复制,速度较快
	BitBlt(hdc, x, y, ImageWidth, ImageHeight, memDC, 0, 0, SRCCOPY);
	//还原：使用原来对象替换内存设备中的位图对象
	SelectObject(memDC, OldFrameBmp);
	DeleteDC(memDC);//删除内存设备
	DeleteObject(OldFrameBmp);//删除位图对象
}

void T_Graph::PaintImage(HDC hdc, int x, int y, int width, int height)
{
	//创建全图的内存设备
	HDC memDC = CreateCompatibleDC(hdc);
	//将源图选进内存设备中
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBmp);
	SetStretchBltMode(hdc, COLORONCOLOR);
	StretchBlt(hdc, x, y, width, height, 
		       memDC, 0, 0, ImageWidth, ImageHeight, 
		       SRCCOPY);

	//使用原来对象替换全图内存设备中的位图对象
	SelectObject(memDC, hOldBitmap);
	DeleteDC(memDC);//删除全图内存设备
	DeleteObject(hOldBitmap);//删除位图对象
}

void T_Graph::PaintImage(HDC hdc, int x, int y, int width, int height, BYTE alpha)
{
	//创建全图的内存设备
	HDC memDC = CreateCompatibleDC(hdc);
	//将源图选进内存设备中
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBmp);

	BLENDFUNCTION dc_bf;
	dc_bf.BlendOp = AC_SRC_OVER;
	dc_bf.BlendFlags = 0;
	dc_bf.SourceConstantAlpha = alpha;
	dc_bf.AlphaFormat = AC_SRC_ALPHA;

	SetStretchBltMode(hdc, COLORONCOLOR);

	AlphaBlend(hdc, x, y, width, height, 
		       memDC, 0, 0, ImageWidth, ImageHeight, 
		       dc_bf);
	//StretchBlt(hdc, x, y, width, height, 
	//			 memDC, 0, 0, ImageWidth, ImageHeight, 
	//			 SRCCOPY);

	//使用原来对象替换全图内存设备中的位图对象
	SelectObject(memDC, hOldBitmap);
	DeleteDC(memDC);//删除全图内存设备
	DeleteObject(hOldBitmap);//删除位图对象
}

//rotType:旋转类型
void T_Graph::PaintRegion(HBITMAP in_hbitmap, HDC destDC, int destX, int destY, 
						  int srcX, int srcY, int regionWidth, int regionHeight,
						  float ratio, int rotType, BYTE alpha)  
{
	int width = (int)(regionWidth*ratio);
	int height = (int)(regionHeight*ratio);

	BYTE* pBits = NULL;
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; 
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = width * height * 4;

	HDC frameDC = ::CreateCompatibleDC(NULL);
	HBITMAP hbitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pBits, NULL, NULL);
	HBITMAP OldFrameBmp = (HBITMAP)SelectObject(frameDC, hbitmap);

	HDC memDC = CreateCompatibleDC(destDC);
	HBITMAP OldMemBmp = (HBITMAP)SelectObject(memDC, in_hbitmap);

	BLENDFUNCTION frame_bf;
	frame_bf.BlendOp = AC_SRC_OVER;
	frame_bf.BlendFlags = 0;
	frame_bf.SourceConstantAlpha = 255;
	frame_bf.AlphaFormat = AC_SRC_ALPHA;
	AlphaBlend(frameDC, 0, 0, (int)(regionWidth*ratio), (int)(regionHeight*ratio), 
		       memDC, srcX, srcY, regionWidth, regionHeight, frame_bf);

	Bitmap* nowFrameBmp =HBITMAP_To_Bitmap(hbitmap, destDC);

	//还原：使用原来对象替换内存设备中的位图对象
	SelectObject(frameDC, OldFrameBmp);
	DeleteDC(frameDC);//删除内存设备
	DeleteObject(OldFrameBmp);//删除位图对象
	OldFrameBmp = NULL;
	DeleteObject(hbitmap);//删除位图对象
	hbitmap = NULL;

	//还原：使用原来对象替换内存设备中的位图对象
	SelectObject(memDC, OldMemBmp);
	DeleteDC(memDC);//删除内存设备
	DeleteObject(OldMemBmp);//删除位图对象
	OldMemBmp = NULL;

	//旋转帧图
	switch(rotType)
	{
	case TRANS_NONE:
		break;
	case TRANS_NOFLIP_ROT90:
		nowFrameBmp->RotateFlip(Rotate90FlipNone);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	case TRANS_NOFLIP_ROT180:
		nowFrameBmp->RotateFlip(Rotate180FlipNone);
		width = (int)(regionWidth*ratio);
		height = (int)(regionHeight*ratio);
		break;
	case TRANS_NOFLIP_ROT270:
		nowFrameBmp->RotateFlip(Rotate270FlipNone);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	case TRANS_VFLIP_NOROT:
		nowFrameBmp->RotateFlip(RotateNoneFlipY);
		width = (int)(regionWidth*ratio);
		height = (int)(regionHeight*ratio);
		break;
	case TRANS_VFLIP_ROT90:
		nowFrameBmp->RotateFlip(Rotate90FlipY);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	case TRANS_VFLIP_ROT180:
		nowFrameBmp->RotateFlip(Rotate180FlipY);
		width = (int)(regionWidth*ratio);
		height = (int)(regionHeight*ratio);
		break;
	case TRANS_VFLIP_ROT270:
		nowFrameBmp->RotateFlip(Rotate270FlipY);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	case TRANS_HFLIP_NOROT:
		nowFrameBmp->RotateFlip(RotateNoneFlipX);
		width = (int)(regionWidth*ratio);
		height = (int)(regionHeight*ratio);
		break;
	case TRANS_HFLIP_ROT90:
		nowFrameBmp->RotateFlip(Rotate90FlipX);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	case TRANS_HFLIP_ROT180:
		nowFrameBmp->RotateFlip(Rotate180FlipX);
		width = (int)(regionWidth*ratio);
		height = (int)(regionHeight*ratio);
		break;
	case TRANS_HFLIP_ROT270:
		nowFrameBmp->RotateFlip(Rotate270FlipX);
		width = (int)(regionHeight*ratio);
		height = (int)(regionWidth*ratio);
		break;
	}
	
	HBITMAP hbmp = NULL;
	nowFrameBmp->GetHBITMAP(NULL, &hbmp );
	HDC bufDC = CreateCompatibleDC(destDC);
	HBITMAP OldbufBmp = (HBITMAP)SelectObject( bufDC, hbmp);

	BLENDFUNCTION buf_bf;
	buf_bf.BlendOp = AC_SRC_OVER;
	buf_bf.BlendFlags = 0;
	buf_bf.SourceConstantAlpha = alpha;
	buf_bf.AlphaFormat = AC_SRC_ALPHA;
	AlphaBlend(destDC, destX, destY, width, height, 
		       bufDC, 0, 0, width, height, buf_bf);

	//还原：使用原来对象替换内存设备中的位图对象
	SelectObject(bufDC, OldbufBmp);
	DeleteDC(bufDC);//删除内存设备
	DeleteObject(OldbufBmp);//删除位图对象
	OldbufBmp = NULL;
	DeleteObject(hbmp);//删除位图对象
	hbmp = NULL;
	DeleteObject(nowFrameBmp);//删除位图对象
	delete nowFrameBmp;//删除位图对象
	nowFrameBmp = NULL;
}

void T_Graph::PaintFrame( HBITMAP in_hbitmap, HDC destDC, int destX, int destY, 
						  int FrameCount, int RowFrames, int wFrame, int hFrame,
						  float ratio, int rotType, BYTE alpha)
{
	int col=FrameCount%RowFrames;
	int row = (FrameCount-col)/RowFrames;
	PaintRegion(in_hbitmap, destDC, destX, destY, 
		        col*wFrame, row*hFrame, wFrame, hFrame, 
				ratio, rotType, alpha);
}

void T_Graph::PaintBlank(HDC hdc, int x, int y, int width, int height, Color crColor)
{
	Gdiplus::Graphics g(hdc);
	Rect rectangle(x, y, width, height);
	SolidBrush solidBrush( crColor );
	g.FillRectangle( &solidBrush, rectangle );
	g.ReleaseHDC(hdc);
}

void T_Graph::PaintBlank(HDC hdc, int x, int y, int width, int height, COLORREF crColor, int alpLevel)
{
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, width, height);
	HDC memdc = ::CreateCompatibleDC(NULL);
	HBITMAP OldBmp = (HBITMAP)SelectObject(memdc, hbitmap);

	HBRUSH hBrush = CreateSolidBrush(crColor);
	RECT rcBitmap = { x, y, width, height };
	FillRect(memdc, &rcBitmap, hBrush);

	BLENDFUNCTION frame_bf;
	frame_bf.BlendOp = AC_SRC_OVER;
	frame_bf.BlendFlags = 0;
	frame_bf.SourceConstantAlpha = alpLevel;
	frame_bf.AlphaFormat = 0;
	AlphaBlend(hdc, x, y, width, height, memdc, 0, 0, width, height, frame_bf);
	
	// 恢复内存设备中的位图对象
	SelectObject(memdc, OldBmp);
	// 删除内存设备
	DeleteDC(memdc);
	// 删除位图对象
	DeleteObject(OldBmp);
	// 释放句柄
	OldBmp = NULL;
	// 删除位图对象
	DeleteObject(hbitmap);
	// 释放句柄
	hbitmap = NULL;
	// 删除笔刷
	DeleteObject(hBrush);
}

void T_Graph::PaintBlank(HBITMAP hbmp, int width, int height, COLORREF crColor)
{
	HDC memdc = ::CreateCompatibleDC(NULL);
	HBITMAP OldBmp = (HBITMAP)SelectObject(memdc, hbmp);

	HBRUSH hBrush = CreateSolidBrush(crColor);
	RECT rcBitmap = {0, 0, width, height};
	FillRect(memdc, &rcBitmap, hBrush);
	
	// 恢复内存设备中的位图对象
	SelectObject(memdc, OldBmp);
	// 删除内存设备
	DeleteDC(memdc);
	// 删除位图对象
	DeleteObject(OldBmp);
	// 释放句柄
	OldBmp = NULL;
	// 删除笔刷
	DeleteObject(hBrush);
}

void T_Graph::PaintText(HDC hdc, RectF fontRect, wstring text, REAL fontSize, 
	wstring fontName, Color fontColor, FontStyle style,
						StringAlignment align)
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
	graph.DrawString(text.c_str(), (INT)(text.length()), &font, fontRect, &format, &solidBrush1);
	graph.ReleaseHDC(hdc);
}