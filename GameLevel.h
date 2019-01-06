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
	int x;   //横坐标
	bool state;			//状态 false->已经没有车了
}CAR_INFO;
typedef struct
{
	T_Sprite* sprite;	//植物精灵
	Point position;		//所在行列
	SPRITEINFO info;	//精灵信息
	int pointNum;       //植物的标识
	int life = 200;     //植物被攻击之后，停留的帧数
	bool attacked = false;  //是否被攻击
}PLANT_INFO;

typedef struct
{
	int frame;			//在第几帧出现
	int zombiesindex;	//是第几种僵尸
}ZOMBIES_ARRAY;
typedef struct
{
	int row;			//在第几行
	int x;				//x坐标
	T_Sprite* sprite;	//僵尸精灵
	SPRITEINFO info;     ///精灵信息
	int count;           //僵尸被击中次数
	bool isChanged;         //是否改变图片
	int typeNum; 
	int frame = 110;   //死掉之后存在的帧数
}ZOMBIES_INFO;
typedef struct {
	ZOMBIES_INFO zom_info;
	int paintTimes;
}ZOM_HEADER;
typedef struct
{
	bool hit = false;			//子弹是否已经击中僵尸
	Point position;		//子弹位置，x->x坐标，y->第几行
	int frame = 10;		//子弹击中后播放帧数
}BULLET_INFO;
typedef struct {
	bool isPicked;     ///是否被拾取
	POINT pt;          //位置
}SUN_INFO;
class GameLevel : public T_Scene
{
public:
	static const int MAXPLANTNUM = 2;	//最大植物种类数量
	static const int MAXZOMBIESNUM = 5;	//最大僵尸种类数量
	static const int MAXCARNUM = 1;		//最大推车数量
	static const int CarXSpace = 50;	//推车x边距
	static const int YSpace = 80;		//Y边距
	static const int CarWidth = 75;		//推车宽度
	static const int PlantWidth = 81;	//植物宽度
	static const int PlantHeight = 100;	//植物高度

	static const int MAXROW = 5;		//最多5行
	static const int MAXCOLUMN = 9;		//最多9列
	static const int INDEXROW = 2;		//从第几行开始

	static const int BULLET_LENGTH = 8;	//子弹步长
	static const int CAR_LENGTH = 10;   //小车步长
	static const int BULLETATTACKETIMES = 12;  //子弹打击次数
	static int bodySequ[15];
	int ZOMENTER_MAXFRAME;
	void Init();					//初始化
	void CutsceneInit();			//初始化过场动画
	void PlantInit();				//初始化植物
	void ZombiesInit();				//初始化僵尸
	void ProgressBarInit();			//初始化进度条
	void CardInit();				//初始化植物卡
	void CarInit();					//初始化小推车
	void AudioInit(AudioDX &dx);	//音频初始化
	void BullentInit();				//子弹初始化

	void DrawBullet(HDC hdc);        //绘制子弹
	void DrawPlant(HDC hdc);		//绘制植物
	void DrawZombies(HDC hdc);		//绘制僵尸
	void DrawCutscene(HDC hdc);		//绘制过场动画
	void DrawProgressBar(HDC hdc);	//绘制进度条
	void DrawCard(HDC hdc);			//绘制植物卡
	void DrawCar(HDC hdc);			//绘制小推车
	void DrawSunLight(HDC hdc);		//绘制阳光
	void ProduceSunLight();          //产生随机阳光
	void DrawClickPlant(HDC hdc,int x,int y);
	void Draw(HDC hdc);				//场景绘制

	void Logic();					//逻辑控制
	void CardLogic();				//卡片逻辑
	void carLogic();				//小推车逻辑
	void attackPlantLogic();		//僵尸攻击植物，检测碰撞,造成伤害
	void attackZombieLogic();		//植物攻击僵尸,生成子弹
	void bulletLogic();				//检测碰撞，更新子弹位置，造成伤害


	void MouseClick(int x,int y);		//鼠标响应
	int CardMouseClick(int x, int y);	//鼠标上没有植物按到植物卡
	void PlantMouseClick(int x, int y);	//种植植物
	void sunlightMouseClick(int x, int y);//收集阳光
	void MouseMove(int x,int y);		//鼠标移动事件

	void GameWin();    //赢得游戏
	void GameLose();    //失败

	void TestDraw(HDC hdc);			//测试
	void ClearGameLevel();
private:
	int mousex;
	int mousey;
	wstring levelName;				//关卡名
	T_Graph bg_img;					//背景图片
	T_Graph shadow_img;				//阴影图片
	ZOMBIES_INFO temp_zom;

	//过场动画部分
	bool cutsceneFlag = false;		//过场动画标志
	T_Graph cutscene_img;			//过场动画背景
	T_Graph cutsceneZombies_img[2];	//过场僵尸图片
	int cutsceneZombies_FrameCount = 0;//过场僵尸帧数计数器
	int cutsceneFrame = 250;		//过场动画总帧数
	int moveLength;					//过场动画移动步长

	//游戏部分
	T_Graph Sunlight_img;			//阳光面板图片
	T_Graph Sun;					//阳光图片
	
	bool pointState = false;		//指针状态,false->没有选中植物，true->选中植物但没种下

	Point PlantPosition;			//没种下但选中时植物位置

	vector<PLANT_INFO> plantVector;	//植物容器
	CARD plantCard[MAXPLANTNUM];	//植物卡
	T_Graph* plant[MAXPLANTNUM];	//静态植物图
	T_Sprite* spritePlant[MAXPLANTNUM];//植物精灵图

	vector<ZOMBIES_INFO> zombiesVector;//僵尸容器
	T_Sprite* spriteZombie[MAXZOMBIESNUM];//僵尸精灵图
	vector<ZOMBIES_ARRAY> zombiesArray;   //僵尸数组
	T_Sprite* attackedZombies[5];  //变化僵尸容器
	vector<ZOM_HEADER> zoms_header;
	
	T_Graph * winImage;  //赢得游戏
	T_Graph * loseImage;// 输掉游戏


	vector<SUN_INFO> sunlightVector;		//未收集的阳光
	vector<BULLET_INFO> bulletVector;	//子弹容器
	T_Graph bullet;					//子弹图
	T_Graph bulletHit;				//击中效果
	
	int pointPlant;					//选中的图片序号

	T_Graph progress_bar[5];		//进度条图片0->空进度条，1->满进度条，2->进度条logo，3->僵尸头，4->最后一波
	double progress_bar_length;		//进度条步长

	int sunlight = 0;				//阳光数

	CAR_INFO car[MAXROW];		//小推车
	
	int frameCount = 0;				//帧计数器
	int trueFrame = 0;				//画了多少帧
	int MaxFrameCount = 10000;		//游戏正常结束总帧数,用于计算游戏进度，控制游戏节奏

	AudioDXBuffer bg_buffer;		//背景音乐
	AudioDXBuffer cutscene_buffer;	//过场动画音乐
	AudioDXBuffer car_buffer;        //小车移动
	AudioDXBuffer eatPlant_buffer;   //吃植物的音乐
	AudioDXBuffer click_buffer;  //点击
	AudioDXBuffer bulletZom_buffer;  //子弹攻击植物的
	AudioDXBuffer clickSun_buffer; //点击阳光
	AudioDXBuffer zomEnter_buffer;  //僵尸入场音乐


};