#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"





CUSTOMVERTEX Title[4]
{
	{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1280.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1280.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};

CUSTOMVERTEX hitflg[]//当たり判定
{
	{ 1850.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1950.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1950.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 1850.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};
void HitFlag()
{
	if (g_playerstate.TitlehitFlag == true)
	{
		g_playerstate.BlackoutFlag = false;

		//タイトルからゲームシーンに移行
		g_scene = GameScene;
	}



	switch (g_scene)
	{
	case TitleScene:
		//当たり判定描画
		SetGameScene(g_pGameTexture[HIT_FLG], hitflg);
		break;
	case GameScene:

		break;
	case GameOverScene:
		SetGameScene(g_pGameTexture[HIT_FLG], hitflg);
		break;
	}
}
void titlescene()
{
	switch (g_scene)
	{
	case TitleScene://タイトル画面
		if (g_playerstate.BlackoutFlag = true)
		{//ブラックアウトフラグがトゥルーかつヒットフラグがファルスの時、タイトルを描画する
			if (g_playerstate.TitlehitFlag == false)
			{
				SetGameScene(g_pGameTexture[TITLE_TEX], Title);
			}
		}
		break;
	case GameScene:
		g_playerstate.BlackoutFlag = true;//
		g_playerstate.TitlehitFlag = false;//
		break;
	case GameOverScene://ゲームオーバー
		SetGameScene(g_pGameTexture[TITLE_TEX], Title);		//SetGameScene()はdx_texから関数呼び出し、
		break;
	}
}