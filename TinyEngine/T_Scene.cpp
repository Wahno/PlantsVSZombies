//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Scene.h"

// 构造函数
T_Scene::T_Scene()
{
	lastSceneX = 0;
	lastSceneY = 0;
	SceneY = 0;
	SceneX = 0;
	SceneWidth = 0;
	SceneHeight = 0;
	WinWidth = 0;
	WinHeight = 0;
	pBarrier = NULL;		//碰撞图层指针
	pMask= NULL;			//遮罩层指针
	LayerChanged = false;
}

// 析构函数
T_Scene::~T_Scene(void)
{
	RemoveAll();
}

// 场景初始化
void T_Scene::InitScene(int scn_x, int scn_y, 
						int scn_width, int scn_height, 
						int win_width, int win_height)
{
	SceneX = scn_x;
	SceneY = scn_y;
	lastSceneX = scn_x;
	lastSceneY = scn_y;
	SceneWidth = scn_width;
	SceneHeight = scn_height;
	WinWidth = win_width;
	WinHeight = win_height;
}

// 场景定位函数
void T_Scene::SetScenePos(int x, int y)
{
	lastSceneX = SceneX;
	lastSceneY = SceneY;

	SceneX = x;
	SceneY = y;
}

// 场景移动处理函数
void T_Scene::MoveScene(int speedX, int speedY)
{	
	lastSceneX = SceneX;
	lastSceneY = SceneY;

	int nextStepX, nextStepY; 
	nextStepX = SceneX + speedX;
	nextStepY = SceneY + speedY;

	if(nextStepX >= 0) 
		speedX = 0 - SceneX;
	if(nextStepX <= (WinWidth-SceneWidth)) 
		speedX = (WinWidth-SceneWidth) - SceneX;

	if(nextStepY >= 0) 
		speedY = 0 - SceneY;
	if(nextStepY <= (WinHeight-SceneHeight)) 
		speedY = (WinHeight-SceneHeight) - SceneY;

	SceneX += speedX;
	SceneY += speedY;
}

