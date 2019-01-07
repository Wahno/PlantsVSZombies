#include "GameLevel3.h"



GameLevel3::GameLevel3()
{
}


GameLevel3::~GameLevel3()
{
}

void GameLevel3::Init()
{
	srand((unsigned int)time(NULL));
	levelName = L"关卡 1 - 2";
	bg_img.LoadImageFile(L"res\\images\\interface\\background1.jpg");
	shadow_img.LoadImageFile(L"res\\images\\interface\\plantshadow32.png");
	Sunlight_img.LoadImageFile(L"res\\images\\interface\\SunBack.png");
	Sun.LoadImageFile(L"res\\images\\interface\\Sun.gif");
	InitScene(0, 0, bg_img.GetImageWidth(), bg_img.GetImageHeight(), WIN_WIDTH, WIN_HEIGHT);
	winImage.LoadImageFile(L"res\\images\\interface\\trophy.png");
	loseImage.LoadImageFile(L"res\\images\\interface\\ZombiesWon.png");
	gameFlag = 1; // 游戏运行中
	sunlight = 300;	//初始阳光值
					//植物
	PlantInit();
	BullentInit();
	PlantChang();
	ZomArrayInit();
	//过场动画
	CutsceneInit();
	//植物卡
	CardInit();
	//小推车
	CarInit();
	//僵尸
	ZombiesInit();
	//进度条
	ProgressBarInit();

}

//void GameLevel3::AddZombies()
//{
//}

void GameLevel3::ZomArrayInit()
{
	ZOMBIES_ARRAY zombies_array;
	zombies_array.zombiesindex = 0;
	zombies_array.frame = 1000;
	zombiesArray.push_back(zombies_array);
	for (int i = 1; i < MAXZOMBIESNUM / 3; i++) {
		zombies_array.zombiesindex = i % MAXZOMBIEARRAYSUN;
		zombies_array.frame = 1000 + (2 * i + 1) * 300;
		zombiesArray.push_back(zombies_array);
	}
	for (int i = MAXZOMBIESNUM / 3; i < MAXZOMBIESNUM * 2 / 3; i++)
	{
		zombies_array.zombiesindex = i % MAXZOMBIEARRAYSUN;
		zombies_array.frame = 1000 + (2 * MAXZOMBIESNUM / 3 + 1) * 300 + (i - MAXZOMBIESNUM / 3) * 500;
		zombiesArray.push_back(zombies_array);
	}
	for (int i = MAXZOMBIESNUM * 2 / 3; i < MAXZOMBIESNUM; i++)
	{
		zombies_array.zombiesindex = i % MAXZOMBIEARRAYSUN;
		zombies_array.frame = 1000 + (2 * MAXZOMBIESNUM / 3 + 1) * 300 + (MAXZOMBIESNUM / 3) * 500 + 600 + i * 150;
		zombiesArray.push_back(zombies_array);
	}
	ZOMENTER_MAXFRAME = zombiesArray.at(MAXZOMBIESNUM - 1).frame;
}
void GameLevel3::AddZombies() {
	SPRITEINFO info;
	info.Active = true;
	info.Dead = false;
	info.Dir = DIR_LEFT;
	info.Alpha = 255;
	info.Score = 0;
	info.Visible = true;
	info.Level = 1;
	info.Ratio = 1;
	info.Rotation = TRANS_NONE;
	info.Speed = 4;
	ZOMBIES_INFO zombie_info;
	/*判断当前帧是否需要新加入僵尸*/
	for (int i = 0; i < zombiesArray.size(); i++)
	{
		if (frameCount == zombiesArray.at(i).frame) {
			zombie_info.sprite = spriteZombie[zombiesArray.at(i).zombiesindex];
			zombie_info.row = INDEXROW + rand() % 4;
			zombie_info.x = WIN_WIDTH;  //僵尸横坐标
			zombie_info.count = 0;
			zombie_info.isChanged = false;
			zombie_info.typeNum = zombiesArray.at(i).zombiesindex;
			info.X = zombie_info.x;
			info.Y = (zombie_info.row) * PlantHeight + 10; //僵尸纵坐标
			zombie_info.info = info;
			zombie_info.frame = 110;
			zombiesVector.push_back(zombie_info);
			zombiesVector.back().sprite->Initiate(info);
			zomEnter_buffer.Play(false);
		}
	}
}
void GameLevel3::Draw(HDC hdc)
{
	trueFrame++;
	if (frameCount < MaxFrameCount - 1)
	{
		frameCount++;
	}
	if (cutsceneFlag)
	{
		DrawCutscene(hdc);
	}
	else
	{
		//画背景
		bg_img.PaintRegion(bg_img.GetBmpHandle(), hdc, 0, 0, 120, 0, WinWidth, WinHeight, 1);
		//小推车
		DrawCar(hdc);
		//画植物
		DrawPlant(hdc);
		//画僵尸
		DrawZombies(hdc);
		//画子弹
		DrawBullet(hdc);
		//画植物卡
		DrawCard(hdc);
		if (pointState)
		{
			//画点击后的植物图
			DrawClickPlant(hdc, mousex, mousey);
		}
		//画阳光面板
		DrawSunLight(hdc);
		//画进度条
		DrawProgressBar(hdc);
		if (gameFlag == 2) {
			winImage.PaintImage(hdc, (WIN_WIDTH - winImage.GetImageWidth()) / 2, (WIN_HEIGHT - winImage.GetImageHeight()) / 2, winImage.GetImageWidth(), winImage.GetImageHeight(), 255);
		}
		if (gameFlag == 0)
		{
			loseImage.PaintImage(hdc, (WIN_WIDTH - loseImage.GetImageWidth()) / 2, (WIN_HEIGHT - loseImage.GetImageHeight()) / 2, loseImage.GetImageWidth(), loseImage.GetImageHeight(), 255);
		}
	}
}
void GameLevel3::MouseClick(int x, int y)
{
	if (!pointState)
	{
		int card = CardMouseClick(x, y);
		if (card != -1 && plantCard[card].state == true && sunlight >= plantCard[card].info.sunlight)
		{
			pointState = true;
			pointPlant = card;

		}
	}
	else
	{
		PlantMouseClick(x, y);
		pointState = false;
	}
	sunlightMouseClick(x, y);
}

