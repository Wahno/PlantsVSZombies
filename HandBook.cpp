#include "HandBook.h"



HandBook::HandBook()
{
	ratio = 0.8; 
}


HandBook::~HandBook()
{
}
/*初始化所有资源*/
void HandBook::Init()
{
	back = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Almanac_IndexBack.jpg"); //加载背景图片
	zombie = new T_Graph(L"res\\images\\interface\\menu\\handbook\\2.gif"); //加载僵尸图片
	sunflower = new T_Graph(L"res\\images\\interface\\menu\\handbook\\0.gif"); //加载向日葵图片
	info_frame = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Almanac_PlantCard.png");
	grass = new T_Graph(L"res\\images\\interface\\menu\\handbook\\sod3row.png");
		
	zom.InitZom(); 
	sun.InitSun();
	r_button.InitReturn();
	//LoadTxtPlants();
	shut.InitShut();
	p_return.InitP_return();
}

int HandBook::GetMenuIndex(int x, int y)
{
	int index = 0;
	if (r_button.GetMenuIndex(x, y) >= 0) {
		return 0; //返回按钮
	}
	else if (sun.GetMenuIndex(x, y) >= 0)
	{
		return 1;  //向日葵按钮
	}
	else
	{
		return 2; //僵尸按钮
	}
}



void HandBook::Draw(HDC hdc)
{	
	/*画背景、向日葵、僵尸图片*/
	back->PaintImage(hdc,(WIN_WIDTH - back->GetImageWidth()) / 2,(WIN_HEIGHT - back->GetImageHeight()) / 2,back->GetImageWidth(),back->GetImageHeight());
	sunflower->PaintImage(hdc,(WIN_WIDTH/2-sunflower->GetImageWidth())/2 + 30,
		(WIN_HEIGHT - sunflower->GetImageHeight())/ 2 - 30,
		sunflower->GetImageWidth(),sunflower->GetImageHeight(),255);
	zombie->PaintImage(hdc, WIN_WIDTH / 2 + (WIN_WIDTH / 2 - zombie->GetImageWidth()) / 2 - 60,
		(WIN_HEIGHT- zombie->GetImageHeight())/2 - 30,zombie->GetImageWidth(),zombie->GetImageHeight(),255);
	/*标题*/
	wstring info = L"图鉴——索引";
	RectF text;
	text.Width = 300;
	text.Height = 50;
	text.X = (WIN_WIDTH - text.Width) / 2;
	text.Y = 25;
	T_Graph::PaintText(hdc, text, info, 20, L"微软雅黑", Color::Black, FontStyleBold, StringAlignmentCenter);
	zom.DrawMenu(hdc);
	sun.DrawMenu(hdc);
	r_button.DrawMenu(hdc);
}

//void HandBook::GameMouseAction(int x, int y, int ActionType)
//{
//
//}

int HandBook::MenuMouseClick(int x, int y)
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

void HandBook::MenuMouseMove(int x, int y)
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

