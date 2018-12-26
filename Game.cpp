#include "Game.h"

PVZ_Game::PVZ_Game(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, 
	WORD Icon, WORD SmIcon, int iWidth, int iHeight) :T_Engine(hInstance,
		szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight)
{
	srand((unsigned)time(NULL));
	wnd_width = iWidth;
	wnd_height = iHeight;
}

PVZ_Game::~PVZ_Game()
{
}

void PVZ_Game::GameInit()
{
	AudioInit();
	MenuInit();
	GameState = GAME_START;
	
}

void PVZ_Game::GameLogic()
{
	if (GameState == GAME_START)
	{
		if (mainMenu.FrameCount > mainMenu.MaxFrameCount) 
		{

			GameState = GAME_RUN;
			mainMenu.flickerFlag = false;
			mainMenu.FrameCount = 0;
			gameLevel.Init();
		}
	}
}

void PVZ_Game::GameEnd()
{
}

void PVZ_Game::GamePaint(HDC hdc)
{
	if (GameState == GAME_START) 
	{
		mainMenu.DrawMenu(hdc);
	}
	if (GameState == GAME_SETTING) {
		choiceMenu.DrawMenu(hdc, 255, true, 0.5);
		returnMenu.DrawMenu(hdc, 255, true, 1);
	}
	if (GameState == GAME_HELP)
	{
		helpMenu.DrawMenu(hdc,wnd_width/6,wnd_height/6);
	}
	if (GameState == GAME_RUN) 
	{
		gameLevel.Draw(hdc);
	}
}

void PVZ_Game::GameKeyAction(int ActionType)
{
}

void PVZ_Game::GameMouseAction(int x, int y, int Action)
{
	if (GameState == GAME_START)
	{
		if (Action == MOUSE_MOVE&&GameState != GAME_RUN)
		{
			mainMenu.MenuMouseMove(x, y);
		}
		if (Action == MOUSE_LCLICK)
		{
			int index = mainMenu.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
				case 1:
				case 2:
					break;
				case 3:
					//GameState = GAME_HANDBOOK;
					break;
				case 4:
					break;
				case 5:
					//GameState = GAME_ABOUT;
					break;
				case 6:
					GameState = GAME_SETTING;
					break;
				case 7:
					GameState = GAME_HELP;
					break;
				case 8:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
	}
	else if (GameState == GAME_SETTING) {
		if (Action == MOUSE_MOVE) {
			choiceMenu.MenuMouseMove(x, y, 0.5);
			returnMenu.MenuMouseMove(x, y, 1);
		}
		if (Action == MOUSE_LCLICK) {
			int  index = choiceMenu.MenuMouseClick(x, y, 0.5);
			if (index >= 0) {
				switch (index)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					GameState = GAME_HANDBOOK;  //Í¼¼ø
				case 3:
					break;
				case 4:
					GameState = GAME_START; //¿ªÊ¼
					break;
				case 5:
					break;
				}
			}
			index = 0;
			index = returnMenu.MenuMouseClick(x, y, 1);
			if (index >= 0) {
				switch (index)
				{
				case 0:
					break;
				}
			}
		}
		
	}
	else if (GameState == GAME_HELP) {
		if (Action == MOUSE_LCLICK)
		{
			helpMenu.MenuMouseClick();
			GameState = GAME_START;
		}
	}
}

void PVZ_Game::MenuInit()
{
	mainMenu.Init();
	helpMenu.Init();
	choiceMenu.Init();
	returnMenu.returnMenuInit();
}

void PVZ_Game::AudioInit()
{
	if (!ds.CreateDS(m_hWnd))return;
	mainMenu.AudioInit(ds);
	helpMenu.AudioInit(ds);
	gameLevel.AudioInit(ds);
}


