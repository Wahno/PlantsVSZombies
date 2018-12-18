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
#include "T_Display.h"

class T_Engine
{
public:
	static HWND m_hWnd;					// 窗口句柄
	static HINSTANCE m_hInstance;		// 实例句柄
	static T_Engine* pEngine;			// 本类静态指针(必须指向本类继承类)

protected:
	ULONG_PTR ptrGdiplusToken;			// 对GDI+的引用

	wstring wndClass;					// 窗口类名称
	wstring wndTitle;					// 窗口标题	
	int wndWidth, wndHeight;			// 窗口宽高
	int scrnWidth, scrnHeight;			// 屏幕分辨率宽、高
	WORD wIcon, wSmIcon;				// 程序大图标及小图标
	BOOL m_bFullScreen;					// 是否全屏显示标志;

	RECT m_rcOld;						// 当前窗口尺寸
	LONG style;							// 窗口基本风格
	LONG ex_style;						// 窗口扩展风格
	T_Display* p_disp;					// 定义显示类指针

	int IntervalTime;					// 游戏帧刷新间隔时间
	BOOL isAsleep;						// 窗口是否处于非焦点状态

	HBITMAP bufferBitmap;				// 内存缓冲位图
	HDC bufferDC;						// 内存缓冲设备

	bool keys[256];						// 记录键盘状态的数组
	int GameState;						// 游戏状态(为GAME_STATE常量值)

public:
	// 构造函数
	T_Engine(HINSTANCE hInstance, wstring szWindowClass, wstring szTitle,
		     WORD Icon = NULL, WORD SmIcon = NULL, 
		     int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	// 析构函数
	virtual ~T_Engine();
	// 获取游戏帧刷新间隔时间
	int GetInterval() { return IntervalTime; }
	// 设置游戏帧刷新间隔时间
	void SetFrame(int iTime) { IntervalTime = 1000 / iTime; }
	// 获取窗口是否为焦点状态
	BOOL GetSleep() { return isAsleep; }
	// 设置窗口是否为焦点状态
	void SetSleep(BOOL asleep) { isAsleep = asleep; }
	// 设置窗口是否全屏幕显示
	void SetFullScreen(BOOL isFull){ m_bFullScreen = isFull; }

	// 获取当前的按键状态
	bool CheckKey(WPARAM wParam){ return keys[wParam]; }
	// 附加按键行为处理
	void SubKeyAction(WPARAM wParam);

	// 被系统自动调用的回调函数
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
		                         WPARAM wParam, LPARAM lParam );
	// 初始化处理
	BOOL GameWinInit();
	// 消息处理函数，将被回调函数调用
	LRESULT GameEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// 引擎启动函数
	void StartEngine();

public:
	// 纯函数声明(具体游戏要重载这些函数并增加游戏功能代码)
	// 游戏初始化
	virtual void GameInit()=0;		
	// 游戏逻辑处理
	virtual void GameLogic()=0;		
	// 游戏结束处理
	virtual void GameEnd()=0;
	// 根据GAME_STATE值显示游戏界面
	virtual void GamePaint(HDC hdc)=0;
	// 根据KM_ACTION值处理按键行为
	virtual void GameKeyAction(int ActionType=KEY_SYS_NONE)=0;
	// 根据KM_ACTION值处理鼠标行为
	virtual void GameMouseAction(int x, int y, int ActionType)=0;	
};
