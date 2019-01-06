#include "GameLevel.h"
int GameLevel::bodySequ[15] = { 0,0,0,0,1,1,2,3,4,5,6,7,8,9,10 };
//int GameLevel::headerSequ[20] = { 0,1,1,2,3,4,5,6,7,8,9,10,11,10,11,11,11,10,11,10};
void GameLevel::Init()
{
	levelName = L"关卡 1 - 1";
	bg_img.LoadImageFile(L"res\\images\\interface\\background1unsodded_1.jpg");
	shadow_img.LoadImageFile(L"res\\images\\interface\\plantshadow32.png");
	Sunlight_img.LoadImageFile(L"res\\images\\interface\\SunBack.png");
	Sun.LoadImageFile(L"res\\images\\interface\\Sun.gif");
	InitScene(0,0, bg_img.GetImageWidth(), bg_img.GetImageHeight(),WIN_WIDTH, WIN_HEIGHT);

	sunlight = 100;	//初始阳光值
	//植物
	PlantInit();
	BullentInit();
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

void GameLevel::CutsceneInit()
{
	cutsceneZombies_img[0].LoadImageFile(L"res\\images\\Zombies\\Zombie\\cutscene0_11.png");
	cutsceneZombies_img[1].LoadImageFile(L"res\\images\\Zombies\\Zombie\\cutscene1_11.png");

	moveLength = (bg_img.GetImageWidth() - WIN_WIDTH) / (cutsceneFrame / 5);
	cutsceneFlag = true;
	cutscene_buffer.Play(false);
}

void GameLevel::PlantInit()
{
	plant[0] = new T_Graph(L"res\\images\\Plants\\SunFlower.png");
	spritePlant[0] = new T_Sprite(L"res\\images\\Plants\\SunFlower_18_1.png",73,74);
	plant[1] = new T_Graph(L"res\\images\\Plants\\Peashooter.png");
	spritePlant[1] = new T_Sprite(L"res\\images\\Plants\\Peashooter_13.png",71,71);
}

void GameLevel::ZombiesInit()
{
	attackedZombies[0] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\ZombieLostHead_18.png",166,144);
	attackedZombies[1] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\ZombieHead_12.png",150,186);
	attackedZombies[2] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\ZombieLostHeadAttack11.png",166,144);
	attackedZombies[3] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\ZombieDie_10.png",166,144);
	attackedZombies[4] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\ZombieAttack_21.png", 166, 144);
	spriteZombie[0] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie0_18.png",166,144);
	spriteZombie[1] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie_22.png",166,144);
	spriteZombie[2] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie0_18.png", 166, 144);
	spriteZombie[3] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie_22.png", 166, 144);
	spriteZombie[4] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie0_18.png", 166, 144);
	//spriteZombie[1] = new T_Sprite(L"res\\images\\Zombies\\Zombie\\Zombie_22.png", 166, 144);
	ZOMBIES_ARRAY zombies_array;
	for (int i = 0; i < MAXZOMBIESNUM; i++) {
		zombies_array.zombiesindex = i;
		zombies_array.frame = (2 * i + 1) * 200;
		zombiesArray.push_back(zombies_array);
	}
}

void GameLevel::ProgressBarInit()
{
	progress_bar[0].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterEmpty.png");
	progress_bar[1].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterFull.png");
	progress_bar[2].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterLevelProgress.png");
	progress_bar[3].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterParts1.png");
	progress_bar[4].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterParts2.png");
	progress_bar_length = (progress_bar[0].GetImageWidth() - progress_bar[3].GetImageWidth()) / (double)MaxFrameCount;
}

void GameLevel::CardInit()
{
	int border = 10;	//边距
	int cardHeight;
	plantCard[0].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\SunFlower.png");
	plantCard[1].card = new T_Graph(L"res\\images\\interface\\menu\\handbook\\Card\\Plants\\Peashooter.png");
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

	plantCard[0].nowTime = 0;
	plantCard[1].nowTime = 0;
	plantCard[0].state = false;
	plantCard[1].state = false;
}

void GameLevel::CarInit()
{
	wstring carImagePath = L"res\\images\\interface\\LawnCleaner.png";
	for (int i = 0; i < MAXROW; i++)
	{
		car[i].car = new T_Graph(carImagePath);
		car[i].row = i;
		car[i].state = true;
		car[i].x = CarXSpace;
	}
}

void GameLevel::AudioInit(AudioDX &ds)
{
	bg_buffer.LoadWave(ds,L"res\\audio\\UraniwaNi.wav");
	cutscene_buffer.LoadWave(ds, L"res\\audio\\LookupattheSky.wav");
	car_buffer.LoadWave(ds, L"res\\audio\\lawnmower.wav");
	eatPlant_buffer.LoadWave(ds, L"res\\audio\\chomp.wav");
	click_buffer.LoadWave(ds, L"res\\audio\\buttonclick.wav");
	bulletZom_buffer.LoadWave(ds,L"res\\audio\\grassstep.wav");
}

void GameLevel::BullentInit()
{
	bullet.LoadImageFile(L"res\\images\\Plants\\PeaBullet.png");
	bulletHit.LoadImageFile(L"res\\images\\Plants\\PeaBulletHit.png");
}

void GameLevel::DrawBullet(HDC hdc)
{
	vector<BULLET_INFO>::iterator iter;
	for (iter = bulletVector.begin(); iter != bulletVector.end(); iter++) 
	{
		if (iter->hit == false)
		{
			bullet.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight+ YSpace+30, bullet.GetImageWidth(), bullet.GetImageHeight(),255);
		}
		else
		{
			bulletHit.PaintImage(hdc, iter->position.X, iter->position.Y*PlantHeight + YSpace + 30, bulletHit.GetImageWidth(), bulletHit.GetImageHeight(),255);
		}
	}	
}

