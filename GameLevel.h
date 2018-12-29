#pragma once
#include "TinyEngine\\T_Scene.h"
#include "TinyEngine\\T_Audio.h"

typedef struct
{
	int destX;			//绘制目标X			
	int destY;			//绘制目标Y
	int srcX;			//绘制源图片X
	int srcY;			//绘制源图片Y
	int regionWidth;	//绘制矩形宽
	int regionHeight;	//绘制矩形高
	float ratio;		//缩放比例
	int rotType;
	BYTE alpha;
}PAINTREGION_INFO;
typedef struct
{
	int x;				//绘制目标x坐标
	int y;				//绘制目标y坐标
	int time;			//冷却时间,按帧率计时
	int sunlight;		//种植所需阳光
}CARD_INFO;
typedef struct
{
	T_Graph* card;		//图片
	CARD_INFO info;		
	int nowTime;		//现在冷却了多久
	bool state;			//状态
}CARD;
typedef struct
{
	T_Graph* car;
	int row;			//第几行
	bool state;			//状态 false->已经没有车了
}CAR_INFO;
typedef struct
{
	T_Sprite* sprite;	//植物精灵
	Point position;		//所在行列
}PLANT_INFO;
class GameLevel : public T_Scene
{
public:
	void Init();					//初始化
	void CutsceneInit();			//初始化过场动画
	void PlantInit();
	void ProgressBarInit();			//初始化进度条
	void CardInit();				//初始化植物卡
	void CarInit();					//初始化小推车
	void AudioInit(AudioDX &dx);	//音频初始化

	void DrawCutscene(HDC hdc);		//绘制过场动画
	void DrawProgressBar(HDC hdc);	//绘制进度条
	void DrawCard(HDC hdc);			//绘制植物卡
	void DrawCar(HDC hdc);			//绘制小推车
	void DrawClickPlant(HDC hdc,int x,int y);
	void Draw(HDC hdc);				//场景绘制

	void Logic();					//逻辑控制
	void CardLogic();				//卡片逻辑

	void MouseClick(int x,int y);		//鼠标响应
	int CardMouseClick(int x, int y);	//鼠标上没有植物按到植物卡
	void PlantMouseClick(int x, int y);	//种植植物
	void MouseMove(int x,int y);

	void TestDraw(HDC hdc);			//测试
private:
	int mousex;
	int mousey;
	wstring levelName;				//关卡名
	T_Graph bg_img;					//背景图片
	T_Graph shadow_img;				//阴影图片

	//过场动画部分
	bool cutsceneFlag = false;		//过场动画标志
	T_Graph cutscene_img;			//过场动画背景
	T_Graph cutsceneZombies_img[2];	//过场僵尸图片
	int cutsceneZombies_FrameCount = 0;//过场僵尸帧数计数器
	int cutsceneFrame = 250;		//过场动画总帧数
	int moveLength;					//过场动画移动步长

	//游戏部分
	//T_Graph Zombies_img;				//僵尸图片
	static const int MAXPLANTNUM = 2;	//最大植物种类数量
	static const int MAXCARNUM = 1;		//最大推车数量
	static const int CarXSpace = 50;	//推车x边距
	static const int YSpace = 80;		//Y边距
	static const int CarWidth = 75;		//推车宽度
	static const int PlantWidth = 81;	//植物宽度
	static const int PlantHeight = 100;	//植物高度

	static const int MAXROW = 1;		//最多5行
	static const int MAXCOLUMN = 9;		//最多9列
	bool pointState = false;		//指针状态,false->没有选中植物，true->选中植物但没种下

	Point PlantPosition;			//没种下但选中时植物位置

	vector<PLANT_INFO> plantvector;	//植物容器
	CARD plantCard[MAXPLANTNUM];	//植物卡
	T_Graph* plant[MAXPLANTNUM];	//静态植物图路径
	T_Graph* spritePlant[MAXPLANTNUM];//植物精灵图路径
	int pointPlant;					//选中的图片序号

	T_Graph progress_bar[5];		//进度条图片0->空进度条，1->满进度条，2->进度条logo，3->僵尸头，4->最后一波
	double progress_bar_length;		//进度条步长

	int sunlight = 0;				//阳光数

	CAR_INFO car[MAXCARNUM];		//小推车
	
	int frameCount = 0;				//帧计数器
	int MaxFrameCount = 10000;		//游戏正常结束总帧数,用于计算游戏进度，控制游戏节奏

	AudioDXBuffer bg_buffer;		//背景音乐
	AudioDXBuffer cutscene_buffer;	//过场动画音乐


};