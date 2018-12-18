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
#include "T_Config.h"
#include "T_Sprite.h"
#include "T_Map.h"

// 记录移动信息的结构体
struct MoveCoord
{
	int oldX;			// 移动前的X坐标
	int oldY;			// 移动前的Y坐标
	int moveX;			// 移动后的X坐标
	int moveY;			// 移动后的Y坐标
	int BoundDir;		// 在边界上的方向
};

class T_AI
{
private:
	int dir_style;		// 方向模式，其值必须是4或8

	// 躲避方向
	// 最高维与GAME_DIR的元素编号一致
	// 第二维表示对应的躲避方向
	static int EvadeDir[8][5];

	// 计算参数sp指定的角色前进方向对应的碰撞检测区域
	// 参数sp：待检测的角色对象
	// 参数spSizeTimes：角色宽高的倍数，决定检测区域的范围
	// 参数testRec：输出型参数，得到最终的检测区域
	void GetHitRect(IN T_Sprite* sp, IN int spSizeTimes, OUT RECT& testRec);

	// 根据移动方向、速度和指定的活动范围计算当前角色的移动位置
	MoveCoord GetMoveCoord(T_Sprite* npc_sp, int dir, int speed, RECT boundary);

public:
	T_AI(int d_style);	// d_style的值必须是4或8
	virtual ~T_AI(void);

	// 根据移动方向、速度和指定的活动范围对角色做漫游处理
	void Wander(T_Sprite* npc_sp, int npc_dir, int speed, RECT boundary);
	// 根据移动方向、速度和指定的地图对象对角色做漫游处理
	void Wander(T_Sprite* npc_sp, int npc_dir, int speed, T_Map* map);
	// 角色躲避处理，第一个参数为躲避的对象，第二个参数为要回避的检测对象
	void Evade(T_Sprite* npc_sp, T_Sprite* player);
	// 角色放重叠处理，第一个参数为检测对象，第二个参数为检测对象所在的角色集合
	void CheckOverlay(T_Sprite* npc_sp, vector<T_Sprite*> vSpriteSet);
};