void GameLevel3::PlantMouseClick(int x, int y)
{
	if (x < CarXSpace + CarWidth || y < YSpace + PlantHeight*INDEXROW || x > CarXSpace + CarWidth + PlantWidth*MAXCOLUMN || y>PlantHeight*MAXROW + YSpace + PlantHeight*(INDEXROW + 4))
	{
		return;
	}
	PLANT_INFO tempPlant;
	x = x - CarXSpace - CarWidth;
	y = y - YSpace;
	tempPlant.position.X = x / PlantWidth;
	tempPlant.position.Y = y / PlantHeight;
	for (int i = 0; i < plantVector.size(); i++)
	{
		if (plantVector.at(i).position.X == tempPlant.position.X&&plantVector.at(i).position.Y == tempPlant.position.Y)
		{
			return;
		}
	}
	click_buffer.Play(false);
	tempPlant.sprite = spritePlant[pointPlant];
	tempPlant.pointNum = pointPlant;
	SPRITEINFO info;
	info.Active = true;
	info.Dead = false;
	info.Dir = DIR_RIGHT;
	info.Rotation = TRANS_NONE;
	info.Ratio = 1.0f;
	info.Level = 0;
	info.Score = 0;
	info.Speed = 0;
	info.X = tempPlant.position.X*PlantWidth + CarXSpace + CarWidth + 5;
	info.Y = tempPlant.position.Y*PlantHeight + YSpace + 10;
	info.Alpha = 255;
	info.Visible = true;

	tempPlant.info = info;
	tempPlant.life = 50;
	tempPlant.attacked = false;
	plantVector.push_back(tempPlant);
	sunlight = sunlight - plantCard[pointPlant].info.sunlight;
	plantCard[pointPlant].nowTime = 0;
}