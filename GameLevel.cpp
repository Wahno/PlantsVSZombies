#include "GameLevel.h"

void GameLevel::Init()
{
	levelName = L"关卡 1 - 1";
	bg_img.LoadImageFile(L"res\\images\\interface\\background1unsodded_1.jpg");

	InitScene(0,0, bg_img.GetImageWidth(), bg_img.GetImageHeight(),WIN_WIDTH, WIN_HEIGHT);

	cutsceneZombies_img[0].LoadImageFile(L"res\\images\\Zombies\\Zombie\\cutscene0_11.png");
	cutsceneZombies_img[1].LoadImageFile(L"res\\images\\Zombies\\Zombie\\cutscene1_11.png");

	moveLength = (bg_img.GetImageWidth() - WIN_WIDTH) / (cutsceneFrame / 5);
	cutsceneFlag = true;

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
	info.y = border *2+ cardHeight;
	info.sunlight = 100;
	plantCard[1].info = info;

	plantCard[0].nowTime = 0;
	plantCard[1].nowTime = 0;
	plantCard[0].state = false;
	plantCard[1].state = false;
	sunlight = 100;					//初始阳光值

	progress_bar[0].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterEmpty.png");
	progress_bar[1].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterFull.png"); 
	progress_bar[2].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterLevelProgress.png");
	progress_bar[3].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterParts1.png");
	progress_bar[4].LoadImageFile(L"res\\images\\interface\\gamelevel\\FlagMeterParts2.png");
	progress_bar_length = (progress_bar[0].GetImageWidth() - progress_bar[3].GetImageWidth()) / (double)MaxFrameCount;
	cutscene_buffer.Play(false);
}

void GameLevel::AudioInit(AudioDX &ds)
{
	bg_buffer.LoadWave(ds,L"res\\audio\\UraniwaNi.wav");
	cutscene_buffer.LoadWave(ds, L"res\\audio\\LookupattheSky.wav");
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
	}
}

void GameLevel::Draw(HDC hdc)
{	
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
		//画背景
		bg_img.PaintRegion(bg_img.GetBmpHandle(), hdc, 0, 0, 120, 0, WinWidth, WinHeight, 1);
		//画植物卡
		DrawCard(hdc);

		//画进度条
		DrawProgressBar(hdc);
	}
}

void GameLevel::Logic()
{
	CardLogic();
}

void GameLevel::CardLogic()
{
	for (int i = 0; i < MAXPLANTNUM; i++)
	{
		if (plantCard[i].nowTime >= plantCard[i].info.time && sunlight >= plantCard[i].info.sunlight)
		{
			plantCard[i].state = true;
			//plantCard[i].nowTime = 0;
		}
		else
		{
			plantCard[i].state = false;
		}
	}
}
