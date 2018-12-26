#pragma once
#include "TinyEngine\\T_Engine.h"
#include "TinyEngine\\T_Scene.h"
#include "TinyEngine\\T_Sprite.h"
#include "TinyEngine\\T_AI.h"
#include "MainMenu.h"
#include "HelpMenu.h"
#include "ChoiceMenu.h"
#include "GameLevel.h"

class PVZ_Game: public T_Engine 
{
public:
	PVZ_Game(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	~PVZ_Game();

	void GameInit();
	void GameLogic();
	void GameEnd();
	void GamePaint(HDC hdc);
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	void GameMouseAction(int x, int y, int ActionType);
private:
	int wnd_width, wnd_height;

	AudioDX ds;

	MainMenu mainMenu;
	HelpMenu helpMenu;
	ChoiceMenu choiceMenu;
	ChoiceMenu returnMenu;

	GameLevel gameLevel;

	void MenuInit();
	void AudioInit();
};