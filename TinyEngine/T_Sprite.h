//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include "T_Graph.h"
#include "T_Map.h"
#include "T_Layer.h"
#include "T_Util.h"

#define ROUND(x) (int)(x+0.5)	//定义四舍五入的宏

class T_Sprite:public T_Layer
{
protected:	
	//……………………………………………………………………………………
	// 与角色图像相关的属性
	//……………………………………………………………………………………

	T_Graph	spImg;					// 原始角色图片
	T_Graph	spOldImg;				// 修改前角色图片
	int		frameCols;				// 原始帧图片总列数
	int		frameRows;				// 原始帧图片总行数
	int		rawFrames;				// 原始帧图片总帧数
	int		totalFrames;			// 当前帧图片总帧数
	int		forward;				// 从前往后播放帧计数
	int		backward;				// 从后往前播放帧计数
	bool	loopForward;			// 是否从前往后播放帧
	int*	frameSequence;			// 自定义动画帧序列
	float	frameRatio;				// 帧图片放大或缩小比（1是原始，大于1放大，小于1缩小）
	int		frameRotate;			// 帧图片旋转或翻转方式(取值为TRANSFER常量值)
	BYTE	frameAlpha;				// 帧图片透明度(255不透明, 0完全透明)

	//……………………………………………………………………………………
	// 与角色状态相关的属性
	//……………………………………………………………………………………

	int		dir;					// 初始方向
	int		lastDir;				// 上次方向
	bool	active;					// 是否可活动
	bool	dead;					// 是否死亡
	int		speed;					// 初始移动速度
	int		level;					// 初始游戏等级
	int		score;					// 游戏分值

	DWORD	startTime;				// 计时开始时间
	DWORD	endTime;				// 计时结束时间

	//……………………………………………………………………………………
	// 与碰撞检测相关的属性
	//……………………………………………………………………………………

	RECT	colideRect;				// 碰撞检测矩形区域
	int		colideWidth;			// 碰撞区域宽度
	int		colideHeight;			// 碰撞区域高度
	POINT	mapBlockPT;				// 碰撞到障碍时的位置

public:
	//……………………………………………………………………………………
	// 构造函数、析构函数及类名获取函数
	//……………………………………………………………………………………

