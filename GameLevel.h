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
class GameLevel : public T_Scene
{
public:
	void Init();					//初始化
	void AudioInit(AudioDX &dx);	//音频初始化
	void DrawCutscene(HDC hdc);		//绘制过场动画
	void DrawProgressBar(HDC hdc);
	void Draw(HDC hdc);				//场景绘制
private:
	wstring levelName;				//关卡名
	T_Graph bg_img;					//背景图片

	bool cutsceneFlag = false;		//过场动画标志
	T_Graph cutscene_img;			//过场动画背景
	T_Graph cutsceneZombies_img[2];	//过场僵尸图片
	int cutsceneZombies_FrameCount = 0;//过场僵尸帧数计数器
	int cutsceneFrame = 250;		//过场动画总帧数
	int moveLength;					//过场动画移动步长

	//T_Graph Zombies_img;			//僵尸图片

	T_Graph progress_bar[5];		//进度条图片0->空进度条，1->满进度条，2->进度条logo，3->僵尸头，4->最后一波
	double progress_bar_length;		//进度条步长
	
	int frameCount = 0;				//帧计数器
	int MaxFrameCount = 500;		//游戏正常结束总帧数,用于计算游戏进度，控制游戏节奏

	AudioDXBuffer bg_buffer;		//背景音乐
	AudioDXBuffer cutscene_buffer;	//过场动画音乐


};