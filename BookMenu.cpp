#include "BookMenu.h"



BookMenu::BookMenu()
{
}


BookMenu::~BookMenu()
{
	
}

void BookMenu::InitZom()
{
	int btn_width = 113;
	int btn_height = 40;
	SetBtnBmp(L"res\\images\\interface\\menu\\handbook\\Button.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.fontName = L"黑体";
	menuInfo.focusTextColor = Color::Color(16,237,22);
	menuInfo.normalTextColor = Color::Color(16,237, 22);
	menuInfo.space = MENU_SPACE;
	menuInfo.isBold = true;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	SetMenuInfo(menuInfo);
	MENUITEM item;
	item.pos.x = 600;
	item.pos.y = 350;
	item.ItemName = L"查看僵尸";
	AddMenuItem(item);

}
void BookMenu::InitSun()
{
	int btn_width = 110;
	int btn_height = 41;
	SetBtnBmp(L"res\\images\\interface\\menu\\handbook\\Button.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.fontName = L"黑体";
	menuInfo.focusTextColor = Color::Color(255, 203, 105);
	menuInfo.normalTextColor = Color::Color(255, 203, 105);
	menuInfo.space = MENU_SPACE;
	menuInfo.isBold = true;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	SetMenuInfo(menuInfo);
	MENUITEM item;
	item.pos.x = 200;
	item.pos.y = 350;
	item.ItemName = L"查看植物";
	AddMenuItem(item);
}

void BookMenu::InitReturn()
{
	int btn_width = 89;
	int btn_height = 26;
	SetBtnBmp(L"res\\images\\interface\\menu\\handbook\\Almanac_CloseButton.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.fontName = L"黑体";
	menuInfo.focusTextColor = Color::Black;
	menuInfo.normalTextColor = Color::Black;
	menuInfo.space = MENU_SPACE;
	menuInfo.isBold = true;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	SetMenuInfo(menuInfo);
	MENUITEM item;
	item.pos.x = WIN_WIDTH - btn_width - 80;
	item.pos.y = WIN_HEIGHT - btn_height - 50 ;
	item.ItemName = L"返  回";
	AddMenuItem(item);
}
void BookMenu::InitShut() {
	int btn_width = 89;
	int btn_height = 26;
	SetBtnBmp(L"res\\images\\interface\\menu\\handbook\\Almanac_CloseButton.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.fontName = L"黑体";
	menuInfo.focusTextColor = Color::Black;
	menuInfo.normalTextColor = Color::Black;
	menuInfo.space = MENU_SPACE;
	menuInfo.isBold = true;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	SetMenuInfo(menuInfo);
	MENUITEM item;
	item.pos.x = WIN_WIDTH - btn_width - 80;
	item.pos.y = WIN_HEIGHT - btn_height - 15;
	item.ItemName = L"关闭";
	AddMenuItem(item);
}
void BookMenu::InitP_return() {
	int btn_width = 164;
	int btn_height = 26;
	SetBtnBmp(L"res\\images\\interface\\menu\\handbook\\Almanac_IndexButton.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.fontName = L"黑体";
	menuInfo.focusTextColor = Color::Black;
	menuInfo.normalTextColor = Color::Black;
	menuInfo.space = MENU_SPACE;
	menuInfo.isBold = true;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	SetMenuInfo(menuInfo);
	MENUITEM item;
	item.pos.x = 70;
	item.pos.y = WIN_HEIGHT - btn_height - 15;
	item.ItemName = L"返回索引";
	AddMenuItem(item);
}

int BookMenu::GetMenuIndex(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;
	int w = menu_info.width;
	int h = menu_info.height;
	RECT rec;
	int iCount = 0;
	vector<MENUITEM>::iterator iter;
	for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
	{
		rec.left = iter->pos.x;
		rec.top = iter->pos.y;
		rec.right = rec.left + w;
		rec.bottom = rec.top + h;

		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;

}

void BookMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	if (&gm_menuBkg != NULL && startState == true)
	{
		gm_menuBkg.PaintImage(hdc, (WIN_WIDTH - gm_menuBkg.GetImageWidth()) / 2, (WIN_HEIGHT - gm_menuBkg.GetImageHeight()) / 2,
			gm_menuBkg.GetImageWidth(), gm_menuBkg.GetImageHeight(), bkImageAlpha);
	}

	int w = menu_info.width;
	int h = menu_info.height;

	int FontHeight;
	int px = 0;
	int w_px = w / (MaxMenuItemLen + 1);	//计算每个字所占的像素
	int h_px = (int)((float)(h / 2.5));
	if (w_px > h_px)
	{
		px = h_px;
	}
	else
	{
		px = w_px;
	}
	FontHeight = (px * 72) / 88;		//根据每个字的像素计算字号

	if (isItemFocused == FALSE)
	{
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			// 绘制按钮图像
			if (&BtnDIB != NULL)
			{
				BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
			}
			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			// 绘制按钮文字
			wstring item = iter->ItemName.c_str();
			T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
				menu_info.normalTextColor, GetFontStyle(), GetAlignment());
		}
	}

	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		Gdiplus::RectF Rec;
		vector<MENUITEM>::iterator iter;
		for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;

			Rec.X = (float)x;
			Rec.Y = (float)y;
			Rec.Width = (float)w;
			Rec.Height = (float)h;

			if (mIndex != m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.normalTextColor, GetFontStyle(), GetAlignment());
			}

			if (mIndex == m_index)
			{
				if (&BtnDIB != NULL)
				{
					BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnTrans);
				}

				wstring item = iter->ItemName.c_str();
				T_Graph::PaintText(hdc, Rec, item, (REAL)FontHeight, menu_info.fontName,
					menu_info.focusTextColor, GetFontStyle(), GetAlignment());
			}

			mIndex = mIndex + 1;
		}
	}
}
