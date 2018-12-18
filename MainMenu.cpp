#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}
void MainMenu::Init()
{
	SetMenuBkg(L"res\\images\\interface\\Surface.png");
	MENU_INFO menuInfo;
	menuInfo.align = 1;                      //对齐方式
	menuInfo.space = MENU_SPACE;               //菜单项之间的间隔距离
	menuInfo.fontName = L"黑体";
	menuInfo.isBold = true;

	SetMenuInfo(menuInfo);

	flickerImg[0].LoadImageFile(L"res\\images\\interface\\menu\\mainmenu\\SelectorScreen_Shadow_Adventure.png");
	flickerImg[1].LoadImageFile(L"res\\images\\interface\\menu\\mainmenu\\SelectorScreen_Shadow_Survival.png");
	flickerImg[2].LoadImageFile(L"res\\images\\interface\\menu\\mainmenu\\SelectorScreen_Shadow_Challenge.png");

	wstring rootpath = L"res\\images\\interface\\menu\\mainmenu\\";
	wstring fileType = L".png";
	int BtnEdge = - 25;					//菜单边距
	for (int i = 0; i < BtnNUM; i++) 
	{
		MENU_BTNWH_INFO mbi;
		wstring temp = T_Util::int_to_wstring(i + 1);

		if (i < 6) {
			BtnPath[i] = rootpath + temp + fileType;
			BtnBkg[i].LoadImageFile(BtnPath[i]);
		}
		switch(i) {
		case 0:	//冒险模式
			mbi.pos.x = WIN_WIDTH / 2+20;				//菜单X坐标
			mbi.pos.y = WIN_HEIGHT / 7;					//菜单Y坐标
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight() / 2;
			break;
		case 1://迷你游戏
			mbi.pos.x = BtnDIBWHInfo[0].pos.x;
			mbi.pos.y = BtnDIBWHInfo[0].pos.y + BtnEdge + BtnDIBWHInfo[0].height;
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight() / 2;
			break;
		case 2://益智模式
			mbi.pos.x = BtnDIBWHInfo[0].pos.x;
			mbi.pos.y = BtnDIBWHInfo[1].pos.y + BtnEdge + BtnDIBWHInfo[1].height;
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight() / 2;
			break;
		case 3://图鉴
			mbi.pos.x = WIN_WIDTH / 9*4;
			mbi.pos.y = WIN_HEIGHT /4*3-20;
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight() / 2;
			break;
		case 4://数据中心
			mbi.pos.x = WIN_WIDTH/20;
			mbi.pos.y = WIN_HEIGHT / 20 * 19 - BtnBkg[i].GetImageHeight()/2;
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight()/2;
			break;
		case 5://更改用户(显示用户信息)
			mbi.pos.x = 30;
			mbi.pos.y = WIN_HEIGHT / 4-10;
			mbi.width = BtnBkg[i].GetImageWidth();
			mbi.height = BtnBkg[i].GetImageHeight() / 2;
			break;
		case 6://选项
			mbi.pos.x = 620 * WIN_WIDTH /900;
			mbi.pos.y = 430 * WIN_HEIGHT /600;
			mbi.width = WIN_WIDTH / 9;
			mbi.height = WIN_HEIGHT / 6;
			break;
		case 7://帮助
			mbi.pos.x = 720 * WIN_WIDTH / 900 ;
			mbi.pos.y = 450 * WIN_HEIGHT / 600 ;
			mbi.width = 70 * WIN_WIDTH / 900;
			mbi.height = WIN_HEIGHT / 6;
			break;
		case 8://退出
			mbi.pos.x = 790 * WIN_WIDTH / 900 ;
			mbi.pos.y = 450 * WIN_HEIGHT / 600;
			mbi.width = WIN_WIDTH / 9;
			mbi.height = WIN_HEIGHT / 6;
			break;
		}
		BtnDIBWHInfo[i] = mbi;
	}
}

void MainMenu::SetMenuBkg(wstring img_path, int alphaLevel, COLORREF backColor)
{
	if (img_path.length() > 0)
	{
		gm_menuBkg.LoadImageFile(img_path);
		bkColor = backColor;
		bkImageAlpha = alphaLevel;
	}
	menuBkg[0].LoadImageFile(L"res\\images\\interface\\SelectorScreen_WoodSign1_32.png");
	menuBkg[1].LoadImageFile(L"res\\images\\interface\\SelectorScreen_WoodSign3_32.png");

}

