//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Sprite.h"

T_Sprite::T_Sprite(wstring imgPath, int frameWidth, int frameHeight)
{
	if(wcslen(imgPath.c_str())>0)
	{
		spImg.LoadImageFile(imgPath);
		spOldImg = spImg;
	}
	else
	{
		throw L"图像路径为空!";
	}
	
	// 无动画的角色图片
	if(frameWidth==0 && frameHeight==0)
	{
		SetWidth(spImg.GetImageWidth());
		SetHeight(spImg.GetImageHeight());

		totalFrames = rawFrames = 0; // 动画总帧数
	}
	else// 具有动画的角色图片
	{
		SetWidth(frameWidth);
		SetHeight(frameHeight);

		frameCols = spImg.GetImageWidth()/frameWidth;		// 动画帧图片总列数
		frameRows = spImg.GetImageHeight()/frameHeight;	// 动画帧图片总行数
		totalFrames = frameCols*frameRows;					// 动画总帧数
		rawFrames = frameCols*frameRows;					// 记录原始动画总帧数
		forward = 0;									// 当前帧计数初始化
		backward = totalFrames-1;
	}
	

	frameSequence = NULL;
	loopForward = true;

	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
}

T_Sprite::~T_Sprite(void)
{
}

void T_Sprite::Initiate(SPRITEINFO spInfo)
{								
	SetPosition(spInfo.X, spInfo.Y);	// 角色坐标
	Visible = spInfo.Visible;			// 角色是否可见
	dir = spInfo.Dir;					// 角色方向
	active = spInfo.Active;				// 角色状态（是否移动）
	speed = spInfo.Speed;				// 角色移动速度
	dead = spInfo.Dead;					// 角色死亡状态
	level = spInfo.Level;				// 角色等级
	score = spInfo.Score;				// 角色角色分值 
	frameRatio = spInfo.Ratio;			// 帧图片缩放比(等于1原始，大于1放大，小于1缩小)
	frameRotate = spInfo.Rotation;		// 帧图片是否旋转变换(TRANSFER值之一)
	frameAlpha = spInfo.Alpha;			// 帧图片透明度
	if(frameRatio>0) 
	{
		colideWidth = GetRatioSize().cx;
		colideHeight = GetRatioSize().cy;
	}
	else
	{
		colideWidth = (int)GetWidth();
		colideHeight =  (int)GetHeight();
	}
}

//往前或往后循环播放所有帧
void T_Sprite::LoopFrame(bool ahead)
{	
	loopForward = ahead;
	if(totalFrames>0)
	{
		if(ahead == true)
		{
			forward = forward + 1;
			if(forward > totalFrames-1) 
			{
				forward = 0; 
			}
		}
		else
		{
			backward = backward - 1;
			if(backward < 0) 
			{
				backward = totalFrames-1;
			}
		}
	}
}