void GameLevel::DrawPlant(HDC hdc)
{
	for (int i = 0; i < plantVector.size(); i++)
	{
		plantVector.at(i).sprite->Initiate(plantVector.at(i).info);
		plantVector.at(i).sprite->Draw(hdc);
		if (trueFrame % 4 == 2)
		{
			plantVector.at(i).sprite->LoopFrame();
		}
	}
}

void GameLevel::DrawZombies(HDC hdc)
{
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
	info.Speed = 3;
	ZOMBIES_INFO zombie_info;
	/*判断当前帧是否需要新加入僵尸*/
	for (int i = 0; i < zombiesArray.size(); i++)
	{
		if (frameCount == zombiesArray.at(i).frame) {
			zombie_info.sprite = spriteZombie[zombiesArray.at(i).zombiesindex];
			zombie_info.row = 2;
			zombie_info.x = WIN_WIDTH;  //僵尸横坐标
			zombie_info.isChanged = false;
			zombie_info.count = 0;  
			zombie_info.isChanged = false;
			zombie_info.typeNum = zombiesArray.at(i).zombiesindex;
			info.X = zombie_info.x;
			info.Y = (zombie_info.row) * PlantHeight ; //僵尸纵坐标
			zombie_info.info = info;
			zombiesVector.push_back(zombie_info);
			zombiesVector.back().sprite->Initiate(info);
		}
	}
	vector<ZOMBIES_INFO>::iterator it;
	for (it = zombiesVector.begin(); it != zombiesVector.end();)
	{
		if (it->count == 6 && it->isChanged == false) { /*豌豆与僵尸碰撞6次之后*/
			it->info.X = it->sprite->GetX();
			it->info.Y = it->sprite->GetY();
			it->sprite = attackedZombies[3];
			it->sprite->Initiate(it->info);
			it->sprite->SetSequence(bodySequ, 15);
			it->sprite->SetFrame(0);
			ZOMBIES_INFO zom_header;
			zom_header.info = it->info;
			zom_header.info.Y = it->sprite->GetY() - 15;
			zom_header.info.Speed = -5;
			zom_header.count = it->count;
			zom_header.row = it->row;
			zom_header.x = it->x;
			zom_header.sprite = attackedZombies[1];
			zom_header.sprite->Initiate(zom_header.info);
			ZOM_HEADER header;
			header.zom_info = zom_header;
			header.paintTimes = 0;
			zoms_header.push_back(header);
			it->isChanged = true;
		}
		if (it->count == 8) {
			it = zombiesVector.erase(it);
			if (it == zombiesVector.end()) {
				break;
			}
		}
		if (it->sprite->IsVisible() == true) {
			it->sprite->Draw(hdc);
			it->x = it->sprite->GetX();
			int speed = it->sprite->GetSpeed();
			if (trueFrame % 8 == 7) {
				it->sprite->LoopFrame();
				it->sprite->Move(-speed, 0);
			}
		}
		it++;
		
	}
	vector<ZOM_HEADER>::iterator iter;
	for (iter = zoms_header.begin(); iter != zoms_header.end(); iter++) {
		if (iter->paintTimes <= 10) {
			iter->zom_info.sprite->Draw(hdc);
			iter->zom_info.x = iter->zom_info.sprite->GetX();
			int speed = iter->zom_info.sprite->GetSpeed();
			if (trueFrame % 7 == 6) {
				iter->paintTimes++;
				iter->zom_info.sprite->LoopFrame();
				iter->zom_info.sprite->Move(-speed, 0);
			}
		}
		
		if (iter->zom_info.count == 7) {
			iter = zoms_header.erase(iter);
		}
		if (iter == zoms_header.end()) {
			break;
		}
	}
}

