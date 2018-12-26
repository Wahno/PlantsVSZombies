#pragma once
#include "TinyEngine\T_Menu.h"
#include "TinyEngine\T_Config.h"
class BookMenu :
	public T_Menu
{
public:
	BookMenu();
	~BookMenu();
public:
	void InitZom();
	void InitSun();
	void InitReturn();
	void InitShut();
	void InitP_return();
	int GetMenuIndex(int x, int y); /*获得菜单项索引*/
	//菜单绘制: btnTrans按钮透明度, 255不透明; startState是否绘制开始菜单
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true);
};

