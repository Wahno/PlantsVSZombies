//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Display.h"

//构造函数 
T_Display::T_Display():mode_changed(false)
{
	SaveMode();
}

//析构函数
T_Display::~T_Display()
{
	ResetMode();
}

// 存储现在的显示模式
void T_Display::SaveMode()
{
	HDC	dc = GetDC(0);
	devmode_saved.dmSize = sizeof(devmode_saved);
	devmode_saved.dmDriverExtra = 0;
	devmode_saved.dmPelsWidth = GetDeviceCaps(dc, HORZRES);
	devmode_saved.dmPelsHeight = GetDeviceCaps(dc, VERTRES);
	devmode_saved.dmBitsPerPel = GetDeviceCaps(dc, BITSPIXEL);
	devmode_saved.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
	devmode_saved.dmFields |= DM_DISPLAYFREQUENCY;
	devmode_saved.dmDisplayFrequency = GetDeviceCaps(dc, VREFRESH);
	ReleaseDC(0, dc);
}

// 还原成之前存储的显示模式
void T_Display::ResetMode()
{
	if (mode_changed) 
	{
		ChangeDisplaySettings(&devmode_saved, 0);
		mode_changed = false;
	}
}

// 更改显示模式
bool T_Display::ChangeMode(int width, int height)
{
	DEVMODE	devmode;

	devmode = devmode_saved;
	devmode.dmPelsWidth = width;
	devmode.dmPelsHeight = height;
	devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) 
		== DISP_CHANGE_SUCCESSFUL) 
	{
		mode_changed = true;
		return true;
	}
	return false;
}