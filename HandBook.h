#pragma once
#include "TinyEngine\T_Graph.h"
#include "TinyEngine\T_Menu.h"
#include"TinyEngine\T_Engine.h"
#include "BookMenu.h"
#include"GraphPlus.h"
#include <codecvt>
typedef struct {
	int count; //顺序号
	wstring tip; //使用小技巧
	wstring sunNum; //所需金币数
	wstring coolTime; //冷却时间
	wstring name; //名称
	wstring info; //详细信息描述
	wstring bigPath; //大图像的地址
	wstring smallPath; //小图像地址
}PZ;
enum HANDBOOK {
	BOOK_ZOM,  //僵尸图鉴
	BOOK_SUN,  //植物图鉴
};  //0 -1
class HandBook : public BookMenu
{
public:
	HandBook();
	~HandBook();
private:
	T_Graph *back; //背景
	T_Menu  *button; //僵尸按钮
	T_Graph *zombie; //僵尸
	T_Graph *sunflower; //植物
	BookMenu zom; //查看僵尸
	BookMenu sun; //查看植物
	BookMenu r_button; //返回按钮
	BookMenu shut; //关闭
	BookMenu p_return; //返回按钮
	T_Graph *sun_back;  //植物信息页面背景
	T_Graph *zomb_back;  //僵尸信息页面背景
	T_Graph *info_frame;  //详细信息框
	T_Graph * grass;
	vector<PZ> plants;   //植物容器
	vector<PZ> zombies;   //僵尸容器
	float ratio;
	int count;
	int width;
	int height;
	wstring smallPath;
	wstring bigPath;
public:
	int HandBookState;  //图鉴内部状态变化
	
public:
	void Init(); //初始化资源
	int GetMenuIndex(int x, int y); /*获得菜单项索引*/
	void Draw(HDC hdc);

	//void GameMouseAction(int x, int y, int ActionType);
	int MenuMouseClick(int x, int y);
	void MenuMouseMove(int x, int y);

	void DrawSunInfo(HDC hdc);
	void DrawZomInfo(HDC hdc);
	void GetTxtMapValue(wstring str, wstring keywords, wstring & value);
	void GetTxtMapValue(wstring str, wstring keywords, int & value);
	void DrawPlants(HDC hdc);
	void DrawZombies(HDC hdc);
	bool LoadTxt(const char * filepath, vector<PZ>& pz);

	int GetPZindex(int x, int y); //获得索引

	void  PZMouseMove(int x, int y);  //鼠标移动
	int PZMouseClick(int x,int y); //鼠标点击

	void DrawPlantFrameInfo(HDC hdc, int index);

	void DrawZomFrameInfo(HDC hdc,int index);

	

};