void MainMenu::DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans, bool startState)
{
	
	if (&gm_menuBkg != NULL && &menuBkg[0] != NULL && &menuBkg[1] != NULL && startState == true)
	{
		HBITMAP tBmp = T_Graph::CreateBlankBitmap(WIN_WIDTH, WIN_HEIGHT, bkColor);
		SelectObject(hdc, tBmp);
		//背景图层
		gm_menuBkg.PaintImage(hdc, bkgX, bkgY, WIN_WIDTH, WIN_HEIGHT, bkImageAlpha);
		menuBkg[0].PaintImage(hdc, bkgX + 30, bkgY, WIN_WIDTH / 3, WIN_HEIGHT / 4, bkImageAlpha);
		
		DeleteObject(tBmp);
		tBmp = NULL;
	}
	else
	{
		T_Graph::PaintBlank(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, MENU_BKCLR, MENU_ALPHA);

		if (&gm_menuBkg != NULL)
		{
			gm_menuBkg.PaintImage(
				hdc, bkgX, bkgY, gm_menuBkg.GetImageWidth(), gm_menuBkg.GetImageHeight(), bkImageAlpha
			);
		}
		if (&menuBkg[0] != NULL)
		{
			menuBkg[0].PaintImage(
				hdc, bkgX, bkgY, menuBkg[0].GetImageWidth(), menuBkg[0].GetImageHeight(), bkImageAlpha
			);
		}
		if (&menuBkg[1] != NULL)
		{
			menuBkg[1].PaintImage(
				hdc, bkgX, bkgY, menuBkg[1].GetImageWidth(), menuBkg[1].GetImageHeight(), bkImageAlpha
			);
		}
	}

	//画菜单
	if (isItemFocused == FALSE)
	{
		for (int i = 0; i < BtnNUM-3; i++) {
			if (&BtnBkg[i] != NULL)
			{
				BtnBkg[i].PaintRegion(BtnBkg[i].GetBmpHandle(),hdc, BtnDIBWHInfo[i].pos.x, BtnDIBWHInfo[i].pos.y,0,0, BtnDIBWHInfo[i].width, BtnDIBWHInfo[i].height,1);
			}
		}
	}
	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		for (int i = 0; i < BtnNUM-3; i++) {
			if (mIndex != m_index)
			{
				if (&BtnBkg[i] != NULL)
				{
					BtnBkg[i].PaintRegion(BtnBkg[i].GetBmpHandle(), hdc, BtnDIBWHInfo[i].pos.x, BtnDIBWHInfo[i].pos.y, 0, 0, BtnDIBWHInfo[i].width, BtnDIBWHInfo[i].height, 1, 0, btnTrans);
				}	
			}
			if (mIndex == m_index)
			{
				if (&BtnBkg[i] != NULL)
				{
					BtnBkg[i].PaintRegion(BtnBkg[i].GetBmpHandle(), hdc, BtnDIBWHInfo[i].pos.x, BtnDIBWHInfo[i].pos.y, 0, BtnDIBWHInfo[i].height, BtnDIBWHInfo[i].width, BtnDIBWHInfo[i].height, 1, 0, btnTrans);
				}
			}

			mIndex = mIndex + 1;
		}
	}
	//遮盖图层
	menuBkg[1].PaintImage(hdc, bkgX + 30, bkgY + WIN_HEIGHT / 3-5, 90, 30, bkImageAlpha);
	//闪动
	if (flickerFlag == true) {
		if (m_index >= 0 && m_index < 3 && FrameCount%8>4) {
			flickerImg[m_index].PaintRegion(flickerImg[m_index].GetBmpHandle(), hdc, BtnDIBWHInfo[m_index].pos.x, BtnDIBWHInfo[m_index].pos.y-5, 0, 0, BtnDIBWHInfo[m_index].width, BtnDIBWHInfo[m_index].height, 1, 0);
		}
		FrameCount++;
	}
}

int MainMenu::GetMenuIndex(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;
	RECT rec;

	int iCount = 0;
	for (int i = 0;i<BtnNUM;i++)
	{
		rec.left = BtnDIBWHInfo[i].pos.x;
		rec.top = BtnDIBWHInfo[i].pos.y;
		rec.right = rec.left + BtnDIBWHInfo[i].width;
		rec.bottom = rec.top + BtnDIBWHInfo[i].height;

		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;
}
void MainMenu::MenuMouseMove(int x, int y)
{
	lastIndex = m_index;//记录前一次的索引值
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		isItemFocused = true;
		//保证鼠标移过按钮只播放一次声音
		if (lastIndex != m_index)
		{
			if (m_MoveSound && m_ClickSound)
			{
				m_ClickSound->Restore();
				m_MoveSound->Restore();
				m_MoveSound->Play(false);
			}
		}
	}
	else
	{
		isItemFocused = false;
	}
}
int MainMenu::MenuMouseClick(int x, int y)
{
	m_index = GetMenuIndex(x, y);
	//进入游戏，播放音乐
	if (m_index >= 0&& m_index < 3)
	{
		if (m_MoveSound && m_ClickSound)
		{
			m_MoveSound->Restore();
			m_ClickSound->Restore();
			m_ClickSound->Play(false);
			mainmenu_backmusic_buffer.Stop();
			flickerFlag = true;
		}
	}
	if (m_index >= 3) 
	{
		nomain_mousedown_buffer.Restore();
		nomain_mousedown_buffer.Play(false);
	}
	return m_index;
}

void MainMenu::MenuAudioInit(AudioDX &ds)
{
	SetClickSound(&mousedown_buffer);
	SetMoveSound(&mousemove_buffer);
	mainmenu_backmusic_buffer.LoadWave(ds, L"res\\audio\\faster.wav");
	mousedown_buffer.LoadWave(ds, L"res\\audio\\evillaugh.wav");
	mousemove_buffer.LoadWave(ds, L"res\\audio\\bleep.wav");
	nomain_mousedown_buffer.LoadWave(ds, L"res\\audio\\buttonclick.wav");
	mainmenu_backmusic_buffer.Play(true);
}
