#include "GameLevel2.h"



GameLevel2::GameLevel2()
{
}


GameLevel2::~GameLevel2()
{
}

void GameLevel2::Init()
{
	srand((unsigned int)time(NULL));
	levelName = L"关卡 1 - 2";
	bg_img.LoadImageFile(L"res\\images\\interface\\background1unsodded2.jpg");
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
void GameLevel2::PlantChang()
{
	CherryBomb = new T_Sprite(L"res\\images\\Plants\\Boom.png",213,196);
	WallNutAte = new T_Sprite(L"res\\images\\Plants\\WallNut_crackd2.png",65,73);
}
void GameLevel2::AddZombies() {
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
			zombie_info.row = INDEXROW + rand() % 3;
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
void GameLevel2::PlantInit()
{
	plant[0] = new T_Graph(L"res\\images\\Plants\\SunFlower.png");
	spritePlant[0] = new T_Sprite(L"res\\images\\Plants\\SunFlower_18_1.png", 73, 74);

	plant[1] = new T_Graph(L"res\\images\\Plants\\Peashooter.png");
	spritePlant[1] = new T_Sprite(L"res\\images\\Plants\\Peashooter_13.png", 71, 71);
	
	spritePlant[2] = new T_Sprite(L"res\\images\\Plants\\CherryBomb.png", 112, 81);
	plant[2] = new T_Graph(L"res\\images\\Plants\\CherryBomb_1.png");

	spritePlant[3] = new T_Sprite(L"res\\images\\Plants\\repeater.png", 73, 71);
	plant[3] = new T_Graph(L"res\\images\\Plants\\repeater_1.png");

	spritePlant[4] = new T_Sprite(L"res\\images\\Plants\\WallNut.png", 65, 73);
	plant[4] = new T_Graph(L"res\\images\\Plants\\WallNut_1.png");
	/*spritePlant[5] = new T_Sprite(L"res\\images\\Plants\\Peashooter_13.png", 71, 71);
	plant[6] = new T_Graph(L"res\\images\\Plants\\SunFlower.png");
	spritePlant[6] = new T_Sprite(L"res\\images\\Plants\\SunFlower_18_1.png", 73, 74);
	plant[7] = new T_Graph(L"res\\images\\Plants\\Peashooter.png");
	spritePlant[7] = new T_Sprite(L"res\\images\\Plants\\Peashooter_13.png", 71, 71);*/

}
void GameLevel2::ZomArrayInit()
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

void GameLevel2::BullentInit()
{
	bullet.LoadImageFile(L"res\\images\\Plants\\PeaBullet.png");
	bulletHit.LoadImageFile(L"res\\images\\Plants\\PeaBulletHit.png");
	
}

void GameLevel2::CardInit()
{
	int border = 10;	//边距
	int cardHeight;
	plantCard[0].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\SunFlower.png");
	plantCard[1].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\Peashooter.png");
	plantCard[2].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\CherryBomb.png");
	plantCard[3].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\Repeater.png");
	plantCard[4].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\WallNut.png");
	
	cardHeight = plantCard[0].card->GetImageHeight() / 2 * 0.8;

	CARD_INFO info;
	info.time = 300;
	info.x = border;
	info.y = border;
	//向日葵
	info.sunlight = 50;
	plantCard[0].info = info;
	//豌豆射手
	info.time = 500;
	info.y = border * 2 + cardHeight;
	info.sunlight = 100;
	plantCard[1].info = info;

	//CherryBomb
	info.time = 700;
	info.sunlight = 150;
	info.y = border * 3 + cardHeight * 2;
	plantCard[2].info = info;

	//Reapter
	info.time = 700;
	info.sunlight = 150;
	info.y = border * 4 + cardHeight * 3;
	plantCard[3].info = info;

	//WallNut
	info.time = 300;
	info.sunlight = 50;
	info.y = border * 5 + cardHeight * 4;
	plantCard[4].info = info;



	plantCard[0].nowTime = 0;
	plantCard[1].nowTime = 0;
	plantCard[2].nowTime = 0;
	plantCard[3].nowTime = 0;
	plantCard[4].nowTime = 0;
	
	plantCard[0].state = false;
	plantCard[1].state = false;
	plantCard[2].state = false;
	plantCard[3].state = false;
	plantCard[4].state = false;

}

void GameLevel2::DrawCar(HDC hdc)
{
	for (int i = 1; i < 4; i++)
	{
		if (car[i].car == NULL) {
			continue;
		}
		if (car[i].state == true)
		{
			car[i].car->PaintImage(hdc, CarXSpace, (car[i].row)*PlantHeight + YSpace + 20, car[i].car->GetImageWidth(), car[i].car->GetImageHeight(), 255);
		}
		else
		{
			if (car[i].x <= WIN_WIDTH) {
				car[i].x += CAR_LENGTH;
				car_buffer.Play(false);
				car[i].car->PaintImage(hdc, car[i].x, (car[i].row)*PlantHeight + YSpace + 20, car[i].car->GetImageWidth(), car[i].car->GetImageHeight(), 255);

			}
			else
			{
				car[i].car = NULL;
			}
		}
	}
}
void GameLevel2::DrawCard(HDC hdc)
{
	PAINTREGION_INFO info;
	for (int i = 0; i < MAXPLANTNUM; i++)
	{
		info.destX = plantCard[i].info.x;
		info.destY = plantCard[i].info.y;
		info.srcX = 0;
		info.srcY = plantCard[i].card->GetImageHeight() / 2;
		info.regionWidth = plantCard[i].card->GetImageWidth();
		info.regionHeight = plantCard[i].card->GetImageHeight() / 2;
		plantCard[i].card->PaintRegion(plantCard[i].card->GetBmpHandle(), hdc, info.destX, info.destY, info.srcX, info.srcY, info.regionWidth, info.regionHeight, 0.8);
		info.srcY = 0;
		if (plantCard[i].state == false)
		{
			info.regionHeight = plantCard[i].card->GetImageHeight() / 2 * plantCard[i].nowTime / plantCard[i].info.time;
			if (info.regionHeight < 2)
			{
				info.regionHeight = 2;
			}

			if (plantCard[i].nowTime <= plantCard[i].info.time)
			{
				plantCard[i].nowTime++;
				plantCard[i].card->PaintRegion(plantCard[i].card->GetBmpHandle(), hdc, info.destX, info.destY, info.srcX, info.srcY, info.regionWidth, info.regionHeight, 0.8);
			}
		}
		else
		{
			info.regionHeight = plantCard[i].card->GetImageHeight() / 2;
			plantCard[i].card->PaintRegion(plantCard[i].card->GetBmpHandle(), hdc, info.destX, info.destY, info.srcX, info.srcY, info.regionWidth, info.regionHeight, 0.8);
		}
		RectF infoRec;
		infoRec.X = (float)plantCard[i].info.x;
		infoRec.Y = (float)plantCard[i].info.y + 30;
		infoRec.Width = plantCard[i].card->GetImageWidth() - 20;
		infoRec.Height = 20;
		T_Graph::PaintText(hdc, infoRec, T_Util::int_to_wstring(plantCard[i].info.sunlight), 10, L"黑体", Color::Black, FontStyleBold, StringAlignmentFar);
	}
}
void GameLevel2::DrawBullet(HDC hdc)
{
	vector<BULLET_INFO>::iterator iter;
	for (iter = bulletVector.begin(); iter != bulletVector.end(); iter++)
	{
		if (iter->hit == false)
		{
			if (iter->pointNum == 1) {
				bullet.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight + YSpace + 15, bullet.GetImageWidth(), bullet.GetImageHeight(), 255);
			}
			if (iter->pointNum == 3) {
				bullet.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight + YSpace + 15, bullet.GetImageWidth(), bullet.GetImageHeight(), 255);
				bullet.PaintImage(hdc, iter->position.X + 10, iter->position.Y*PlantHeight + YSpace + 20, bullet.GetImageWidth(), bullet.GetImageHeight(), 255);
			}	
		}
		else
		{
			if (iter->pointNum == 1) {
				bulletHit.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight + YSpace + 15, bulletHit.GetImageWidth(), bulletHit.GetImageHeight(), 255);
			}
			if (iter->pointNum = 3) {
				bulletHit.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight + YSpace + 15, bulletHit.GetImageWidth(), bulletHit.GetImageHeight(), 255);
				bulletHit.PaintImage(hdc, iter->position.X + 10, iter->position.Y*PlantHeight + YSpace + 20, bulletHit.GetImageWidth(), bulletHit.GetImageHeight(), 255);
			}
		}
	}
}
void GameLevel2::Draw(HDC hdc)
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
void GameLevel2::CardLogic()
{
	for (int i = 0; i < MAXPLANTNUM; i++)
	{
		if (plantCard[i].nowTime >= plantCard[i].info.time && sunlight >= plantCard[i].info.sunlight)
		{
			plantCard[i].state = true;
		}
		else
		{
			plantCard[i].state = false;
		}
	}
}

