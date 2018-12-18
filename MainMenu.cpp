#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}
void MainMenu::InitBtn()
{
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
	//BtnBkg[i].Destroy();
}
void MainMenu::SetMenuBkg(LPCTSTR img_path, LPCTSTR img_path1, int alphaLevel, COLORREF backColor)
{
	if (wcslen(img_path) > 0)
	{
		gm_menuBkg.LoadImageFile(img_path);
		bkColor = backColor;
		bkImageAlpha = alphaLevel;
	}
	if (wcslen(img_path1) > 0)
	{
		menuBkg.LoadImageFile(img_path1);
		bkColor = backColor;
	}
}

void MainMenu::DrawMenu(HDC hdc, int bkgX, int bkgY, BYTE btnTrans, bool startState)
{
	if (&gm_menuBkg != NULL && &menuBkg != NULL && startState == true)
	{
		HBITMAP tBmp = T_Graph::CreateBlankBitmap(WIN_WIDTH, WIN_HEIGHT, bkColor);
		SelectObject(hdc, tBmp);
		
		gm_menuBkg.PaintImage(hdc, bkgX, bkgY, WIN_WIDTH, WIN_HEIGHT, bkImageAlpha);
		menuBkg.PaintImage(hdc, bkgX + 30, bkgY, WIN_WIDTH / 3, WIN_HEIGHT / 4, bkImageAlpha);
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
		if (&menuBkg != NULL)
		{
			menuBkg.PaintImage(
				hdc, bkgX, bkgY, menuBkg.GetImageWidth(), menuBkg.GetImageHeight(), bkImageAlpha
			);
		}
	}

	if (isItemFocused == FALSE)
	{
		for (int i = 0; i < BtnNUM-3; i++) {
			//BtnBkg[i].LoadImageFile(BtnPath[i]);
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
			//BtnBkg[i].LoadImageFile(BtnPath[i]);
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
	//BtnDIB.Destroy();
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
	if (m_index >= 0)
	{
		if (m_MoveSound && m_ClickSound)
		{
			m_MoveSound->Restore();
			m_ClickSound->Restore();
			m_ClickSound->Play(false);
		}
	}
	return m_index;
}
