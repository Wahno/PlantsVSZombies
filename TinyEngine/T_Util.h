//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include "T_Config.h"

class T_Util
{
public:

	static HWND GetHWnd()
	{
		return FindWindow(WIN_CLASS, NULL);
	}

	static HINSTANCE GetHInst()
	{
		return GetModuleHandle(NULL);
	}

	static wchar_t * int_to_wstring(int i);

	// 产生参数range指定范围的等额随机数
	// 参数iArray为输出随机数的输出参数
	// 参数iArray必须首先定义为元素个数等于range的数组
	static void GetRandomNum(int range, int* iArray);


	// 计算startPT到destPT之间
	// 斜角移动时X轴与Y轴的分量值
	// xRatio和yRatio为输出参数
	static void GetBevelSpeed(
		IN POINT startPT, IN POINT destPT, 
		OUT int& xRatio, OUT int& yRatio
	);

	// 根据输入的三个参数所指定的起点、终点坐标和移动速度
	// 如果要保持两点直线移动且长边速度为指定移动速度
	// 本函数计算出短边对应的分量速度
	// xRatio与yRatio为输出参数, 即最终计算结果
	// 本函数会自动判断方向：
	//	xRatio、yRatio为正值，表示朝右、下移动
	//	xRatio、yRatio为负值，表示朝左、上移动
	static void GetBevelSpeed(
		IN POINT startPT, IN POINT destPT, IN int Speed, 
		OUT int& xRatio, OUT int& yRatio
	);
	static wchar_t * multiByteToWideChar(const string & pKey);

};