#include "Game.h"
#include "resource.h"
int WINAPI wWinMain(HINSTANCE h_Instance,
	HINSTANCE hPrevInstance,
	LPWSTR    szpCmdLine,
	int      iCmdShow)
{
	LPCTSTR WinTitle = L"Plants VS Zombies";

	PVZ_Game* pGame = new PVZ_Game(h_Instance, WIN_CLASS, WinTitle, IDI_ICON_MAIN, IDI_ICON_MAIN, WIN_WIDTH, WIN_HEIGHT);
	T_Engine::pEngine = pGame;
	pGame->SetFrame(50);
	pGame->StartEngine();
}