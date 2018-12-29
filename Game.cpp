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
	else if(GameState == GAME_RUN)
	{
		gameLevel.Logic();
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
	if (GameState == GAME_HANDBOOK) {
		handMenu.Draw(hdc);
	}
	if (GameState == GAME_SUN) {
		handMenu.DrawSunInfo(hdc);
		handMenu.DrawPlants(hdc);
		GameState = 12;
	}
	if (GameState >= 12 && GameState <= 46) {
		handMenu.DrawPlantFrameInfo(hdc, GameState - 12);
	}
	if (GameState == GAME_ZOM) {
		handMenu.DrawZomInfo(hdc);
		handMenu.DrawZombies(hdc);
		GameState = 47;
	}
	if (GameState >= 47 && GameState <= 64) {
		handMenu.DrawZomFrameInfo(hdc,GameState - 47);
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
					GameState = GAME_HANDBOOK;  //图鉴
				case 3:
					break;
				case 4:
					GameState = GAME_START; //开始
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
			handMenu.MenuMouseMove(x, y);
		}
		if (Action == MOUSE_LCLICK) {
			int  index = handMenu.MenuMouseClick(x, y);
			switch (index)
			{
			case 0:
				GameState = GAME_START;
				break;
			case 1:
				GameState = GAME_SUN; //查看植物
				break;
			case 2:
				GameState = GAME_ZOM; 
				break;
			}
		}
	}
	else if (GameState == GAME_SUN || (GameState >= 12 && GameState <= 46))
	{
		if (Action == MOUSE_MOVE) {
			handMenu.PZMouseMove(x, y);
		}
		if (Action == MOUSE_LCLICK) {
			int index = handMenu.PZMouseClick(x, y);
			switch (index)
			{
			case 101:
				GameState = GAME_HANDBOOK;
				break;
			case 102:
				GameState = GAME_START;
				break;
			case 404:
				//GameState = GAME_SUN;
				break;
			default:
				GameState = index + 12;
				break;
			}
		}
	}
	else if (GameState == GAME_ZOM || (GameState >= 47 && GameState <= 64))
	{
		if (Action == MOUSE_MOVE) {
			handMenu.PZMouseMove(x, y);
		}
		if (Action == MOUSE_LCLICK) {
			int index = handMenu.PZMouseClick(x, y);
			switch (index)
			{
			case 101:
				GameState = GAME_HANDBOOK;
				break;
			case 102:
				GameState = GAME_START;
				break;
			case 404:
				//GameState = GAME_ZOM;
				break;
			default:
				GameState = index + 47;
				break;
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
	gameLevel.AudioInit(ds);
}


