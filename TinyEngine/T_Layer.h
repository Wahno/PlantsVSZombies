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

class T_Layer
{
public:
	T_Layer(){};
	virtual ~T_Layer(void){};

protected:
	int Width, Height;	// 图层的宽、高
	int X, Y;			// 图层的X、Y坐标
	bool Visible;		// 图层是否可见
	int LayerTypeID;	// 图层的标识（取值为LAYER_TYPE常量）
	int zorder;			// 图层的绘制顺序

public:
	// 设置和获取图层的宽、高
	void SetWidth(int width){ Width = width; }
	int GetWidth(){ return Width; }
	void SetHeight(int height){ Height = height; }
	int GetHeight(){ return Height; }
	
	// 设置和获取图层的X、Y坐标
	void SetPosition(int x, int y){ X = x; Y = y; }
	int GetX(){ return X; }
	int GetY(){ return Y; }
	
	// 设置和获取图层可见性
	void SetVisible(bool visible){ Visible = visible; }
	bool IsVisible(){ return Visible; }
	
	// 设置和获取图层的标识（取值为LAYER_TYPE常量）
	void SetLayerTypeID(int i){ LayerTypeID = i; }
	int GetLayerTypeID(){ return LayerTypeID; }
	
	// 设置和获取图层的绘制顺序
	int getZorder(){ return zorder; }
	void setZorder(int z){ zorder = z; }
	
	// 图层移动
	//dx_speed: 正值向右移动， 负值向左移动
	//dy_speed: 正值向下移动， 负值向上移动
	void Move(int dx_speed, int dy_speed){ X += dx_speed; Y += dy_speed;}

	// 获取本类及派生类的类名
	virtual string ClassName(){ return "T_Layer"; }
	
	// 纯虚函数，由派生类具体实现
	virtual void Draw(HDC hdc)=0;
};