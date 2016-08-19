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
		{  200.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{  200.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{    0.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
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

}