bool T_Sprite::LoopFrameOnce(bool ahead)
{
	loopForward = ahead;
	if(totalFrames<=0) return true;
	if(totalFrames>0)
	{
		if(ahead == true)
		{
			forward = forward + 1;
			if(forward > totalFrames-1) 
			{
				forward = 0; 
				return true;//播放完一轮所有帧
			}
			else
			{
				return false;
			}
		}
		if(ahead == false)
		{
			backward = backward - 1;
			if(backward < 0) 
			{
				backward = totalFrames-1;
				return true;//播放完一轮所有帧
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void T_Sprite::Draw(HDC hdc)
{
	int frmIndex = 0;
	if(frameSequence != NULL && backward>=0 && forward>=0)
	{
		if(loopForward == false)
			frmIndex = frameSequence[backward];
		else
			frmIndex = frameSequence[forward];
	}
	else
	{
		if(loopForward == false)
			frmIndex = backward;
		else
			frmIndex = forward;
	}

	if(&spImg != NULL)
	{
		if(Visible == true)
		{
			if(totalFrames==0)
			{
				spImg.PaintRegion(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y, 
					0, 0, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
			else
			{
				spImg.PaintFrame(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y, frmIndex,  
					frameCols, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
		}
	}
}

bool T_Sprite::MoveTo(IN POINT mousePT, IN POINT desPT, IN RECT Boundary)
{
	//使用鼠标更新角色位置
	//
	//检测是否到达目的地，使用的关键函数是PtInRect
	//根据角色当前位置建立一个矩形区域，检测该活动区域是否包含鼠标点
	//注意，该区域不能太小，否则会造成颤动
	//以指定点(desPT)往外5个像素为检测区比较合适
	//如果该活动区域包含鼠标点的位置，则表示角色已经移到了目的地
	//如果到达目的地，则角色停在检测区内
	//
	int  xRatio, yRatio; 
	if(active == true)
	{
		SIZE ratioFrameSize = GetRatioSize();	//计算缩放后的帧图尺寸
		RECT HotRect;//检测用的矩形区域(指定点往外5个像素为检测区)
		HotRect.left = (long)(desPT.x-5);
		HotRect.top = (long)(desPT.y-5);
		HotRect.right = (long)(desPT.x+5);
		HotRect.bottom = (long)(desPT.y+5);

		// 据mousePT和desPT计算角色以speed速度移动时的X和Y方向的移动速度
		T_Util::GetBevelSpeed(desPT, mousePT, speed, xRatio, yRatio);

		BOOL ToDesPos = PtInRect(&HotRect, mousePT);

		if(ToDesPos == TRUE)
		{
			return true;
		}
		if(ToDesPos == FALSE)
		{		
			// 下一步X和Y方向的移动速度
			int nextStepX = (int)xRatio;
			int nextStepY = (int)yRatio;
			
			// 获取下一步移动
			POINT nextPT = {(long)(GetX()+nextStepX), (long)(GetY()+nextStepY)};

			// 判断下一步是否如果到达边界，如果是则停在边界位置
			if(nextPT.x <=Boundary.left) 
				nextStepX = Boundary.left - (int)GetX();
			if((nextPT.x+ratioFrameSize.cx) >=Boundary.right) 
				nextStepX = Boundary.right - ratioFrameSize.cx - (int)GetX();
			if(nextPT.y <=Boundary.top) 
				nextStepY = Boundary.top - (int)GetY();
			if((nextPT.y+ratioFrameSize.cy) >=Boundary.bottom) 
				nextStepY = Boundary.bottom - ratioFrameSize.cy - (int)GetY();
			
			// 根据计算的移动结果移动角色的位置
			Move(nextStepX, nextStepY);	

			return false;
		}
	}
	return true;
}

bool T_Sprite::MoveTo(IN POINT mousePT, IN POINT desPT, IN T_Map* map)
{
	//检测是否到达目的地，使用的关键函数是PtInRect
	//根据角色当前位置建立一个矩形区域，检测该活动区域是否包含鼠标点
	//注意，该区域不能太小，否则会造成颤动
	//以指定点(desPT)往外5个像素为检测区比较合适
	//如果该活动区域包含鼠标点的位置，则表示角色已经移到了目的地
	//如果到达目的地，则角色停在检测区内
	int  xRatio, yRatio; 
	if(active == true)
	{
		// 计算缩放后的帧图尺寸
		SIZE ratioFrameSize = GetRatioSize();
		// 检测用的矩形区域(指定点往外5个像素为检测区)
		RECT HotRect;
		HotRect.left = (long)(desPT.x-5);
		HotRect.top = (long)(desPT.y-5);
		HotRect.right = (long)(desPT.x+5);
		HotRect.bottom = (long)(desPT.y+5);

		// 据mousePT和desPT计算角色以speed速度移动时的X和Y方向的移动速度
		T_Util::GetBevelSpeed(desPT, mousePT, speed, xRatio, yRatio);
		// 判断鼠标点是否在检测区
		BOOL ToDesPos = PtInRect(&HotRect, mousePT);
		// 如果在检测区表示角色已经到达目的地
		if(ToDesPos == TRUE)
		{
			return true;
		}
		// 角色没有到达目的地
		if(ToDesPos == FALSE)
		{		
			// 下一步X和Y方向的移动速度
			int nextStepX = (int)xRatio;
			int nextStepY = (int)yRatio;
			int x =0;
			int y = 0;
			// 如果没有和地图障碍物碰撞，则继续移动
			if(!CollideWith(map)) 
			{
				x = GetX();
				y = GetY();
				Move(nextStepX, nextStepY);	
			}
			// 如果和地图障碍物碰撞，则定位在碰撞前的位置
			if(CollideWith(map))
			{
				SetPosition(x, y);
			}

			return false;
		}
	}
	return true;
}

//根据鼠标判断方向
int T_Sprite::GetDir(POINT mousePT)
{
	int dir = -1;
	POINT spNowXY = {(long)GetX(),(long)GetY()};

	//计算缩放后的帧图尺寸
	SIZE ratioFrameSize = GetRatioSize();
	
	//按照角色矩形区建立参考矩形区域
	//作为参照的矩形区域（根据角色当前坐标计算获得）
	RECT SpriteRect;
	SpriteRect.left = (long)GetX();
	SpriteRect.top = (long)GetY();
	SpriteRect.right = (long)(GetX() + ratioFrameSize.cx);
	SpriteRect.bottom = (long)(GetY() + ratioFrameSize.cy);

	//判断朝向的情况
	if( mousePT.x <= SpriteRect.left && 
		mousePT.y >= SpriteRect.top && 
		mousePT.y <= SpriteRect.bottom)
	{
		dir = DIR_LEFT;
	}
	else if(mousePT.x >= SpriteRect.right && 
		mousePT.y >= SpriteRect.top && mousePT.y <= SpriteRect.bottom)
	{
		dir = DIR_RIGHT;
	}
	else if(mousePT.y <= (SpriteRect.bottom-ratioFrameSize.cy/2) &&
		mousePT.x > SpriteRect.left && mousePT.x < SpriteRect.right)
	{
		dir = DIR_UP;
	}
	else if(mousePT.y > (SpriteRect.bottom-ratioFrameSize.cy/2) &&
		mousePT.x > SpriteRect.left && mousePT.x < SpriteRect.right)
	{
		dir = DIR_DOWN;
	}
	else if(mousePT.x < SpriteRect.left && mousePT.y < SpriteRect.top)
	{
		dir = DIR_LEFT_UP;
	}
	else if(mousePT.x < SpriteRect.left && mousePT.y > SpriteRect.bottom)
	{
		dir = DIR_LEFT_DOWN;
	}
	else if(mousePT.x > SpriteRect.right && mousePT.y < SpriteRect.top)
	{
		dir = DIR_RIGHT_UP;
	}
	else if(mousePT.x > SpriteRect.right && mousePT.y > SpriteRect.bottom)
	{
		dir = DIR_RIGHT_DOWN;
	}
	else
	{
		dir = -1;			
	}
	return dir;
}

// 检测地图碰撞
bool T_Sprite::CollideWith(IN T_Map* map)
{
	// 如果背景为图片则不检测地图碰撞
	if(map->getMapRows() == 0 && map->getMapCols() == 0)
	{
		mapBlockPT.x = -1;
		mapBlockPT.y = -1;
		return false;
	}

	// 如果地图不可见或角色不可见不检测地图碰撞
	if ((!(map->IsVisible())) || (!(this->IsVisible()))) 
	{
		mapBlockPT.x = -1;
		mapBlockPT.y = -1;
		return false;
	}

	// 计算当前地图图层的矩形范围
	int mapLeft = map->GetX();
	int mapTop =  map->GetY();
	int mapRight = mapLeft+map->GetWidth();
	int mapBottom = mapTop+map->GetHeight();

	// 获得地图图层中使用的图块的宽高
	int tW = map->getTileWidth();
	int tH = map->getTileHeight();

	// 计算当前角色的矩形范围
	int spLeft = this->GetCollideRect()->left;
	int spTop = this->GetCollideRect()->top;
	int spRight =this->GetCollideRect()->right;
	int spBottom = this->GetCollideRect()->bottom;

	// 获得当前地图中图块的总列数
	int tNumCols = map->getMapCols();
	// 获得当前地图中图块的总行数
	int tNumRows = map->getMapRows();

	// 计算当前角色的实际的宽高
	int spW = spRight-spLeft;
	int spH = spBottom-spTop;

	RECT lprcDst;
	// 根据以上计算的图层的矩形范围和角色的矩形范围构造两个矩形对象
	RECT mapRect={mapLeft, mapTop, mapRight, mapBottom};
	RECT spRect={spLeft, spTop, spRight, spBottom};
	// 如果两个矩形对象没有发生任何碰撞，则退出函数
	if ((IntersectRect(&lprcDst, &mapRect, &spRect))==FALSE)
	{
		mapBlockPT.x = -1;
		mapBlockPT.y = -1;
		return false;
	}

	// 如果两个矩形对象发生了碰撞，首先计算角色矩形上、下、左、右的矩形区域
	int startRow = (spTop <= mapTop) ? 0 : (spTop - mapTop) / tH;
	int endRow = (spBottom < mapBottom) ? (spBottom - 1 - mapTop) / tH : tNumRows - 1;
	int startCol = (spLeft <= mapLeft) ? 0 : (spLeft - mapLeft) / tW;
	int endCol = (spRight < mapRight) ? (spRight - 1 - mapLeft) / tW : tNumCols - 1;

	// 根据角色矩形上、下、左、右的矩形区域判断哪个矩形区域为障碍
	for (int row = startRow; row <= endRow; ++row) 
	{
		for (int col = startCol; col <= endCol; ++col) 
		{
			// 如果当前矩形所在的图块在地图数据中为非0，就表示是障碍
			if (map->getTile(col, row) != 0) 
			{
				mapBlockPT.x = col;	// 记录当前障碍图块的列
				mapBlockPT.y = row;	// 记录当前障碍图块的行

				// 根据角色当前的方向计算碰撞前的位置
				int x=GetX(), y = GetY();
				switch(GetDir())
				{
				case DIR_LEFT:
					x = GetX() + GetSpeed();
					y = GetY();
					break;
				case DIR_RIGHT:
					x = GetX() - GetSpeed();
					y = GetY();
					break;
				case DIR_UP:
					x = GetX();
					y = GetY() + GetSpeed();
					break;
				case DIR_DOWN:
					x = GetX();
					y = GetY() - GetSpeed();
					break;
				}
				// 将角色定位在撞前的位置
				SetPosition(x, y);
				return true;
			}
		}
	}
	return false;
}