void GameLevel::DrawCutscene(HDC hdc)
{
	bg_img.PaintRegion(bg_img.GetBmpHandle(), hdc, 0, 0, SceneX, 0, WinWidth, WinHeight, 1);
	
	//向右移
	if (frameCount < cutsceneFrame / 5) 
	{
		SceneX += moveLength;
	}
	//回退
	else if (frameCount > cutsceneFrame * 13 / 14) 
	{
		SceneX -= 2*moveLength;
	}
	//中间停顿
	else 
	{
		//变换僵尸帧数
		if (frameCount % 5 == 4) 
		{
			cutsceneZombies_FrameCount++;
			cutsceneZombies_FrameCount = cutsceneZombies_FrameCount % 11;
		}
		//画僵尸
		for (int i = 0; i < 5; i++)
		{
			PAINTREGION_INFO info;
			info.destX = WIN_WIDTH * 3 / 5;
			info.destY = WIN_HEIGHT * i * 3 / 20;
			info.srcX = cutsceneZombies_img[i%2].GetImageWidth() / 11 * cutsceneZombies_FrameCount;
			info.srcY = 0;
			info.regionWidth = cutsceneZombies_img[i%2].GetImageWidth() / 11;
			info.regionHeight = cutsceneZombies_img[i%2].GetImageHeight();
			info.ratio = 1;
			cutsceneZombies_img[i%2].PaintRegion(cutsceneZombies_img[i%2].GetBmpHandle(), hdc,info.destX,info.destY,info.srcX, info.srcY,info.regionWidth,info.regionHeight,info.ratio);
		}
	}
	//绘制关卡名
	T_Graph::PaintBlank(hdc, 0, WIN_HEIGHT * 4 / 5, WIN_WIDTH, WIN_HEIGHT / 10, Color::Blue, 80);
	RectF infoRec;
	infoRec.X = (float)0;
	infoRec.Y = (float)WIN_HEIGHT * 4 / 5;
	infoRec.Width = (float)WIN_WIDTH;
	infoRec.Height = (float)WIN_HEIGHT / 10;
	T_Graph::PaintText(hdc, infoRec, levelName, 20, L"黑体", Color::White, FontStyleBold, StringAlignmentCenter);

	//结束处理
	if (frameCount > cutsceneFrame)
	{
		cutsceneFlag = false;
		frameCount = 0;
		SetScenePos(0, 0);
		cutscene_buffer.Stop();
		bg_buffer.Play(true);
	}
}

