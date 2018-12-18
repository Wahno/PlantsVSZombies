#include "HelpMenu.h"

void HelpMenu::Init()
{
	SetMenuBkg(L"res\\images\\interface\\menu\\help.png");
	MENUITEM item;
	item.pos.x = 0;
	item.pos.y = 0;

	AddMenuItem(item);
	menu_info.width = WIN_WIDTH;
	menu_info.height = WIN_HEIGHT;
}

void HelpMenu::MenuMouseClick()
{
	mousedown_buffer.Play(false);
}

void HelpMenu::AudioInit(AudioDX & ds)
{
	mousedown_buffer.LoadWave(ds, L"res\\audio\\plant1.wav");
}

void HelpMenu::DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans, bool startState)
{
	if (&gm_menuBkg != NULL && startState == true)
	{
		//±³¾°Í¼²ã
		gm_menuBkg.PaintImage(hdc, bkgX, bkgY, gm_menuBkg.GetImageWidth(), gm_menuBkg.GetImageHeight(), bkImageAlpha);
	}
}
