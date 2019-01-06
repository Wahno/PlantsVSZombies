#include "GameLevelMenu.h"



GameLevelMenu::GameLevelMenu()
{
}


GameLevelMenu::~GameLevelMenu()
{
}

void GameLevelMenu::InitButtton()
{
	buttonWidth = 113;
	buttonHeight = 41;
	XSpace = 20;
	buttonSpace = 10;
	YSpace = 10;
	pauseButton.buttonImg.LoadImageFile(L"res\\images\\interface\\menu\\handbook\\Button.png");
	pauseButton.pt.x = WIN_WIDTH - 2 * buttonWidth - XSpace - buttonSpace;
	pauseButton.pt.y = YSpace;
	pauseButton.name = L"ÔÝ  Í£";
	returnMainButtton.buttonImg.LoadImageFile(L"res\\images\\interface\\menu\\handbook\\Button.png");
	returnMainButtton.pt.x = WIN_WIDTH - buttonWidth - XSpace;
	returnMainButtton.pt.y = YSpace;
	returnMainButtton.name = L"²Ë  µ¥";
}

void GameLevelMenu::Draw(HDC hdc)
{
	InitButtton();
	pauseButton.buttonImg.PaintImage(hdc,pauseButton.pt.x,pauseButton.pt.y);
	RectF pauseName;
	pauseName.Width = buttonWidth;
	pauseName.Height = buttonHeight;
	pauseName.X = pauseButton.pt.x;
	pauseName.Y = pauseButton.pt.y;
	T_Graph::PaintText(hdc,pauseName,pauseButton.name,16,L"Î¢ÈíÑÅºÚ",Color::Color(0, 203, 8),FontStyle::FontStyleRegular,StringAlignmentCenter);
	returnMainButtton.buttonImg.PaintImage(hdc, returnMainButtton.pt.x, returnMainButtton.pt.y);
	pauseName.X = returnMainButtton.pt.x;
	pauseName.Y = returnMainButtton.pt.y;
	T_Graph::PaintText(hdc, pauseName, returnMainButtton.name, 16, L"Î¢ÈíÑÅºÚ", Color::Color(0, 203, 8), FontStyle::FontStyleRegular, StringAlignmentCenter);
}

int GameLevelMenu::MouseClick(int x, int y)
{
	POINT pt = { x,y };
	RECT pauseRect;
	pauseRect.left = pauseButton.pt.x;
	pauseRect.right = pauseButton.pt.x+ buttonWidth ;
	pauseRect.top = pauseButton.pt.y;
	pauseRect.bottom = pauseButton.pt.y + buttonHeight;
	RECT returnRect;
	returnRect.left = returnMainButtton.pt.x;
	returnRect.right = returnMainButtton.pt.x + buttonWidth;
	returnRect.top = returnMainButtton.pt.y;
	returnRect.bottom = returnMainButtton.pt.y + buttonHeight;
	if (PtInRect(&pauseRect, pt)) {
		return 0;
	}
	if (PtInRect(&returnRect, pt)) {
		return 1;
	}
	return -1;
}
