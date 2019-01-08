#include "Game.h"

bool PVZ_Game::levlechange = false;
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
			levlechange = false;
			gameLevel.Init();
			//gameLevel2.Init();
			//gameLevel3.Init();
		}
	}
	else if(GameState == GAME_RUN)
	{
		if (levlechange)
		{
			level++;
			if (level == 2)
			{
				gameLevel2.Init();
			}
			else if (level == 3)
			{
				gameLevel3.Init();
			}
		}
		if (level == 1)
		{
			gameLevel.Logic();
			levlechange = gameLevel.getGameFlag();
		}
		else if (level == 2)
		{
			gameLevel2.Logic();
			levlechange = gameLevel2.getGameFlag();
		}
		else if (level == 3)
		{
			gameLevel3.Logic();
			levlechange = gameLevel3.getGameFlag();
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
		if (level == 1)
		{
			gameLevel.Draw(hdc);
		}
		else if (level == 2)
		{
			gameLevel2.Draw(hdc);
		}
		else if (level == 3)
		{
			gameLevel3.Draw(hdc);
		}
	}
	if (GameState == GAME_HANDBOOK) {
		if (handMenu.HandBookState == BOOK_SUN) {
			handMenu.DrawSunInfo(hdc);
			handMenu.DrawPlants(hdc);
			handMenu.HandBookState = 2;
		}else if (handMenu.HandBookState == BOOK_ZOM) {
			handMenu.DrawZomInfo(hdc);
			handMenu.DrawZombies(hdc);
			handMenu.HandBookState = 38;
		}else if (handMenu.HandBookState >= 2 && handMenu.HandBookState <= 37) {
			handMenu.DrawPlantFrameInfo(hdc, handMenu.HandBookState - 2);
		}else if (handMenu.HandBookState >= 38 && handMenu.HandBookState <= 48) {
			handMenu.DrawZomFrameInfo(hdc, handMenu.HandBookState - 38);
		}
		else
		{
			handMenu.Draw(hdc);
		}
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
					GameState = GAME_HANDBOOK;
					break;
				case 4:
					break;
				case 5:
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
					GameState = GAME_START;
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
	else if (GameState == GAME_HANDBOOK) {
		if (Action == MOUSE_MOVE)
		{
			if (handMenu.HandBookState == BOOK_SUN ||
				(handMenu.HandBookState >= 2 && handMenu.HandBookState <= 37) || 
				handMenu.HandBookState == BOOK_ZOM  ||
				(handMenu.HandBookState >= 38 && handMenu.HandBookState <= 48)) 
			{
				handMenu.PZMouseMove(x,y);
			}
			else {
				handMenu.MenuMouseMove(x, y);
			}
		}
		if (Action == MOUSE_LCLICK) {
			int  index = 0;
			if (handMenu.HandBookState == BOOK_SUN || 
				(handMenu.HandBookState >= 2 && handMenu.HandBookState <= 37)) {
				index = handMenu.PZMouseClick(x,y);
				switch (index)
				{
				case 101:
					GameState = GAME_HANDBOOK;
					handMenu.HandBookState = 100;
					break;
				case 102:
					GameState = GAME_START;
					handMenu.HandBookState = 100;
					break;
				case 404:
					//GameState = GAME_SUN;
					break;
				default:
					handMenu.HandBookState = index + 2;
					break;
				}
			}
			else if (handMenu.HandBookState == BOOK_ZOM || 
				(handMenu.HandBookState >= 38 && handMenu.HandBookState <= 48)) {
				index = handMenu.PZMouseClick(x,y);
				switch (index)
				{
				case 101:
					GameState = GAME_HANDBOOK;
					handMenu.HandBookState = 100;
					break;
				case 102:
					GameState = GAME_START;
					handMenu.HandBookState = 100;
					break;
				case 404:
					//GameState = GAME_ZOM;
					break;
				default:
					handMenu.HandBookState = index + 38;
					break;
				}
			}
			else
			{
				index = handMenu.MenuMouseClick(x, y);
				switch (index)
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					handMenu.HandBookState = BOOK_SUN;
					break;
				case 2:
					handMenu.HandBookState = BOOK_ZOM;
					break;
				}
			}
		}
	}
	else if (GameState == GAME_RUN)
	{
		if (Action == MOUSE_MOVE)
		{
			if (level == 1)
			{
				gameLevel.MouseMove(x, y);
			}
			else if (level == 2)
			{
				gameLevel2.MouseMove(x, y);
			}
			else if (level == 3)
			{
				gameLevel3.MouseMove(x, y);
			}
			
		}
		else if (Action == MOUSE_LCLICK)
		{
			if (level == 1)
			{
				gameLevel.MouseClick(x, y);
			}
			else if (level == 2)
			{
				gameLevel2.MouseClick(x, y);
			}
			else if (level == 3)
			{
				gameLevel3.MouseClick(x, y);
			}		
			int	index = gameLevelMenu.MouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_PAUSE;
					break;
				case 1:
					GameState = GAME_SETTING;
					break;
				default:
					break;
				}
			}
		}
	}
	else if (GameState == GAME_PAUSE) {
		if (Action == MOUSE_LCLICK) {
			int	index = gameLevelMenu.MouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_RUN;
					break;
					/*case 1:
					GameState = GAME_SETTING;
					break;*/
				default:
					break;
				}
			}
		}
	}

	
}

void PVZ_Game::MenuInit()
{
	mainMenu.Init();
	helpMenu.Init();
	choiceMenu.Init();
	returnMenu.returnMenuInit();
	handMenu.Init();
}

void PVZ_Game::AudioInit()
{
	if (!ds.CreateDS(m_hWnd))return;
	mainMenu.AudioInit(ds);
	helpMenu.AudioInit(ds);
	if (level == 1)
	{
		gameLevel.AudioInit(ds);
	}
	else if (level == 2)
	{
		gameLevel2.AudioInit(ds);
	}
	else if (level == 3)
	{
		gameLevel3.AudioInit(ds);
	}
}