	// 构造函数参数说明:
	// frameWidth和frameHeight值都为0: 角色图像无动画
	// frameWidth和frameHeight值都大于0: 角色图像包含帧动画
	T_Sprite(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	// 析构函数
	virtual ~T_Sprite(void);
	// 获取本类名
	virtual string ClassName(){ return "T_Sprite"; }	

	//……………………………………………………………………………………
	// 与图像相关的操作
	//……………………………………………………………………………………

	T_Graph* GetImage(){ return &spImg; }				// 获得本类T_Graph对象
	void SetImage(T_Graph* pImg){ spImg = *pImg; }		// 设置本类T_Graph对象
	void ResetImage(){ spImg = spOldImg; }				// 恢复本类T_Graph对象

	float GetRatio(){ return frameRatio; }				// 获得缩放比
	void SetRatio(float rat){ frameRatio = rat; }		// 设置缩放比
	// 根据缩放比计算帧图片宽、高
	SIZE GetRatioSize()									
	{ 
		SIZE ratioFrameSize;
		ratioFrameSize.cx = ROUND(frameRatio*Width);
		ratioFrameSize.cy = ROUND(frameRatio*Height); 
		return ratioFrameSize;
	}

	int GetRotation(){ return frameRotate; }			// 获得图像转换方式
	void SetRotation(int rot){ frameRotate = rot; }		// 设置图像转换方式(rot为TRANSFER常量值)

	BYTE GetAlpha(){ return frameAlpha; }				// 获得透明度值
	void SetAlpha(BYTE a){ frameAlpha = a; }			// 设置透明度值

	//……………………………………………………………………………………
	// 与状态相关的操作
	//……………………………………………………………………………………

	int GetDir(){ return dir; }							// 获得方向值			
	void SetDir(int d){ dir = d; }						// 设置方向值

	bool IsActive(){ return active; }					// 是否可活动
	void SetActive(bool act){ active = act; }			// 设置是否可活动

	bool IsDead(){ return dead; }						// 死亡状态
	void SetDead(bool dd){ dead = dd; }					// 设置死亡状态

	int GetSpeed(){ return speed; }						// 获得速度值
	void SetSpeed(int spd){ speed = spd; }				// 设置速度值

	int GetLevel(){ return level; }						// 获得等级值
	void SetLevel(int lvl){ level = lvl; }				// 设置等级值

	int GetScore(){ return score; }						// 获得分值
	void SetScore(int scr){ score = scr; }				// 设置分值

	//……………………………………………………………………………………
	// 与计时相关的操作
	//……………………………………………………………………………………

	void SetEndTime(DWORD time){ endTime = time; }		// 设置计时结束时间
	DWORD GetEndTime(){ return endTime; }				// 获得计时结束时间
	void SetStartTime(DWORD time){ startTime = time; }	// 设置计时开始时间
	DWORD GetStartTime(){ return startTime; }			// 获得计时开始时间

	//……………………………………………………………………………………
	// 与碰撞相关的操作
	//……………………………………………………………………………………

	// 计算扩大或收缩后的碰撞检测区宽高(px、py为正值放大、负值缩小，单位为像素)
	void AdjustCollideRect(int px=0, int py=0);	
	// 获得缩放后的实际碰撞检测矩形区域
	RECT* GetCollideRect();	
	// 检测角色碰撞, distance检测碰撞的距离
	bool CollideWith(T_Sprite* target, int distance=0);
	// 检测地图碰撞
	bool CollideWith(IN T_Map* map);	
	// 获取碰撞到障碍时的位置
	POINT GetMapBlockPT(){ return mapBlockPT; }				

	//……………………………………………………………………………………
	// 与动画帧相关的操作
	//……………………………………………………………………………………

	// 往前或往后循环播放所有帧
	void LoopFrame(bool ahead = true);
	// 往前或往后循环播放一轮所有帧
	bool LoopFrameOnce(bool ahead = true);				
	// 获取原始帧的长度
	int GetRawFrames(){ return rawFrames; }	
	// 计算帧序列数组长度
	int GetTotalFrames(){ return totalFrames; }			

	// 获取当前帧序列号
	int GetFrame(bool ahead = true)						
	{ 
		if(ahead == true)
			return forward;
		else
			return backward;
	}

	// 设置当前帧序列号
	void SetFrame(int sequenceIndex, bool ahead = true)	
	{ 
		if(ahead == true)
			forward = sequenceIndex;
		else
			backward = sequenceIndex;
	}

	// 设置新的帧序列
	void SetSequence(int* sequence, int length)			
	{ 
		frameSequence = sequence; 
		totalFrames = length;
	}

	//……………………………………………………………………………………
	// 与鼠标相关的操作
	//……………………………………………………………………………………

	// 根据鼠标判断方向
	int GetDir(POINT mousePT);							
	// 检查角色是否到达鼠标处
	bool MoveTo(IN POINT mousePT, IN POINT desPT, IN RECT Boundary);
	// 检查角色是否到达地图鼠标处
	bool MoveTo(IN POINT mousePT, IN POINT desPT, IN T_Map* map);	

	//……………………………………………………………………………………
	// 本类初始化及绘制函数
	//……………………………………………………………………………………

	// 初始化本类对象
	void Initiate(SPRITEINFO spInfo);
	// 本类对象绘制
	void Draw(HDC hdc);	

};

// 计算扩大或收缩后的碰撞检测区宽高(px、py为正值放大、负值缩小，单位为像素)
inline void T_Sprite::AdjustCollideRect(int px, int py)
{
	if(px == 0 && py == 0)  
	{
		return;
	}
	else
	{
		RECT tempRec={0, 0, colideWidth, colideHeight};
		InflateRect(&tempRec, px, py); //收缩或扩大矩形区域
		colideWidth = tempRec.right-tempRec.left;
		colideHeight = tempRec.bottom - tempRec.top;
	}
} 

// 获得缩放后的实际碰撞检测矩形区域
inline RECT* T_Sprite::GetCollideRect()
{
	int c_left, c_top;
	if(frameRatio>0) 
	{
		c_left = (GetRatioSize().cx-colideWidth)/2;
		c_top = (GetRatioSize().cy-colideHeight)/2;
	}
	else
	{
		c_left = ((int)GetWidth()-colideWidth)/2;
		c_top = ((int)GetHeight()-colideHeight)/2;
	}

	colideRect.left = (LONG)X+c_left;
	colideRect.right = colideRect.left + colideWidth;
	colideRect.top = (LONG)Y+c_top;
	colideRect.bottom = colideRect.top + colideHeight;
	return &colideRect;
}

// 检测本角色对象是否与目标角色碰撞(distance参数为检测距离)
inline bool T_Sprite::CollideWith(T_Sprite* target, int distance)
{
	//计算参与碰撞检测的角色矩形区域
	RECT targetRect = *(target->GetCollideRect());
	RECT hitRec;
	hitRec.left =targetRect.left-distance;
	hitRec.top = targetRect.top-distance;
	hitRec.right = targetRect.right+distance;
	hitRec.bottom = targetRect.bottom+distance;
	RECT thisRect = *(this->GetCollideRect());
	int cw = abs(thisRect.right - thisRect.left);
	int tw = abs(hitRec.right - hitRec.left);
	int ch = abs(thisRect.bottom - thisRect.top);
	int th = abs(hitRec.bottom - hitRec.top);

	//方式一：同时满足4个条件
	return thisRect.left <= hitRec.right &&
		   hitRec.left <= thisRect.right &&
		   thisRect.top <= hitRec.bottom &&
		   hitRec.top <= thisRect.bottom;

	//方式二：同时满足2个条件
	//return (abs((thisRect.left + cw/2)-(hitRec.left + tw/2))<(cw+tw)/2) &&
	//       (abs((thisRect.top + ch/2)-(hitRec.top + th/2))<(ch+th)/2);
}