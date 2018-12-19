#pragma once
#include"TinyEngine\T_Menu.h"
class ChoiceMenu : public T_Menu
{
public:
	ChoiceMenu();
	~ChoiceMenu();
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true,float ratio = 1);

	int GetMenuIndex(int x, int y, float ratio);

	int MenuMouseClick(int x, int y, float ratio);

	void MenuMouseMove(int x, int y, float ratio);
	
};

