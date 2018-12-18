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
#include "T_Layer.h"

class T_Map:public T_Layer
{
protected:
	int tile_width;					// 图块宽
	int tile_height;				// 图块高
	int map_cols;					// 地图图块总列数
	int map_rows;					// 地图图块总行数
	int	first_gid;					// 图块编号从0还是1开始	
	bool updated;					// 地图图层是否更新
	
	T_Graph* graph;					// 保存图块图像或背景图像
	HDC dc_buf;						// 当前图层内存设备
	HBITMAP hbmp_old;				// 替换前的原始位图句柄
	HBITMAP hbmp_layer;				// 当前图层位图句柄
	vector<vector<int>> layer_data;	// 地图图层数据
	
public:
	T_Map(LAYERINFO layerInfo);		//使用地图数据构造
	T_Map(wchar_t* imgFilepath);		//使用背景图片构造
	virtual ~T_Map(void);

	int getTileWidth(){ return tile_width; }		// 获得图块宽
	int getTileHeight(){ return tile_height; }		// 获得图块高
	int getMapCols(){ return map_cols; }			// 获取地图图块总列数
	int getMapRows(){ return map_rows; }			// 获取地图图块总行数
	void setUpdate(bool updt){ updated = updt; }	// 设置图层位图是否更新
	bool getUpdate(){ return updated; }				// 获取图层位图是否更新状态
	virtual string ClassName(){ return "T_Map"; }	// 获取当前类的类名

	void setTile(int col, int row, int tileIndex);	// 修改当前图层指定行、列的元素值
	int getTile(int col, int row);					// 获取当前图层指定行、列的元素值
	void Redraw(HDC hdc);							// 重新绘制当前图层全部图块
	void Draw(HDC hdc);								// 重载父类中的同名函数,处理图层绘制
};