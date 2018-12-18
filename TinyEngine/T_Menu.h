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
#include "T_Graph.h"
#include "T_Audio.h"



//
// 本菜单类支持：
// 垂直排列：纯文字按钮或图片按钮
// 水平排列：纯文字按钮或图片按钮
//
class T_Menu
{
protected:
	MENU_INFO menu_info;								// 菜单信息
	
	int m_index;										// 当前焦点菜单索引号
	bool isItemFocused;									// 当前菜单是否获焦点
	
	int lastIndex;
	int key_index;
	int MaxMenuItemLen;									// 最长菜单文字长度

	int bkImageAlpha;									// 背景图片透明度
	int bkColor;										// 背景颜色

	T_Graph gm_menuBkg;									// 菜单背景
	T_Graph BtnDIB;										// 菜单图片					
	vector<MENUITEM> gm_menuItems;						// 菜单项目

	int GetMenuIndex(int x, int y);						// 根据当前鼠标坐标计算菜单项索引号
	StringAlignment GetAlignment();						
	FontStyle GetFontStyle();

	AudioDXBuffer* m_MoveSound;							// 菜单鼠标移过时的声音
	AudioDXBuffer* m_ClickSound;						// 菜单鼠标点击时的声音

public:
	T_Menu();
	virtual ~T_Menu(void);

	// 设置菜单背景图片。透明度及背景颜色
	void SetMenuBkg(wstring img_path, int alphaLevel=255, COLORREF backColor=RGB(0,0,0));	
	void SetBtnBmp(wstring img_path,						// 设置菜单按钮图片
		           int btnWidth,							// 图片按钮宽
		           int btnHeight);							// 图片按钮高

	void SetMenuInfo(MENU_INFO menuInfo);			
	void AddMenuItem(MENUITEM menuItem);					// 添加菜单文字项目

	//菜单绘制: btnTrans按钮透明度, 255不透明; startState是否绘制开始菜单
	void DrawMenu(HDC hdc, BYTE btnTrans=255, bool startState=true);

	int MenuMouseClick(int x, int y);					// 菜单鼠标点击事件处理
	void MenuMouseMove(int x, int y);					// 菜单鼠标移动事件处理
	int MenuKeyDown(WPARAM key);						// 菜单按键事件处理

	int GetMenuIndex(){ return m_index; }				// 返回当前的m_index
	void SetMenuIndex(int i){ m_index = i; }			// 设置当前的m_index

	void DestroyAll();

	void SetMoveSound(AudioDXBuffer* ms_buffer);
	void SetClickSound(AudioDXBuffer* mc_buffer);
};