void HandBook::DrawSunInfo(HDC hdc)
{
	sun_back = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Almanac_PlantBack.jpg");
	sun_back->PaintImage(hdc,(WIN_WIDTH - sun_back->GetImageWidth())/2,(WIN_HEIGHT - sun_back->GetImageHeight()) / 2,
		sun_back->GetImageWidth(),sun_back->GetImageHeight());
	info_frame->PaintImage(hdc,WIN_WIDTH * 3 / 5 - 25 ,(WIN_HEIGHT - info_frame->GetImageHeight())/2 + 20,
		info_frame->GetImageWidth(),info_frame->GetImageHeight());
	p_return.DrawMenu(hdc);
	shut.DrawMenu(hdc);
	wstring info = L"图鉴——植物";
	RectF text;
	text.Width = 300;
	text.Height = 50;
	text.X = (WIN_WIDTH - text.Width) / 2;
	text.Y = 20;
	T_Graph::PaintText(hdc, text, info, 20, L"微软雅黑", Color::Color(255, 203, 105), FontStyleBold, StringAlignmentCenter);
	//grass = new T_Graph(L"res\\images\\interface\\menu\\handbook\\sod3row.png");
	HBITMAP hbitmp = grass->GetBmpHandle();
	grass->PaintRegion(hbitmp,hdc,WIN_WIDTH * 3 /5 + 27,(WIN_HEIGHT)/5 - 16,20,20,200,145,1);
}
void HandBook::DrawZomInfo(HDC hdc)
{
	sun_back = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Almanac_ZombieBack.jpg");
	sun_back->PaintImage(hdc, (WIN_WIDTH - sun_back->GetImageWidth()) / 2, (WIN_HEIGHT - sun_back->GetImageHeight()) / 2,
		sun_back->GetImageWidth(), sun_back->GetImageHeight());
	info_frame->PaintImage(hdc, WIN_WIDTH * 3 / 5 - 25, (WIN_HEIGHT - info_frame->GetImageHeight()) / 2 + 20,
		info_frame->GetImageWidth(), info_frame->GetImageHeight());
	p_return.DrawMenu(hdc);
	shut.DrawMenu(hdc);
	wstring info = L"图鉴——僵尸";
	RectF text;
	text.Width = 300;
	text.Height = 50;
	text.X = (WIN_WIDTH - text.Width) / 2;
	text.Y = 20;
	T_Graph::PaintText(hdc, text, info, 20, L"微软雅黑", Color::Color(16, 237, 22), FontStyleBold, StringAlignmentCenter);
	//grass = new T_Graph(L"res\\images\\interface\\menu\\handbook\\sod3row.png");
	HBITMAP hbitmp = grass->GetBmpHandle();
	grass->PaintRegion(hbitmp, hdc, WIN_WIDTH * 3 / 5 + 27, (WIN_HEIGHT) / 5 - 16, 20, 20, 200, 145, 1);
}
// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
// 如果存在，解析关键字后的值并转换成字符串，通过第三个参数输出
void HandBook::GetTxtMapValue(wstring str, wstring keywords, wstring& value)
{
	int pos;
	pos = (int)(str.find(keywords));
	if (pos != -1)
	{
		pos = (int)(str.find(L"="));
		value = str.substr(pos + 1, wcslen(str.c_str())).c_str();
		pos = (int)(value.find(L">"));
		if (pos != -1)
		{
			value = value.substr(0, pos);
		}
	}
}

// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
// 如果存在，解析关键字后的值并转换成整型，通过第三个参数输出
void HandBook::GetTxtMapValue(wstring str, wstring keywords, int& value)
{
	int pos;
	pos = (int)(str.find(keywords));
	if (pos != -1)
	{
		pos = (int)(str.find(L"="));
		value = _wtoi(str.substr(pos + 1, wcslen(str.c_str())).c_str());
	}
}

void HandBook::DrawPlants(HDC hdc)
{
	LoadTxt("res\\images\\interface\\menu\\handbook\\plants.txt",plants);
	vector<PZ>::iterator p;
	int initX = 70;
	int initY = 100;
	int offsetX = 0;
	int offsetY = 0;
	int posX = initX + offsetX;
	int posY = initY + offsetY;
	for (p = plants.begin(); p != plants.end(); p ++)
	{
		offsetX = (p->count % 5) * width * 0.85 ;
		offsetY = (p->count / 5) * height * 0.85 ;
		posX = initX + offsetX;
		posY = initY + offsetY; //画图的位置
		T_Graph* plant = new T_Graph(p->smallPath);
		HBITMAP hbitmap = plant->GetBmpHandle();
		plant->PaintRegion(hbitmap,hdc,posX,posY,0,0,width,height,ratio); //缩放0.8倍
		plant = NULL;
	}
}