void GameLevel::DrawProgressBar(HDC hdc)
{
	progress_bar[0].PaintImage(hdc, WinWidth * 3 / 4, WinHeight * 19 / 20 - 20, progress_bar[0].GetImageWidth(), progress_bar[0].GetImageHeight(), 255);
	PAINTREGION_INFO info;
	info.destX = WinWidth * 3 / 4 + progress_bar[1].GetImageWidth() * (MaxFrameCount - frameCount) / MaxFrameCount;
	info.destY = WinHeight * 19 / 20 - 20;
	info.srcX = progress_bar[1].GetImageWidth()* (MaxFrameCount - frameCount) / MaxFrameCount;
	info.srcY = 0;
	info.regionWidth = progress_bar[1].GetImageWidth()* frameCount / MaxFrameCount + 1;//此处加1防止因为regionWidth为0抛异常
	info.regionHeight = progress_bar[1].GetImageHeight();
	progress_bar[1].PaintRegion(progress_bar[1].GetBmpHandle(), hdc, info.destX, info.destY, info.srcX, info.srcY, info.regionWidth, info.regionHeight, 1);
	progress_bar[4].PaintImage(hdc, WinWidth * 4 / 5, WinHeight * 19 / 20 - 10 - progress_bar[4].GetImageHeight(), progress_bar[4].GetImageWidth(), progress_bar[4].GetImageHeight(),255);
	progress_bar[2].PaintImage(hdc, WinWidth * 4 / 5 - 10, WinHeight * 29 / 30 - 20, progress_bar[2].GetImageWidth(), progress_bar[2].GetImageHeight(), 255);
	progress_bar[3].PaintImage(hdc, WinWidth * 3 / 4 + progress_bar[0].GetImageWidth() - progress_bar[3].GetImageWidth() - progress_bar_length*frameCount, WinHeight * 19 / 20 - 20, progress_bar[3].GetImageWidth(), progress_bar[3].GetImageHeight(), 255);
}

void GameLevel::DrawCard(HDC hdc)
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
		infoRec.Y = (float)plantCard[i].info.y+30;
		infoRec.Width = plantCard[i].card->GetImageWidth()-20;
		infoRec.Height = 20;
		T_Graph::PaintText(hdc, infoRec, T_Util::int_to_wstring(plantCard[i].info.sunlight), 10, L"黑体", Color::Black, FontStyleBold,StringAlignmentFar);
	}
}

