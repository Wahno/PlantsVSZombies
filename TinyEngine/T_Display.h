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
#include <Windows.h> 

class T_Display 
{
public:
	T_Display();
	~T_Display();

	void SaveMode();						// 保存当前分辨率
	void ResetMode();						// 恢复已保存的分辨率
	bool ChangeMode(int width, int height);	// 改变分辨率

private:
	DEVMODE	devmode_saved;					// 保存的当前分辨率
	bool mode_changed;						// 分辨率是否改变
} ;