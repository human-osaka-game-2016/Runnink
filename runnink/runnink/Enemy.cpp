#include <stdlib.h>
#include <time.h>
#include <dx_lib.h>
//#include "Enemy.h"

//--------------------------------
//　デバック目的の為　マスター不要
#include "GameSceneControl.h"
#include "GameSceneDraw.h"
//--------------------------------



#define ENEMY_WIDTH 256
#define ENEMY_HIGHT 128
#define ENEMY_POSX 1408
#define ENEMY_POSY_1 460
#define ENEMY_POSY_2 260
#define ENEMY_POSY_3 360
#define ENEMY_SPEED 10.f

CUSTOMVERTEX Enemy[4];
CUSTOMVERTEX Fire[4];

bool Enemy_HitFrag = false;
bool DrawFrag = false;
bool fireFrag = false;

void Init_Enemy_1()
{
	Enemy[0] = {ENEMY_POSX - (ENEMY_WIDTH / 2), ENEMY_POSY_1 - (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, };
	Enemy[1] = {ENEMY_POSX + (ENEMY_WIDTH / 2), ENEMY_POSY_1 - (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, };
	Enemy[2] = {ENEMY_POSX + (ENEMY_WIDTH / 2), ENEMY_POSY_1 + (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, };
	Enemy[3] = {ENEMY_POSX - (ENEMY_WIDTH / 2), ENEMY_POSY_1 + (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, };
}

void Init_Enemy_2()
{
	Enemy[0] = { ENEMY_POSX - (ENEMY_WIDTH /2), ENEMY_POSY_2 - (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, };
	Enemy[1] = { ENEMY_POSX + (ENEMY_WIDTH /2), ENEMY_POSY_2 - (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, };
	Enemy[2] = { ENEMY_POSX + (ENEMY_WIDTH /2), ENEMY_POSY_2 + (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, };
	Enemy[3] = { ENEMY_POSX - (ENEMY_WIDTH /2), ENEMY_POSY_2 + (ENEMY_HIGHT / 2), 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, };
}

void Init_Enemy_3()
{
	Enemy[0] = { ENEMY_POSX - ENEMY_WIDTH, ENEMY_POSY_3 - ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, };
	Enemy[1] = { ENEMY_POSX + ENEMY_WIDTH, ENEMY_POSY_3 - ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, };
	Enemy[2] = { ENEMY_POSX + ENEMY_WIDTH, ENEMY_POSY_3 - ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, };
	Enemy[3] = { ENEMY_POSX - ENEMY_WIDTH, ENEMY_POSY_3 - ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, };
}

void Init_Fire()
{
	Fire[0] = { ENEMY_POSX - ENEMY_WIDTH, ENEMY_POSY_3, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	Fire[1] = { ENEMY_POSX - (ENEMY_WIDTH / 2), ENEMY_POSY_3, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	Fire[2] = { ENEMY_POSX - (ENEMY_WIDTH / 2), ENEMY_POSY_3 + ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	Fire[3] = { ENEMY_POSX - ENEMY_WIDTH, ENEMY_POSY_3 + ENEMY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}


void Control_Enemy()
{
	for (int i = 0; i < 4; i++)
	{
		Enemy[i].x -= ENEMY_SPEED;
	}

	if (fireFrag)
	{
		for (int i = 0; i < 4; i++)
		{
			Fire[i].x -= ENEMY_SPEED;
		}
	}

	if (Enemy[1].x <= 0.f)
	{
		DrawFrag = false;
		if (fireFrag)
		{
			fireFrag = false;
		}
	}
}

void Draw_Enemy()
{
	static int fireTime;

	if (!DrawFrag)
	{
		srand((unsigned)time(NULL));

		int Rand = rand() % 11;

		if (Rand == 0)
		{
			Init_Enemy_3();
			Init_Fire();
			fireFrag = true;
			fireTime = 0;
		}
		else if (Rand <= 5)
		{
			Init_Enemy_2();
		}
		else
		{
			Init_Enemy_1();
		}
	}
	else
	{
		Control_Enemy();

		SetGameScene(g_pGameTexture[ENEMY_TEX], Enemy);

		if (fireFrag)
		{
			fireTime++;
		}
		if (Enemy_HitFrag)
		{
			DrawFrag = false;
			Enemy_HitFrag = false;
			fireFrag = false;
		}
	}
}

//------------------------------------------
//
//　以下　デバック用
//
//------------------------------------------
void Comand()
{
	if (g_key[K] == PUSH)
	{
		DrawFrag = true;
	}
	if (g_key[L] == PUSH)
	{
		DrawFrag = false;
		fireFrag = false;
	}
}