void GameLevel2::Logic()
{
	AddZombies();
	CardLogic();
	bulletLogic();
	attackPlantLogic();
	attackZombieLogic();
	carLogic();
	GameWin();
	GameLose();

}
void GameLevel2::attackZombieLogic()
{
	bool zom[5];

	for (int i = 0; i < 5; i++)
	{
		zom[i] = false;		//先假设所有行都没有僵尸

	}
	for (int i = 0; i < zombiesVector.size(); i++)
	{
		zom[zombiesVector.at(i).row] = true;	//有僵尸置为真

	}
	for (int i = 0; i < plantVector.size(); i++)
	{
		if (plantVector.at(i).pointNum == 1)//豌豆射手
		{
			if (zom[plantVector.at(i).position.Y] == true)//所在行有僵尸
			{
				if (trueFrame % 50 == 0)	//子弹发射间隔
				{
					BULLET_INFO info;
					info.pointNum = 1;
					info.position.X = (plantVector.at(i).position.X + 1) * PlantWidth + CarXSpace + CarWidth;//x坐标
					info.position.Y = plantVector.at(i).position.Y;//第几行
					bulletVector.push_back(info);
				}
			}
		}
		if (plantVector.at(i).pointNum == 3)//另一个射手
		{
			if (zom[plantVector.at(i).position.Y] == true)//所在行有僵尸
			{
				if (trueFrame % 50 == 0)	//子弹发射间隔
				{
					BULLET_INFO info;
					info.pointNum = 3;
					info.position.X = (plantVector.at(i).position.X + 1) * PlantWidth + CarXSpace + CarWidth;//x坐标
					info.position.Y = plantVector.at(i).position.Y;//第几行
					bulletVector.push_back(info);
				}
			}
		}

	}
}
int GameLevel2::CardMouseClick(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	RECT rec;
	for (int i = 0; i < MAXPLANTNUM; i++)
	{
		rec.left = plantCard[i].info.x;
		rec.top = plantCard[i].info.y;
		rec.right = rec.left + plantCard[i].card->GetImageWidth()*0.8;
		rec.bottom = rec.top + plantCard[i].card->GetImageHeight() / 2 * 0.8;
		if (PtInRect(&rec, pt))
		{
			return i;
		}
	}
	return -1;
}