void HandBook::DrawZombies(HDC hdc)
{
	LoadTxt("res\\images\\interface\\menu\\handbook\\zombies.txt",zombies);
	vector<PZ>::iterator p;
	int initX = 70;
	int initY = 100;
	int offsetX = 0;
	int offsetY = 0;
	int posX = initX + offsetX;
	int posY = initY + offsetY;
	for (p = zombies.begin(); p != zombies.end(); p++)
	{
		offsetX = (p->count % 5) * width * 0.85;
		offsetY = (p->count / 5) * height * 0.85;
		posX = initX + offsetX;
		posY = initY + offsetY; //画图的位置
		T_Graph* zombie = new T_Graph(p->smallPath);
		HBITMAP hbitmap = zombie->GetBmpHandle();
		zombie->PaintRegion(hbitmap, hdc, posX, posY, 0, 0, width, height, ratio); //缩放0.8倍
		zombie = NULL;
	}
}

bool HandBook::LoadTxt(const char * filepath,vector<PZ> &pzs)
{
	wifstream infile(filepath, ios::in);  //读入文件
	infile.imbue(locale(infile.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>));


	if (!infile) { return false; }

	wchar_t *l_str = new wchar_t[1024];
	wstring line_str = L"";
	//wstring info = L"";
	wstring currentZomId = L"";
	PZ pz;
	int i = 0;

	while (!infile.eof())
	{

		infile.getline(l_str, 1024); //按行读取，读取结果存入l_str
		line_str = wstring(l_str);
		//wsprintf(line_str,"%wc",);
		//判断读取的每行内容是否有所需关键字
		GetTxtMapValue(line_str, L"count", count);
		GetTxtMapValue(line_str, L"width", width);
		GetTxtMapValue(line_str, L"height", height);
		GetTxtMapValue(line_str, L"smallpath", smallPath);
		GetTxtMapValue(line_str, L"bigpath", bigPath);
		if (line_str.find(L"<layer") != -1) {
			GetTxtMapValue(line_str, L"id", currentZomId);
		}
		if (line_str.find(L"<name>") != -1) {
			int pos = (int)(line_str.find(L"<name>"));
			if (pos > 0 && pos < (int)(line_str.length() - 1)) {
				int next = (int)(line_str.find(L"</name>"));
				if (next > 0 && next < (int)(line_str.length() - 1)) {
					line_str = line_str.substr(pos + 6, next - 7);
				}
				pz.name = pz.name + line_str;
			}
		}
		if (line_str.find(L"<tip>") != -1) {
			int pos = (int)(line_str.find(L"<tip>"));
			if (pos > 0 && pos < (int)(line_str.length() - 1)) {
				int next = (int)(line_str.find(L"</tip>"));
				if (next > 0 && next < (int)(line_str.length() - 1)) {
					line_str = line_str.substr(pos + 5, next - 6);
				}
				pz.tip = pz.tip + line_str;
			}
		}
		if (line_str.find(L"<description>") != -1) {
			int pos = (int)(line_str.find(L"<description>"));
			if (pos > 0 && pos < (int)(line_str.length() - 1)) {
				int next = (int)(line_str.find(L"</description>"));
				if (next > 0 && next < (int)(line_str.length() - 1)) {
					line_str = line_str.substr(pos + 13, next - 14);
				}
				pz.info = pz.info + line_str;
			}
		}
		if (!pz.name.empty() && !pz.tip.empty() 
			&& !pz.info.empty()) {
			pz.smallPath = smallPath + currentZomId;
			pz.bigPath = bigPath + currentZomId;
			pz.count = i;
			i++;
			pzs.push_back(pz);
			pz.name = L"";
			pz.tip = L"";
			pz.sunNum = L"";
			pz.info = L"";
			pz.coolTime = L"";
		}
	}
	delete[] l_str;
	return true;
}

