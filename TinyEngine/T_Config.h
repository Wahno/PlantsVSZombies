//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#ifndef TCONFIG_H
#define TCONFIG_H

#include <windows.h>
#include <typeinfo.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
#include <gdiplus.h>
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;


static const int WIN_WIDTH		 = 900;			// 默认游戏窗口宽
static const int WIN_HEIGHT		 = 600;				// 默认游戏窗口高
static const int FRAME_SPEED	 = 100;				// 默认游戏帧频

static const int MENU_WIDTH		 = 200;				// 默认菜单宽
static const int MENU_HEIGHT	 = 60;				// 默认菜单高
static const int MENU_SPACE		 = 10;				// 默认菜单间隔距离
static const int MENU_ALPHA		 = 180;				// 默认菜单背景的透明度
static const COLORREF MENU_BKCLR = RGB(0, 0, 0);	// 默认菜单背景色

static const int LAYER_MAX		= 1000;				// 默认游戏图层最大值

static const LPCTSTR WIN_CLASS	
	= TEXT("TinyEngine");;							// 默认注册的窗口类名
static const LPCTSTR WIN_TITLE						// 默认窗口标题
	= TEXT("TinyEngine Ver 1.0 作者:万立中(C) 2007-2013");

// 游戏方向常量，其值为方向键对应的键值
enum GAME_DIR
{
	DIR_LEFT,					// 左
	DIR_RIGHT,					// 右
	DIR_UP,						// 上
	DIR_DOWN,					// 下
	DIR_LEFT_UP,				// 左上
	DIR_LEFT_DOWN,				// 左下
	DIR_RIGHT_UP,				// 右上
	DIR_RIGHT_DOWN				// 右下
};

// 图像绘制处理常量
enum TRANSFER
{
	TRANS_NONE,					// 原始图像
	TRANS_NOFLIP_ROT90,			// 原始图像顺时针旋转90度
	TRANS_NOFLIP_ROT180,		// 原始图像顺时针旋转180度
	TRANS_NOFLIP_ROT270,		// 原始图像顺时针旋转270度
	TRANS_VFLIP_NOROT,			// 原始图像垂直翻转
	TRANS_VFLIP_ROT90,			// 原始图像垂直翻转并顺时针旋转90度
	TRANS_VFLIP_ROT180,			// 原始图像垂直翻转并顺时针旋转180度
	TRANS_VFLIP_ROT270,			// 原始图像垂直翻转并顺时针旋转27度
	TRANS_HFLIP_NOROT,			// 原始图像水平翻转
	TRANS_HFLIP_ROT90,			// 原始图像水平翻转并顺时针旋转90度
	TRANS_HFLIP_ROT180,			// 原始图像水平翻转并顺时针旋转180度
	TRANS_HFLIP_ROT270			// 原始图像水平翻转并顺时针旋转270度
};

// 游戏状态枚举常量定义
enum GAME_STATE
{
	GAME_START,					// 开始
	GAME_RUN,					// 运行
	GAME_HANDBOOK,				// 图鉴
	GAME_PAUSE,					// 暂停
	GAME_UPGRADE,				// 升级
	GAME_WIN,					// 通关
	GAME_OVER,					// 结束
	GAME_HELP,					// 帮助状态
	GAME_ABOUT,					// 关于状态
	GAME_SETTING,				// 设置状态
}; //0-11
 
// 按键行为常量
enum KM_ACTION
{
	KEY_SYS_NONE,				// 非系统按键处理
	KEY_UP,						// 释放按键
	KEY_DOWN,					// 按下键
	MOUSE_MOVE,					// 鼠标移动
	MOUSE_LCLICK,				// 鼠标左键点击
	MOUSE_RCLICK				// 鼠标右键点击
};

// 图层类型
enum LAYER_TYPE
{
	LAYER_PLY,					// 玩家
	LAYER_NPC,					// NPC
	LAYER_PLY_BOMB,				// 玩家炮弹
	LAYER_NPC_BOMB,				// NPC炮弹
	LAYER_MAP_BACK,				// 地图背景层
	LAYER_MAP_BARR,				// 地图障碍层
	LAYER_MAP_MASK,				// 地图遮罩层
	LAYER_EXPLOSION,			// 爆炸效果图层
	LAYER_TARGET,				// 攻击和保护的目标
	LAYER_BONUS,				// 游戏中的奖励
	LAYER_NONE					// 游戏中非游戏对象
};

// 游戏角色关键信息(每个新增角色必须设置全部值)
typedef struct
{
	int		X;					// 角色初始X坐标
	int		Y;					// 角色初始Y坐标
	int		Dir;				// 角色初始方向(取值为GAME_DIR常量)
	int		Speed;				// 角色初始的移动速度
	int		Level;				// 角色初始的等级
	int		Score;				// 角色角色分值 
	bool	Visible;			// 角色在屏幕上是否可见
	bool	Active;				// 角色的状态（是否移动）
	bool	Dead;				// 角色是否是死亡状态
	BYTE	Alpha;				// 角色透明度
	float	Ratio;				// 动画帧图片放大或缩小比
								// 等于1原始，大于1放大，小于1缩小
	int		Rotation;			// 帧图片是否镜像变换(取值为TRANSFER常量)
}SPRITEINFO;

//地图每个图层信息
typedef struct
{
	int			type_id;			// 图层标识号(取值为LAYER_TYPE常量)
	int			map_cols;			// 地图宽度(图块列数)
	int			map_rows;		// 地图高度(图块行数)
	int			tile_width;		// 图块宽度
	int			tile_height;		// 图块高度
	wstring		tile_path;			// 图块原始图片路径
	int			first_gid;			// 地图数据从0还是1开始
											// Tiled地图编辑软件默认为1
	vector<vector<int>> data;	// 图层数据	
}LAYERINFO;

// 菜单项信息
typedef struct  
{
	POINT pos;
	wstring ItemName;
}MENUITEM;

// 菜单信息
typedef struct  
{
	int		width;				// 菜单宽度
	int		height;				// 菜单高度
	int		space;				// 菜单项之间间隔距离
	int		align;				// 文字对齐方式(0:左对齐; 1:居中; 2:右对齐)
	wstring fontName;			// 字体名称
	bool	isBold;				// 是否粗体
	Color	normalTextColor;	// 正常菜单文字颜色
	Color	focusTextColor;		// 焦点菜单文字颜色
}MENU_INFO;

#endif