void GameLevel2::MouseClick(int x, int y)
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

void GameLevel2::PlantMouseClick(int x, int y)
{
	if (x < CarXSpace + CarWidth || y < YSpace + PlantHeight*INDEXROW || x > CarXSpace + CarWidth + PlantWidth*MAXCOLUMN || y>PlantHeight*MAXROW + YSpace + PlantHeight*(INDEXROW + 3))
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

void GameLevel2::attackPlantLogic()
{
	int LineZoms[5][MAXZOMBIESNUM] = { WIN_WIDTH + 1 };         //每行的僵尸位置
	int LinePlants[5][9] = { 0 };  //每行的植物
	for (int m = 0; m < 5; m++)
	{
		int n = 0;
		for (int i = 0; i < zombiesVector.size(); i++) {
			if (zombiesVector.at(i).row == m) {
				LineZoms[m][n] = zombiesVector.at(i).x;
				n++;
			}
		}
	}
	for (int m = 0; m < 5; m++)
	{
		int n = 0;
		for (int i = 0; i < plantVector.size(); i++) {
			if (plantVector.at(i).position.Y == m) {
				LinePlants[m][n] = plantVector.at(i).position.X * PlantWidth + CarWidth + CarXSpace + 5;
				n++;
			}
		}
	}
	vector<ZOMBIES_INFO>::iterator it;
	vector<PLANT_INFO>::iterator iter;
	for (int m = 0; m < 5; m++)
	{
		for (int n = 0; n < 9; n++)
		{
			for (int i = 0; i < MAXZOMBIESNUM; i++)
			{
				if (abs(LineZoms[m][i] + 70 - LinePlants[m][n]) <= 30)
				{
					for (it = zombiesVector.begin(); it != zombiesVector.end(); it++)
					{
						if (abs(LineZoms[m][i] - it->x) <= 30)
						{
							it->sprite->SetSpeed(0);
							for (iter = plantVector.begin(); iter != plantVector.end(); iter++)
							{
								if (LinePlants[m][n] == iter->info.X)
								{
									it->sprite->SetSpeed(0);
									if (iter->pointNum == 2 && iter->attacked == false) {
										iter->sprite = CherryBomb;
										iter->sprite->Initiate(iter->info);
										it->info.X = it->sprite->GetX();
										it->info.Y = it->sprite->GetY();
										it->sprite = attackedZombies[5]; //被炸死
										it->sprite->Initiate(it->info);
										it->sprite->SetFrame(0);
										it->isChanged = true;
										it->count = BULLETATTACKETIMES;
										iter->attacked = true;
										break;
									}
									if (iter->pointNum == 4 && iter->attacked == false) {
										iter->info.X = iter->sprite->GetX();
										iter->info.Y = iter->sprite->GetY();
										iter->sprite = WallNutAte;
										iter->sprite->Initiate(iter->info);
									}
									if (it->count >= BULLETATTACKETIMES && iter->attacked == true && it->isChanged == false)
									{
										eatPlant_buffer.Play(false);
										it->info.X = it->sprite->GetX();
										it->info.Y = it->sprite->GetY();
										it->sprite = attackedZombies[2]; //掉头还不忘记吃的僵尸
										it->sprite->Initiate(it->info);
										iter->attacked = false;
									}
									if (iter->attacked == false)
									{
										eatPlant_buffer.Play(false);
										if (it->count < BULLETATTACKETIMES)
										{
											it->info.Speed = 0;
											it->info.X = it->sprite->GetX();
											it->info.Y = it->sprite->GetY();
											it->sprite = attackedZombies[4];
											it->sprite->Initiate(it->info);
										}
										else
										{
											it->info.Speed = 0;
											it->info.X = it->sprite->GetX();
											it->info.Y = it->sprite->GetY();
											it->sprite = attackedZombies[2];
											it->sprite->Initiate(it->info);
										}
										iter->attacked = true;
									}
									iter->life--;
									if (iter->life <= 0)
									{
										eatPlant_buffer.Stop();
										iter = plantVector.erase(iter);
										if (it->count < BULLETATTACKETIMES)
										{
											it->sprite->SetSpeed(3);
											it->info.Speed = 3;
											it->sprite->SetVisible(true);
											it->sprite = spriteZombie[it->typeNum];
											it->sprite->Initiate(it->info);
										}
										if (iter == plantVector.end()) {
											break;
										}
									}
									break;
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}

void GameLevel2::bulletLogic()
{
	vector<BULLET_INFO>::iterator iter;
	int firstzomX[5];
	for (int i = 0; i < 5; i++)
	{
		firstzomX[i] = WIN_WIDTH + 1;	//初始化
	}
	for (int i = 0; i < zombiesVector.size(); i++)
	{
		if (zombiesVector.at(i).x < firstzomX[zombiesVector.at(i).row])
		{
			firstzomX[zombiesVector.at(i).row] = zombiesVector.at(i).x;//遍历出每行第一个僵尸的地址
		}
	}
	for (iter = bulletVector.begin(); iter != bulletVector.end(); iter++)
	{

		if (iter->position.X >= (firstzomX[iter->position.Y] + 60))
		{
			//击中僵尸
			iter->hit = true;
			bulletZom_buffer.Play(false);
		}
		if (iter->hit == false)
		{
			iter->position.X += BULLET_LENGTH;
		}
		else
		{
			iter->frame--;
			if (iter->frame <= 0)
			{
				for (int i = 0; i < zombiesVector.size(); i++)
				{
					if (zombiesVector.at(i).x == firstzomX[iter->position.Y]) //找到该行第一个僵尸
					{
						if (iter->pointNum == 1) {
							zombiesVector.at(i).count++;  //僵尸减血次数加1
						}
						if (iter->pointNum == 3) {
							zombiesVector.at(i).count = zombiesVector.at(i).count + 2;  //僵尸减血次数加2
						}
						break;
					}
				}
				iter = bulletVector.erase(iter);
			}
			/*判断是否越界*/
			if (iter == bulletVector.end()) {
				break;
			}
		}

		if (iter->position.X >= WIN_WIDTH) {
			iter = bulletVector.erase(iter);
			/*判断是否越界*/
			if (iter == bulletVector.end()) {
				break;
			}
		}
	}
}