int  HandBook::GetPZindex(int x, int y) {
	int index = 0;
	if (y > (31 / 5 + 1)*height * ratio + 100 || x > 5 * width * ratio + 70) {
		
		index = 404;
	}
	else
	{
		int rows = (y - 100) / (height  * ratio);
		int cols = (x - 70) / (int)(width * ratio);
		index = rows * 5 + cols;
		if (index > count) {
			index = 404;
		}
	}
	if (p_return.GetMenuIndex(x, y) >= 0) {
		index = 101;
	}
	if (shut.GetMenuIndex(x, y) >= 0) {
		index =  102;
	}
	return index;
}
void HandBook::PZMouseMove(int x, int y)
{
	lastIndex = m_index;  //记录上一次索引值
	m_index = GetPZindex(x ,y);
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

int HandBook::PZMouseClick(int x, int y)
{
	m_index = GetPZindex(x, y);
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

void HandBook::DrawPlantFrameInfo(HDC hdc,int index)
{

	wstring info = L"";
	wstring name = L"";
	wstring tip = L"";
	wstring sunNum = L"";
	wstring coolTime = L"";
	wstring bigPath = L"";
	int i = 0;
	vector<PZ>::iterator iter;
	for (iter = plants.begin(); iter != plants.end(); iter++)
	{
		if (iter->count == m_index) {
			info = iter->info;
			name = iter->name;
			tip = iter->tip;
			sunNum = iter->sunNum;
			coolTime = iter->coolTime;
			bigPath = iter->bigPath;
			break;
		}
		i++;
	}
	if (bigPath == L"") {
		return;
	}
	info_frame->PaintImage(hdc, WIN_WIDTH * 3 / 5 - 25, (WIN_HEIGHT - info_frame->GetImageHeight()) / 2 + 20,
		info_frame->GetImageWidth(), info_frame->GetImageHeight());
	HBITMAP hbitmp = grass->GetBmpHandle();
	grass->PaintRegion(hbitmp, hdc, WIN_WIDTH * 3 / 5 + 27, (WIN_HEIGHT) / 5 - 16, 20, 20, 200, 145, 1);
	T_Graph* bigPlant = new T_Graph(bigPath);
	bigPlant->PaintImage(hdc,WIN_WIDTH * 3 / 5 + 27 + 50,(WIN_HEIGHT) / 5 + 30);
	RectF nameRect;
	nameRect.Width = name.size() * 40;
	nameRect.Height = 40;
	nameRect.X = WIN_WIDTH * 3 / 5 - 25 +(info_frame->GetImageWidth() - nameRect.Width) / 2;
	nameRect.Y =(WIN_HEIGHT) / 5 + 140;
	
	T_Graph::PaintText(hdc,nameRect,name,20,L"微软雅黑",Color::Color(255, 203, 105),FontStyle::FontStyleRegular,StringAlignmentCenter);
}

void HandBook::DrawZomFrameInfo(HDC hdc, int index)
{
	wstring info = L"";
	wstring name = L"";
	wstring tip = L"";
	wstring sunNum = L"";
	wstring coolTime = L"";
	wstring bigPath = L"";
	int i = 0;
	vector<PZ>::iterator iter;
	for (iter = zombies.begin(); iter != zombies.end(); iter++)
	{
		if (iter->count == m_index) {
			info = iter->info;
			name = iter->name;
			tip = iter->tip;
			sunNum = iter->sunNum;
			coolTime = iter->coolTime;
			bigPath = iter->bigPath;
			break;
		}
		i++;
	}
	if (bigPath == L"") {
		return;
	}
	info_frame->PaintImage(hdc, WIN_WIDTH * 3 / 5 - 25, (WIN_HEIGHT - info_frame->GetImageHeight()) / 2 + 20,
		info_frame->GetImageWidth(), info_frame->GetImageHeight());
	HBITMAP hbitmp = grass->GetBmpHandle();
	grass->PaintRegion(hbitmp, hdc, WIN_WIDTH * 3 / 5 + 27, (WIN_HEIGHT) / 5 - 16, 20, 20, 200, 145, 1);
	T_Graph* bigZom = new T_Graph(bigPath);
	bigZom->PaintImage(hdc, WIN_WIDTH * 3 / 5 + 27 + 50, (WIN_HEIGHT) / 5 + 30);
	RectF nameRect;
	nameRect.X = WIN_WIDTH * 3 / 5 + 27 + 50;
	nameRect.Y = (WIN_HEIGHT) / 5 + 140;
	nameRect.Width = name.size() * 40;
	nameRect.Height = 40;
	T_Graph::PaintText(hdc, nameRect, name, 20, L"微软雅黑", Color::Color(255, 203, 105), FontStyle::FontStyleRegular, StringAlignmentCenter);
}
