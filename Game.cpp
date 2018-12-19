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
	ChoiceMenuInit();
	ReturnMenuInit();
	GameState = GAME_START;
	
}

void PVZ_Game::GameLogic()
{
	if (GameState == GAME_START)
	{
		if (mainMenu.FrameCount > mainMenu.MaxFrameCount) 
		{

			//GameState = GAME_RUN;
			mainMenu.flickerFlag = false;
			mainMenu.FrameCount = 0;
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
					break;
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
}

void PVZ_Game::MenuInit()
{
	mainMenu.Init();
	helpMenu.Init();
}

void PVZ_Game::AudioInit()
{
	if (!ds.CreateDS(m_hWnd))return;
	mainMenu.AudioInit(ds);
	helpMenu.AudioInit(ds);
}
void PVZ_Game::ChoiceMenuInit() {
	choiceMenu.SetMenuBkg(L"res\\images\\interface\\menu\\choicemenu\\OptionsMenuback8.png");
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Color normalClr, focusClr;
	wstring menuItems[] = { L"游戏选关",L"游戏调速",L"查看图鉴",L"重新开始",L"返回菜单" };
	btn_width = 360;
	btn_height = 100;
	normalClr = Color::Yellow;
	focusClr = Color::White;
	choiceMenu.SetBtnBmp(L"res\\images\\interface\\menu\\choicemenu\\OptionsBackButton8.png", btn_width, btn_height);

	//设置菜单信息
	MENU_INFO menuInfo;
	menuInfo.align = 1;   //对齐方式居中
	menuInfo.space = MENU_SPACE; //菜单项之间的间隔距离
	menuInfo.width = btn_width; //菜单项宽
	menuInfo.height = btn_height; //菜单项高
	menuInfo.fontName = L"黑体"; //菜单项字体
	menuInfo.isBold = true; //是否粗体
	menuInfo.normalTextColor = normalClr; //正常状态文字
	menuInfo.focusTextColor = focusClr;  //选中状态文字
	choiceMenu.SetMenuInfo(menuInfo);
	for (int i = 0; i < 5; i++)
	{
		//垂直居中布局坐标
		x = 290;
		//y =  10 + i * (btn_height + MENU_SPACE) + (wnd_height - 6* btn_height - 5* MENU_SPACE) / 6;
		y = 220 + i * 50;
		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];   //当前菜单项文字
		choiceMenu.AddMenuItem(mItem);
	}

}
void PVZ_Game::ReturnMenuInit() {
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Color normalClr, focusClr;
	wstring menuItems = { L"返回游戏" };
	btn_width = 360;
	btn_height = 100;
	normalClr = Color::Yellow;
	focusClr = Color::White;
	returnMenu.SetBtnBmp(L"res\\images\\interface\\menu\\choicemenu\\OptionsBackButton8.png", btn_width, btn_height);
	//设置菜单信息
	MENU_INFO menuInfo;
	menuInfo.align = 1;   //对齐方式居中
	menuInfo.space = MENU_SPACE; //菜单项之间的间隔距离
	menuInfo.width = btn_width; //菜单项宽
	menuInfo.height = btn_height; //菜单项高
	menuInfo.fontName = L"黑体"; //菜单项字体
	menuInfo.isBold = true; //是否粗体
	menuInfo.normalTextColor = normalClr; //正常状态文字
	menuInfo.focusTextColor = focusClr;  //选中状态文字
	returnMenu.SetMenuInfo(menuInfo);

	//垂直居中布局坐标
	x = 200;
	//y =  10 + i * (btn_height + MENU_SPACE) + (wnd_height - 6* btn_height - 5* MENU_SPACE) / 6;
	y = 476;
	MENUITEM mItem;
	mItem.pos.x = x;
	mItem.pos.y = y;
	mItem.ItemName = menuItems;   //当前菜单项文字
	returnMenu.AddMenuItem(mItem);
}