void T_Scene::ScrollScene(T_Sprite* player)
{
	bool scn_scrolling = false;
	int speedX=0, speedY=0;
	switch(player->GetDir())
	{
	case DIR_LEFT:
		speedX = player->GetSpeed();
		speedY = 0;
		// 如果角色在离窗口左边缘五分之一以外区域，场景不滚动
		if (player->GetX() > (WinWidth/5) ) 
		{
			scn_scrolling = false;
		}
		else// 在离窗口左边缘五分之一以内区域，场景需要滚动
		{
			scn_scrolling = true;
		}
		break;
	case DIR_RIGHT:
		speedX = -player->GetSpeed();
		speedY = 0;
		// 如果角色在离窗口右边缘五分之一以外区域，场景不滚动
		if (player->GetX() < (WinWidth*4/5)-player->GetRatioSize().cx) 
		{
			scn_scrolling = false;
		}
		else// 在离窗口右边缘五分之一以内区域，场景需要滚动
		{
			scn_scrolling = true;
		}
		break;
	case DIR_UP:
		speedX = 0;
		speedY = player->GetSpeed();

		// 如果角色在离窗口上边缘五分之一以外区域，场景不滚动
		if (player->GetY() > (WinHeight/5)) 
		{
			scn_scrolling = false;
		}
		else // 在离窗口上边缘五分之一以内区域，场景需要滚动
		{
			scn_scrolling = true;
		}
		break;
	case DIR_DOWN:
		speedX = 0;
		speedY =  -player->GetSpeed();
		// 如果角色在离窗口下边缘五分之一以外区域，场景不滚动
		if (player->GetY() < (WinHeight*4/5)-player->GetRatioSize().cy) 
		{
			scn_scrolling = false;
		}
		else// 在离窗口下边缘五分之一以内区域，场景需要滚动
		{
			scn_scrolling = true;
		}
		break;
	case DIR_LEFT_UP:
		// 如果角色在离窗口左边缘和上边缘五分之一以外区域，场景不滚动
		if (player->GetX() > (WinWidth/5)  &&  player->GetY() > (WinHeight/5)) 
		{
			scn_scrolling = false;
		}
		// 在离窗口左边缘和上边缘五分之一以内区域，场景需要滚动
		if (player->GetX() <= (WinWidth/5) &&  player->GetY() <= (WinHeight/5)) 
		{
			// 计算角色左上角的坐标
			POINT spPT = {player->GetX(), player->GetY()};
			// 计算场景左上角的坐标
			POINT scenePT = {SceneX, SceneY};
			// 根据角色移动的速度，计算从spPT至scenePT之间，
			// 场景进行斜角移动时，X、Y方向的分量步长
			// speedX和speedY为最终计算结果
			T_Util::GetBevelSpeed(spPT, scenePT, player->GetSpeed(), speedX, speedY);
			speedX = -speedX;
			speedY = -speedY;
			scn_scrolling = true;
		}
		break;
	case DIR_LEFT_DOWN:
		// 如果角色在离窗口左边缘和下边缘五分之一以外区域，场景不滚动
		if ((player->GetX() > (WinWidth/5)) &&  
			(player->GetY() < ((WinHeight*4/5)-player->GetRatioSize().cy)))
		{
			scn_scrolling = false;
		}
		//在离窗口左边缘和下边缘五分之一以内区域，场景需要滚动
		if ((player->GetX() <= (WinWidth/5)) &&  
			(player->GetY() >= ((WinHeight*4/5)-player->GetRatioSize().cy)))
		{
			// 计算角色左下角的坐标
			POINT spPT = {player->GetX(), player->GetY()+player->GetRatioSize().cy};
			// 计算场景左下角的坐标
			POINT scenePT = {SceneX, SceneY+SceneHeight};
			// 根据角色移动的速度，计算从spPT至scenePT之间，
			// 场景进行斜角移动时，X、Y方向的分量步长
			// speedX和speedY为最终计算结果
			T_Util::GetBevelSpeed(spPT, scenePT, player->GetSpeed(), speedX, speedY);
			speedX = -speedX;
			speedY = -speedY;
			scn_scrolling = true;
		}
		break;
	case DIR_RIGHT_UP:
		// 如果角色在离窗口右边缘和上边缘五分之一以外区域，场景不滚动
		if ((player->GetX() < (WinWidth*4/5)-player->GetRatioSize().cx) &&  
			(player->GetY() > (WinHeight/5)))
		{
			scn_scrolling = false;
		}
		//在离窗口右边缘和上边缘五分之一以内区域，场景需要滚动
		if ((player->GetX() >= (WinWidth*4/5)-player->GetRatioSize().cx) &&  
			(player->GetY() <= (WinHeight/5)))
		{
			// 计算角色右上角的坐标
			POINT spPT = {player->GetX()+player->GetRatioSize().cx, player->GetY()};
			// 计算场景右上角的坐标
			POINT scenePT = {SceneX+SceneWidth, SceneY};
			// 根据角色移动的速度，计算从spPT至scenePT之间，
			// 场景进行斜角移动时，X、Y方向的分量步长
			// speedX和speedY为最终计算结果
			T_Util::GetBevelSpeed(spPT, scenePT, player->GetSpeed(), speedX, speedY);
			speedX = -speedX;
			speedY = -speedY;
			scn_scrolling = true;
		}
		break;
	case DIR_RIGHT_DOWN:
		// 如果角色在离窗口右边缘和下边缘五分之一以外区域，场景不滚动
		if ((player->GetX() < (WinWidth*4/5)-player->GetRatioSize().cx) &&  
			(player->GetY() < (WinHeight*4/5)-player->GetRatioSize().cy))
		{
			scn_scrolling = false;
		}
		//在离窗口右边缘和下边缘五分之一以内区域，场景需要滚动
		if ((player->GetX() >= (WinWidth*4/5)-player->GetRatioSize().cx) &&  
			(player->GetY() >= (WinHeight*4/5)-player->GetRatioSize().cy))
		{
			// 计算角色右下角的坐标
			POINT spPT = {player->GetX()+player->GetRatioSize().cx, 
				          player->GetY()+player->GetRatioSize().cy};
			// 计算场景右下角的坐标
			POINT scenePT = {SceneX+SceneWidth, SceneY+SceneHeight};
			// 根据角色移动的速度，计算从spPT至scenePT之间，
			// 场景进行斜角移动时，X、Y方向的分量步长
			// speedX和speedY为最终计算结果
			T_Util::GetBevelSpeed(spPT, scenePT, player->GetSpeed(), speedX, speedY);
			speedX = -speedX;
			speedY = -speedY;
			scn_scrolling = true;
		}
		break;
	}
	//如果地图可以滚动，滚动地图
	if (scn_scrolling == true) 
	{
		MoveScene((int)speedX, (int)speedY);
	}
}


