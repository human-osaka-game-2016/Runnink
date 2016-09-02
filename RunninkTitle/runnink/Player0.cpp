#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

void MapDraw();

void PlayerDraw()
{

	CUSTOMVERTEX PlayerDraw[4]
	{
		{    0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{  200.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.f },
		{  200.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.25f },
		{    0.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.25f }
	};

	for (int i = 0; i < 4; i++)
	{
		PlayerDraw[i].x += g_playerstate.posX;
		PlayerDraw[i].y += g_playerstate.posY;
	}

	

	SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);	

}

void PlayerControl()
{
	//プレイヤーの左下のマップのx位置
	int playerLeftDownArrayX = int((g_playerstate.posX - 100) / TIPSIZE);
	//プレイヤーの右下のマップのx位置
	int playerRightDownArrayX = int((g_playerstate.posX + 100) / TIPSIZE);
	
	//プレイヤーの右のマップのx位置
	int playerArrayX = int((g_playerstate.posX + 200) / TIPSIZE);
	//プレイヤーのマップのy位置
	int playerArrayY = int(g_playerstate.posY / TIPSIZE);

	//if (g_playerstate.dispPosX == 420.f)
	//{
	//	g_playerstate.dispPosX += MOVESPEED;
	//}
	//else
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		g_mapTip1[i].x -= MOVESPEED;
	//		g_mapTip2[i].x -= MOVESPEED;
	//	}
	//}

	//if (g_key[UP] == ON)
	//{
	//	g_playerstate.jumpFlag = true;
	//	g_playerstate.skyFlag = true;
	//	g_playerstate.a = JUMP_POWER;
	//
	//}

	if (g_key[UP] == PUSH && !g_playerstate.skyFlag)
	{
		g_playerstate.jumpFlag = true;
		g_playerstate.skyFlag = true;
		g_playerstate.a = JUMP_POWER;
	}


	if (g_playerstate.jumpFlag)
	{
		if (g_playerstate.a < 0)
		{
			g_playerstate.a = 0.8f;
		}
	}



	//ジャンプ処理中にこの処理に入る
	if (g_playerstate.jumpFlag)
	{
		//プレイヤーの下のマップチップを見る
		int playerUpArrayY = int((g_playerstate.posY - 240) / TIPSIZE);
		if (map[playerUpArrayY][playerLeftDownArrayX] != 0 || map[playerUpArrayY][playerRightDownArrayX] != 0)
		{
			//上昇中でないと上判定を行わない
			if (g_playerstate.a < 0)
			{
				g_playerstate.a = 0.8f;
			}
		}
		//初速度から重力を引く
		g_playerstate.a += GRAVITY;
		//速度をプレイヤーの座標に入れる
		g_playerstate.posY += g_playerstate.a;
	
		int playerDownArrayY = int((g_playerstate.posY + 240) / TIPSIZE);
	
		if (map[playerDownArrayY][playerLeftDownArrayX] == 1 || map[playerDownArrayY][playerRightDownArrayX] == 1)
		{
			//落下中でないと着地判定を行わない
			if (g_playerstate.a > 0)
			{
				g_playerstate.jumpFlag = false;
				g_playerstate.skyFlag = false;
			}
		}
	}
	
	int playerDownArrayY = int((g_playerstate.posY + 240) / TIPSIZE);
	//ジャンプ処理中以外の落下処理
	if (map[playerDownArrayY][playerLeftDownArrayX] == 0 || map[playerDownArrayY][playerRightDownArrayX] == 0)
	{
		if (g_playerstate.jumpFlag == false)
		{
			g_playerstate.a += GRAVITY;
			g_playerstate.posY += g_playerstate.a;
			g_playerstate.skyFlag = true;
		}
	}
	
	//ジャンプ処理中以外の着地処理
	if (map[playerDownArrayY][playerLeftDownArrayX] == 1 || map[playerDownArrayY][playerRightDownArrayX] == 1)
	{
		if (g_playerstate.jumpFlag == false)
		{
			//下が地面ならキャラクターをその地面の上に座標を移動する。
			g_playerstate.posY = TIPSIZE * playerDownArrayY - 240;
			g_playerstate.a = 0.f;
			g_playerstate.skyFlag = false;
		}
	}

	//if (g_key[Z] == ON)
	//{
	//
	//}
	//
	//if (g_key[X] == ON)
	//{
	//
	//}

}