void GameLevel::DrawCar(HDC hdc)
{
		int i = 2;
	
		/*if (car[i].car == NULL) {
			continue;
		}*/
		if (car[i].state == true)
		{
			car[i].car->PaintImage(hdc,CarXSpace, (car[i].row)*PlantHeight + YSpace+20, car[i].car->GetImageWidth(), car[i].car->GetImageHeight(),255);
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

void GameLevel::DrawSunLight(HDC hdc)
{
	//产生阳光
	for (int i = 0; i < plantVector.size(); i++) {
		if (plantVector.at(i).pointNum == 0) {
			if (trueFrame % (600 - i * 10) == 0) {
				ProduceSunLight();
			}
		}
	}
	Sunlight_img.PaintImage(hdc, 100, 10, Sunlight_img.GetImageWidth(), Sunlight_img.GetImageHeight(), 255);
	RectF infoRec;
	infoRec.X = (float)125;
	infoRec.Y = (float)15;
	infoRec.Width = (float)100;
	infoRec.Height = (float)30;
	T_Graph::PaintText(hdc, infoRec, T_Util::int_to_wstring(sunlight), 20, L"黑体", Color::Black, FontStyleBold, StringAlignmentCenter);
	vector<SUN_INFO>::iterator iter;
	for (iter = sunlightVector.begin(); iter != sunlightVector.end();iter ++)
	{
		if (iter->isPicked == false) {
			Sun.PaintImage(hdc, iter->pt.x, iter->pt.y, Sun.GetImageWidth(), Sun.GetImageHeight(), 255);
		}
		else
		{
			iter = sunlightVector.erase(iter);
			if (iter == sunlightVector.end()) {
				break;
			}
		}
	}
}

void GameLevel::ProduceSunLight()
{
	srand((unsigned int)time(NULL));
	SUN_INFO sun;
	int posX = rand() % (WIN_WIDTH - Sun.GetImageWidth());
	int posY = rand() % (WIN_HEIGHT - Sun.GetImageHeight());
	POINT pt = { posX,posY};
	sun.isPicked = false;
	sun.pt = pt;
	sunlightVector.push_back(sun);

}

void GameLevel::DrawClickPlant(HDC hdc, int x, int y)
{
	plant[pointPlant]->PaintImage(hdc, x-30, y-40, plant[pointPlant]->GetImageWidth(), plant[pointPlant]->GetImageHeight(),255);
}

void GameLevel::Draw(HDC hdc)
{	
	trueFrame++;
	if (frameCount < MaxFrameCount-1)
	{
		frameCount++;
	}
	if (cutsceneFlag) 
	{
		DrawCutscene(hdc);
	}
	else
	{
		bullet.PaintImage(hdc, 0, 0, bullet.GetImageWidth(), bullet.GetImageHeight());
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
	}

	//测试线
	TestDraw(hdc);
}

void GameLevel::Logic()
{
	CardLogic();
	bulletLogic();
	attackPlantLogic();
	attackZombieLogic();
	carLogic();
}

void GameLevel::CardLogic()
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

void GameLevel::carLogic()
{
	int LineZoms[5][MAXZOMBIESNUM];         //每行的僵尸位置
	for (int i = 0; i < 5; i++) //初始化
	{
		for (int j = 0; j < MAXZOMBIESNUM; j++)
		{
			LineZoms[i][j] = WIN_WIDTH + 1;
		}
	}
	for (int m = 0; m < 5; m++)
	{
		int n = 0;
		for (int i = 0; i < zombiesVector.size(); i++) 
		{
			if (zombiesVector.at(i).row == m) 
			{
				if (LineZoms[m][0] >= zombiesVector.at(i).x)  //将每行僵尸坐标最小的存在第一个
				{
					LineZoms[m][n] = LineZoms[m][0];
					LineZoms[m][0] = zombiesVector.at(i).x;

				}
				else
				{
					LineZoms[m][n] = zombiesVector.at(i).x;
				}
				n++;
			}
		}
	}
	vector<ZOMBIES_INFO>::iterator iter;
	for (int m = 0; m < 5; m++)
	{
		if (CarXSpace + CarWidth >= LineZoms[m][0] +70)
		{
			if (car[m].state == true) 
			{
				for ( iter = zombiesVector.begin(); iter != zombiesVector.end();)
				{
					if (car[m].row == iter->row)
					{
						iter = zombiesVector.erase(iter);
						if (iter == zombiesVector.end()) {
							break;
						}
					}
					else
					{
						iter++;
					}
				}
				car[m].state = false;
			}
		}
			
	}
}



void GameLevel::attackPlantLogic()
{
	int LineZoms[5][MAXZOMBIESNUM] = {WIN_WIDTH + 1};         //每行的僵尸位置
	int LinePlants[5][9] = {0};  //每行的植物
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
	for (int m = 0; m < 5 ; m++)
	{
		for (int n = 0; n < 9; n++)
		{
			for (int i = 0; i < MAXZOMBIESNUM; i++) 
			{
				if (abs(LineZoms[m][i]+ 70- LinePlants[m][n]) <= 30) 
				{
					for (it = zombiesVector.begin(); it != zombiesVector.end(); it++) 
					{
						if (LineZoms[m][i] == it->x)
						{
							it->sprite->SetSpeed(0);
							for (iter = plantVector.begin(); iter != plantVector.end(); iter++)
							{
								if (LinePlants[m][n] == iter->info.X)
								{
									it->sprite->SetSpeed(0);
									eatPlant_buffer.Play(true);
									if (it->count == 6 && iter->attacked == true)
									{
										it->info.X = it->sprite->GetX();
										it->info.Y = it->sprite->GetY();
										it->sprite = attackedZombies[2];
										it->sprite->Initiate(it->info);
										iter->attacked == false;
									}
									if(iter->attacked == false)
									{
										if (it->count < 6)
										{
											it->info.Speed = 0;
											it->info.X = it->sprite->GetX();
											it->info.Y = it->sprite->GetY();
											it->sprite = attackedZombies[4];
											it->sprite->Initiate(it->info);
											iter->attacked = true;
										}
										else
										{
											it->info.Speed = 0;
											it->info.X = it->sprite->GetX();
											it->info.Y = it->sprite->GetY();
											it->sprite = attackedZombies[3];
											it->sprite->Initiate(it->info);
										}
									}
									iter->life--;
									if (iter->life <= 0)
									{
										eatPlant_buffer.Stop();
										iter = plantVector.erase(iter);
										if (it->count < 6)
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

void GameLevel::attackZombieLogic()
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
					info.position.X = (plantVector.at(i).position.X+1) * PlantWidth + CarXSpace + CarWidth;//x坐标
					info.position.Y = plantVector.at(i).position.Y;//第几行
					bulletVector.push_back(info);
				}
			}
		
		}
		
	}	
}

void GameLevel::bulletLogic()
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
		
		if (iter->position.X >= (firstzomX[iter->position.Y]+60))
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
						zombiesVector.at(i).count++;  //僵尸减血次数加1
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

void GameLevel::MouseClick(int x, int y)
{
	if(!pointState)
	{
		int card = CardMouseClick(x, y);
		if (card != -1&& plantCard[card].state==true&& sunlight>=plantCard[card].info.sunlight)
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
	sunlightMouseClick(x,y);
}

int GameLevel::CardMouseClick(int x, int y)
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
		rec.bottom = rec.top + plantCard[i].card->GetImageHeight()/2*0.8;
		if (PtInRect(&rec, pt))
		{
			return i;
		}
	}
	return -1;
}

void GameLevel::PlantMouseClick(int x, int y)
{
	if (x < CarXSpace + CarWidth || y < YSpace+ PlantHeight*INDEXROW ||x > CarXSpace + CarWidth+ PlantWidth*MAXCOLUMN || y>PlantHeight*MAXROW+YSpace+ PlantHeight*INDEXROW)
	{
		return;
	}
	PLANT_INFO tempPlant;
	x = x - CarXSpace - CarWidth;
	y = y - YSpace;
	tempPlant.position.X = x / PlantWidth;  
	tempPlant.position.Y = y / PlantHeight;
	for(int i = 0; i < plantVector.size(); i++)
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
	info.X = tempPlant.position.X*PlantWidth+ CarXSpace + CarWidth+5;
	info.Y = tempPlant.position.Y*PlantHeight+ YSpace+10;
	info.Alpha = 255;
	info.Visible = true;
	
	tempPlant.info = info;
	tempPlant.life = 50;
	tempPlant.attacked = false;
	plantVector.push_back(tempPlant);
	sunlight = sunlight - plantCard[pointPlant].info.sunlight;
	plantCard[pointPlant].nowTime = 0;
}

void GameLevel::sunlightMouseClick(int x, int y)
{
	RECT rect  ;
	POINT pt;
	vector<SUN_INFO>::iterator it;
	for (it = sunlightVector.begin(); it != sunlightVector.end(); it++) {
		rect.left = it->pt.x;
		rect.top = it->pt.y;
		rect.right = rect.left + Sun.GetImageWidth();
		rect.bottom = rect.top + Sun.GetImageHeight();
		pt = { x,y };
		if(PtInRect(&rect,pt)) {
			if (it->isPicked == false) {
				it->isPicked = true;
				sunlight = sunlight + 25;
				click_buffer.Play(false);
			}
		}
	}
}

void GameLevel::MouseMove(int x, int y)
{
	mousex = x;
	mousey = y;
}

void GameLevel::TestDraw(HDC hdc)
{
	T_Graph::PaintBlank(hdc, 50, 0, 1, WinHeight, Color::Black, 255);//推车X坐标50
	for (int i = 0; i < 10; i++) 
	{
		T_Graph::PaintBlank(hdc, 125+i*81, 0, 1, WinHeight, Color::Black, 255);//第一列125，间距81
	}
	for (int i = 0; i < 6; i++) 
	{
		T_Graph::PaintBlank(hdc, 0, 80+100*i, WinWidth, 1, Color::Black, 255);//第一行Y80,行间距100
	}
}
