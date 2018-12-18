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

	MenuInit();
	GameState = GAME_START;
	AudioInit();
}

void PVZ_Game::GameLogic()
{
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
			if (GameState == GAME_START)
			{
				int index = mainMenu.MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (index)
					{
					case 0:
					case 1:
					case 2:
						GameState = GAME_RUN;
						break;
					case 3:
						GameState = GAME_HANDBOOK;
						break;
					case 4:
						break;
					case 5:
						GameState = GAME_ABOUT;
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
	}
}

void PVZ_Game::MenuInit()
{
	mainMenu.Init();
	
}

void PVZ_Game::AudioInit()
{
	if (!ds.CreateDS(m_hWnd))return;
	mainMenu.MenuAudioInit(ds);
}
