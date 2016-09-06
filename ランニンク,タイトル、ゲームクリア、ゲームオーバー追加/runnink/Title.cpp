#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

//ここ自体追加点


CUSTOMVERTEX Title[4]
{
	{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1280.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1280.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};
//スタッフロール
CUSTOMVERTEX StaffRoll[4]
{
	{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1280.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1280.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};

//当たり判定
CUSTOMVERTEX hitflg[]
{
	{ 1450.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1950.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1950.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 1450.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};
void HitFlag()
{


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
	case TitleScene://g_playerstate.SceneHitFlag画面
		if (g_playerstate.SceneHitFlag == false )
		{
			SetGameScene(g_pGameTexture[TITLE_TEX], Title);
		}else		
		if (g_playerstate.SceneHitFlag == true)
		{
			static int BlackTime = 0;

			BlackTime++;
			if (BlackTime == 60 * 1)
			{
				g_scene = GameScene;
				p_scene = GamePlayer;
				g_playerstate.SceneHitFlag = false;
				BlackTime = 0;
			}
		}
		break;
	case GameScene:
		break;
	case GameOverScene://ゲームオーバー
		if (g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[TITLE_TEX], Title);
		}else if (g_playerstate.SceneHitFlag == true)
		{
			static int BlackTime = 0;

			BlackTime++;
			if (BlackTime == 60 * 1)
			{

				g_playerstate.posX = 200;
				g_playerstate.posY = 320;
				//ゲームオーバーからg_playerstate.SceneHitFlag
				g_scene = TitleScene;
				p_scene = Normal;
				g_playerstate.SceneHitFlag = false;
				BlackTime = 0;
			}
		}
		break;
	case GameClearScene://
		if (g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[TITLE_TEX], Title);
		}
		else if (g_playerstate.SceneHitFlag == true)
		{
			static int BlackTime = 0;

			BlackTime++;
			if (BlackTime == 60 * 1)
			{

				g_playerstate.posX = 200;
				g_playerstate.posY = 320;
				//ゲームオーバーからg_playerstate.SceneHitFlag
				g_scene = TitleScene;
				p_scene = Normal;
				g_playerstate.SceneHitFlag = false;
				BlackTime = 0;
			}
		}
		break;
	case GameCreditScene:
		if (g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[TITLE_TEX], StaffRoll);
		}
		if (g_playerstate.SceneHitFlag == true)
		{
			g_playerstate.posX = 200;
			g_playerstate.posY = 320;
			//ゲームクリアからg_playerstate.SceneHitFlag
			g_scene = TitleScene;
			p_scene = Normal;
			g_playerstate.SceneHitFlag = false;
		}
		break;
	}
}