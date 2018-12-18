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
#include "T_Map.h"
#include "T_Layer.h"
#include "T_Sprite.h"

typedef struct
{
	int z_order;	// 图层序号(序号越小图层离观众越近)
	int type_id;	// LAYER_TYPE常量值的图层类型标识号
	T_Layer* layer;	// 地图图层图像	
}GAMELAYER;

// 游戏中的图层容器类型
typedef vector<GAMELAYER> SCENE_LAYERS;

class T_Scene
{
protected:

	SCENE_LAYERS sceneLayers;		// 保存游戏中全部图层的vector容器
	T_Map* pBarrier;				// 碰撞图层指针
	T_Map* pMask;					// 遮罩层指针

	int SceneWidth, SceneHeight;	// 整个场景的宽、高
	int WinWidth, WinHeight;		// 窗口的宽、高
	int lastSceneX, lastSceneY;		// 场景上一次的坐标位置
	int SceneX, SceneY;				// 场景当前的坐标位置
	bool LayerChanged;				// 图层是否发生变化

	//图层排序比较函数（该函数必须为静态函数）
	static bool SortByZorder(const GAMELAYER &l1, const GAMELAYER &l2);
	
public:
	T_Scene();
	virtual ~T_Scene(void);
	
	//……………………………………………………………………………………
	// 获取本类数据成员值的函数
	//……………………………………………………………………………………
	// 获取场景当前X坐标
	int getSceneX(){ return SceneX; }
	// 获取场景当前Y坐标
	int getSceneY(){ return SceneY; }
	// 获取场景上一次X坐标
	int getlastSceneX(){ return lastSceneX; }
	// 获取场景上一次Y坐标
	int getlastSceneY(){ return lastSceneY; }
	// 获取场景中地图障碍图层
	T_Map* getBarrier(){ return pBarrier; }
	// 获取场景中地图遮罩图层
	T_Map* getMask(){ return pMask; }
	// 场景中图层总数
	int GetTotalLayers(){ return (int)(sceneLayers.size()); }
	// 获取场景图层容器对象
	SCENE_LAYERS* getSceneLayers(){ return &sceneLayers; }	
	
	//……………………………………………………………………………………
	// 与场景操作相关的函数
	//……………………………………………………………………………………
	// 场景初始化
	void InitScene(int scn_x, int scn_y, 
		           int scn_width, int scn_height, 
		           int win_width, int win_height);
	// 设置场景左上角坐标
	void SetScenePos(int x, int y);
	// 将场景当前坐标按照参数指定的步长移动
	void MoveScene(int speedX, int speedY);
	// 根据参数指定的角色对象判断场景是否需要滚动
	void ScrollScene(T_Sprite* player);
		
	//……………………………………………………………………………………
	// 与图层操作相关的函数
	//……………………………………………………………………………………
	// 添加图层
	void Append(GAMELAYER gm_layer);
	// 在指定的图层索引号前插入图层
	void Insert(GAMELAYER gm_layer, int index);
	// 删除指定图层
	void Remove(GAMELAYER gm_layer);
	// 删除全部图层
	void RemoveAll();
	// 根据图层索引号对图层进行排序
	void SortLayers();
	// 得到地图上非障碍的随机位置
	POINT getRandomFreeCell();

	//……………………………………………………………………………………
	// 与地图文件解析有关的函数
	//……………………………………………………………………………………
	// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
	// 如果存在，解析关键字后的值并转换成整型，通过第三个参数输出
	void GetTxtMapValue(wstring str, wstring keywords, int& value);
	// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
	// 如果存在，解析关键字后的值并转换成字符串，通过第三个参数输出
	void GetTxtMapValue(wstring str, wstring keywords, wstring& value);
	// 解析第一个参数指定的CSV格式的地图数据字符串
	// 将解析后的地图数据保存到第二个参数的data元素中
	void parseCsvData(wstring csv_data, LAYERINFO& m_LayerInfo);
	// 加载参数指定的地图文件，解析其中的地图数据，并保存到场景图层中
	bool LoadTxtMap(const char* txtmap_path);
	
	//……………………………………………………………………………………
	// 负责整个场景绘制的函数
	//……………………………………………………………………………………
	void Draw(HDC hdc, int x, int y);

};

