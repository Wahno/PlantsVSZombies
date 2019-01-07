#pragma once
#include"TinyEngine\\T_Graph.h"
typedef struct {
	POINT pt;
	T_Graph buttonImg;
	wstring name;
}BUTTON;
class GameLevelMenu 
{
public:
	GameLevelMenu();
	~GameLevelMenu();
	void InitButtton();  //按钮初始化
	void Draw(HDC hdc);  
	int MouseClick(int x , int y); //计算鼠标点击的按钮
private:
	BUTTON pauseButton;  //占停按钮
	BUTTON returnMainButtton;  //返回主菜单按钮
	int buttonWidth;
	int buttonHeight; //按钮宽高
	int XSpace;  //距边框距离
	int buttonSpace;  //按钮间距
	int YSpace;
};