// 添加图层
void T_Scene::Append(GAMELAYER gm_layer)
{
	sceneLayers.push_back(gm_layer);
	LayerChanged = true;
}

// 在指定的图层索引号前插入图层
void T_Scene::Insert(GAMELAYER gm_layer, int index)
{
	int p_index = 0;
	SCENE_LAYERS::iterator p;
	for (p = sceneLayers.begin(); p != sceneLayers.end(); p++) 
	{
		if(p_index == index)
		{
			sceneLayers.insert(p, gm_layer);
			break;
		}
		p_index++;
	}
}

// 删除指定图层
void T_Scene::Remove(GAMELAYER gm_layer)
{
	SCENE_LAYERS::iterator p;
	for (p = sceneLayers.begin(); p != sceneLayers.end(); p++) 
	{
		if((*p).layer == gm_layer.layer)
		{
			sceneLayers.erase(p);
			break;
		}
	}
}

// 删除全部图层
void T_Scene::RemoveAll()
{	
	//清除图层数据
	SCENE_LAYERS::iterator vp = sceneLayers.begin();
	for (; vp != sceneLayers.end();) 
	{
		if(vp->layer)
		{
			delete vp->layer;
			vp->layer = NULL;
			vp = sceneLayers.erase(vp);
		}
		
		
	}
	sceneLayers.clear();
	//使用swap,清除元素并回收内存
	//清除容器并最小化它的容量
	vector<GAMELAYER> emptyVec;
	sceneLayers.swap(emptyVec) ;
}

// 图层排序比较函数（该函数必须为静态函数）
bool T_Scene::SortByZorder(const GAMELAYER &l1, const GAMELAYER &l2)
{
	return l1.z_order < l2.z_order;//升序排列
}

// 根据图层索引号对图层进行排序
void T_Scene::SortLayers()
{
	sort(sceneLayers.begin(),sceneLayers.end(),SortByZorder);  
	LayerChanged = false;
}

// 得到地图上非障碍的随机位置
POINT T_Scene::getRandomFreeCell()
{
	POINT cellPos = {0, 0};

	int row = 0, col = 0;

	do 
	{
		row = rand()%(pBarrier->getMapRows()-1);
		col = rand()%(pBarrier->getMapCols()-1);
		if(row==0) row = 1;
		if(col==0) col = 1;

		bool isFree = true;

		for(int r=row-1; r<=row+1; r++)
		{
			for(int c=col-1; c<=col+1; c++)
			{
				if(pBarrier->getTile(c, r)!=0 ||
					pMask->getTile(c, r)!=0)
				{
					isFree = false;
					break;
				}
			}
			if(isFree == false)
			{
				break;
			}
		}

		if(isFree == true)
		{
			break;
		}
	}while(1);

	cellPos.x = (col-1)*pBarrier->getTileWidth();
	cellPos.y = (row-1)*pBarrier->getTileHeight();

	cellPos.x = SceneX + cellPos.x;
	cellPos.y = SceneY + cellPos.y;

	return cellPos;
}

// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
// 如果存在，解析关键字后的值并转换成整型，通过第三个参数输出
void T_Scene::GetTxtMapValue(wstring str, wstring keywords, int& value)
{
	int pos;
	pos = (int)(str.find(keywords));
	if(pos !=-1)
	{
		pos= (int)(str.find(L"="));
		value = _wtoi(str.substr(pos+1, wcslen(str.c_str())).c_str());
	}
}

// 解析第一个参数指定的字符串中是否存在第二个参数指定的关键字
// 如果存在，解析关键字后的值并转换成字符串，通过第三个参数输出
void T_Scene::GetTxtMapValue(wstring str, wstring keywords, wstring& value)
{
	int pos;
	pos = (int)(str.find(keywords));
	if(pos !=-1)
	{
		pos= (int)(str.find(L"="));
		value = str.substr(pos+1, wcslen(str.c_str())).c_str();
		pos= (int)(value.find(L">"));
		if(pos !=-1)
		{
			value = value.substr(0, pos);
		}
	}
}

// 解析第一个参数指定的CSV格式的地图数据字符串
// 将解析后的地图数据保存到第二个参数的data元素中
void T_Scene::parseCsvData(wstring csv_data, LAYERINFO& m_LayerInfo)
{
	wstring data = csv_data;

	vector<int> layerDataRow( m_LayerInfo.map_cols );
	int m_LayerRow = 0;
	int m_LayerCol = 0;

	for (int i = 0; i < m_LayerInfo.map_rows; i++)
	{
		m_LayerInfo.data.push_back( layerDataRow );
	}

	int pos =0;
	while(pos !=-1 && m_LayerRow<m_LayerInfo.map_rows)
	{
		pos= (int)(data.find(','));
		int gid = _wtoi(data.substr(0,pos).c_str());
		data = data.substr(pos+1, data.size());

		m_LayerInfo.data[m_LayerRow][m_LayerCol] = gid;

		m_LayerCol++;
		if(m_LayerCol == m_LayerInfo.map_cols)
		{
			m_LayerCol = 0;
			m_LayerRow++;
		}
	}
}

// 加载参数指定的地图文件，解析其中的地图数据，并保存到场景图层中
bool T_Scene::LoadTxtMap(const char* txtmap_path)
{
	//***************************************************************************
	//txt纯文本地图格式：
	//map_width=50					//等号后为地图图块列数
	//map_height=50					//等号后为地图图块行数
	//tile_width=32					//等号后为地图图块宽度
	//tile_height=32				//等号后为地图图块高度
	//tile_path=map\Forest.png		//等号后为地图图块图像文件路径
	//tile_grid_id=1				//等号后为地图图块编号起始号
	//back_layer_name=background	//等号后为地图背景图层名称
	//barrier_layer_name=obstacle	//等号后为地图障碍检测图层名称
	//mask_layer_name=mask			//等号后为地图遮罩图层名称
	//<layer name=background>		//<layer>标记,后面为地图数据,name为图层名称
	//两个<layer>标记之间粘贴csv格式一维地图数组
	//</layer>						//地图数据结束的标记
	//......						//继续仿照以上格式使用<layer>标记添加其它图层
	//***************************************************************************
	
	string str;
	wifstream infile(txtmap_path,ios::in);

	if(!infile)
	{
		return false;
	}

	wchar_t* l_str = new wchar_t[1024];
	wstring line_str;
	wstring mapdata= L"";
	bool startReadMapData=false;
	int layerCount=0;
	wstring barrierName = L"";
	wstring maskName = L"";
	wstring bkgName = L"";
	wstring currentlayerName = L"";

	LAYERINFO layerInfo;
	GAMELAYER mapLayer;

	while(!infile.eof())
	{
		infile.getline(l_str, 1024);//按行读取,读取结果存入l_str
		line_str = wstring(l_str);

		//以下判断读取的每行数据中是否含有要查找的关键字, 然后解析出对应的数据
		GetTxtMapValue(line_str, L"map_cols", layerInfo.map_cols);
		GetTxtMapValue(line_str, L"map_rows", layerInfo.map_rows);
		GetTxtMapValue(line_str, L"tile_width", layerInfo.tile_width);
		GetTxtMapValue(line_str, L"tile_height", layerInfo.tile_height);
		GetTxtMapValue(line_str, L"tile_path", layerInfo.tile_path);
		GetTxtMapValue(line_str, L"tile_grid_id", layerInfo.first_gid);
		GetTxtMapValue(line_str, L"back_layer_name", bkgName);
		GetTxtMapValue(line_str, L"barrier_layer_name", barrierName);
		GetTxtMapValue(line_str, L"mask_layer_name", maskName);
		
		// 查找是否有layer标记, 并获取对应的图层名称
		if(line_str.find(L"<layer")!=-1)
		{
			GetTxtMapValue(line_str, L"name", currentlayerName);

			//检查">"后是否有数据
			int pos = (int)(line_str.find(L">"));
			if(pos>0 && pos < (int)(line_str.length()-1))
			{
				line_str = line_str.substr(pos+1, line_str.length());
				mapdata = mapdata+line_str;
			}
			startReadMapData = true;
			continue;
		}
		// 解析地图图层数据
		if(startReadMapData == true)
		{
			// 如果没有到结束的</layer>标记, 不断将图层数据添加在字符串中
			if(line_str.find(L"</layer>") == -1)
			{
				mapdata = mapdata+line_str;
			}
			// 如果到达结束的</layer>标记
			if(line_str.find(L"</layer>") != -1)
			{
				startReadMapData = false;
				// 解析出字符串中的图层数据
				parseCsvData(mapdata, layerInfo);
				// 用图层数据构造T_Map对象
				mapLayer.layer = new T_Map(layerInfo);
				// 判断当前图层是否为背景图层
				if( currentlayerName == bkgName && 
					currentlayerName != L"" && bkgName!= L"")
				{
					mapLayer.layer->SetLayerTypeID(LAYER_MAP_BACK);
					mapLayer.type_id = LAYER_MAP_BACK;
					layerInfo.type_id = LAYER_MAP_BACK;
				}
				// 判断当前图层是否为障碍图层
				if(currentlayerName == barrierName && 
				   currentlayerName != L"" && barrierName!= L"")
				{
					pBarrier = (T_Map*)mapLayer.layer;//指定碰撞图层
					mapLayer.layer->SetLayerTypeID(LAYER_MAP_BARR);
					mapLayer.type_id = LAYER_MAP_BARR;
					layerInfo.type_id = LAYER_MAP_BARR;
					
				}
	
				//如果为遮罩层,则z_order为LAYER_MAX
				if(currentlayerName == maskName && 
				   currentlayerName != L"" && maskName!= L"")
				{
					mapLayer.z_order = LAYER_MAX;
					mapLayer.layer->setZorder(LAYER_MAX);
					pMask = (T_Map*)mapLayer.layer;//指定遮罩图层
					mapLayer.layer->SetLayerTypeID(LAYER_MAP_MASK);
					mapLayer.type_id = LAYER_MAP_MASK;
					layerInfo.type_id = LAYER_MAP_MASK;
				}
				else
				{
					mapLayer.z_order = layerCount;
					mapLayer.layer->setZorder(layerCount);
				}
				// 将图层对象添加到图层容器中
				sceneLayers.push_back(mapLayer);
				
				mapdata = L"";
				layerInfo.data.clear();
				layerInfo.type_id = -1;
				layerCount = layerCount + 1;
			}
		}
	}
	delete[] l_str;
	return true;
}

// 整个游戏场景的绘制
void T_Scene::Draw(HDC hdc, int x, int y)
{	
	// 计算场景当前坐标与场景上一次坐标的差值
	int offsetX =0;
	int offsetY =0;
	offsetX = (abs(lastSceneX) - abs(SceneX));
	offsetY = (abs(lastSceneY) - abs(SceneY));
	// 如果图层发生过任何变化
	if(LayerChanged == true)
	{
		SortLayers();//对图层重新排序
	}
		
	int pX, pY;
	// 遍历全部图层
	SCENE_LAYERS::iterator p;
	for (p = sceneLayers.begin(); p != sceneLayers.end(); p++) 
	{
		// 计算每个图层要平移的步长
		pX = (*p).layer->GetX();
		pX += offsetX;
		pY = (*p).layer->GetY();
		pY += offsetY;
		(*p).layer->SetPosition(pX, pY);
		// 如果图层可见,将其绘制出来
		if((*p).layer->IsVisible() == true)
		{
			(*p).layer->Draw(hdc);//调用图层自己的绘制方法
		}
	}

	//将数据复位
	lastSceneX = SceneX;
	lastSceneY = SceneY;
}