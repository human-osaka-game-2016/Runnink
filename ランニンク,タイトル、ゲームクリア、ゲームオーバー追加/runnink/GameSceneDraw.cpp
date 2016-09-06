#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"
#include "Enemy.h"

// ゲームシーンの画像情報を入れておく配列
LPDIRECT3DTEXTURE9			g_pGameTexture[TEXTURE_MAX];

CUSTOMVERTEX g_mapTip1[] =
{
	{    0.0f,    0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ TIPSIZE,    0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{    0.0f, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};

CUSTOMVERTEX g_mapTip2[] =
{
	{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ TIPSIZE, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{ 0.0f, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};

CUSTOMVERTEX g_mapTip3[] =
{
	{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ TIPSIZE, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{ 0.0f, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};

CUSTOMVERTEX g_mapTip4[] =
{
	{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ TIPSIZE, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{ 0.0f, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};

//CUSTOMVERTEX g_mapTip2[] =
//{
//	{ 0.0f, TIPSIZE * 1.5, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
//	{ TIPSIZE * 1.5, TIPSIZE * 1.5, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
//	{ TIPSIZE * 1.5, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
//	{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
//	
//};
//

TEXTSTATE g_textstate;//追加点

// マップチップのデータを格納してる二次元配列
int map[MAP_HEIGHT][MAP_WIDTH];

void Render()
{
	static float BackGroundTv = 0.0f;

	CUSTOMVERTEX backGround[4]
	{
		{    0.f,   0.f, 1.f, 1.f, 0xFFFFFFFF, BackGroundTv, 0.f },
		{ 1280.f,   0.f, 1.f, 1.f, 0xFFFFFFFF, BackGroundTv + 0.3f, 0.f },
		{ 1280.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, BackGroundTv + 0.3f, 1.f },
		{    0.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, BackGroundTv, 1.f }
	};

	BackGroundTv += SCROOLSPEED;

	SetGameSceneStart(D3DFVF_CUSTOMVERTEX);		//SetGameSceneStart()はdx_texから関数呼び出し、
																	



	//シーンIDごとにとぶ　追加点
	switch (g_scene)
	{
	case TitleScene://タイトル画面
		titlescene();//タイトルシーンの描画
		HitFlag();//当たり判定
		PlayerDraw();//プレイヤー描画
		TextDraw();//文字の描画
		break;
	case GameScene://プレイ画面
		SetGameScene(g_pGameTexture[BACKGROUND_TEX], backGround);		//SetGameScene()はdx_texから関数呼び出し、
		PlayerDraw();
		MapDraw();
		Draw_Enemy();
		PlayerSliding();
		PlayerPunch();
		UIRender();
		break;
	case GameOverScene://ゲームオーバー
		titlescene();
		TextDraw();
		HitFlag();//当たり判定
		PlayerDraw();
		break;
	case GameClearScene:
		titlescene();
		TextDraw();
		HitFlag();//当たり判定
		PlayerDraw();
		break;
	case GameCreditScene:
		titlescene();
		TextDraw();
		break;
	};//ここまで

	SetGameSceneEnd();	//SetGameSceneEnd()はdx_texから関数呼び出し

}

// Csvの読み込み関数
void MapLoad(const char* mapdata)
{
	FILE*  fp;
	fopen_s(&fp, mapdata, "r");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &map[i][j], _countof(map));
		}
	}
}


void MapDraw()
{

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == 1)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip1[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}

				SetGameScene(g_pGameTexture[MAP_GROUND_TEX], drawMapVertex);

			}
			else if (map[y][x] == 2)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip2[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}

				SetGameScene(g_pGameTexture[MAP_GROUND2_TEX], drawMapVertex);
			}
			else if (map[y][x] == 3)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip2[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}

				SetGameScene(g_pGameTexture[MAP_GROUND2_TEX], drawMapVertex);
			}
			else if (map[y][x] == 4)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip2[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}

				SetGameScene(g_pGameTexture[MAP_GROUND2_TEX], drawMapVertex);
			}

		}
	}

}
//文字描画　追加点
void TextDraw()//追加点
{
	//文字描画

	CUSTOMVERTEX TitleText[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX PushEnterText[4]
	{
		{ 300.f, 200.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 980.f, 200.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 980.f, 550.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 300.f, 550.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX GameOverText[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	//---------------------------------------------
	//
	//     ゲームクリア画面
	//
	//---------------------------------------------
	CUSTOMVERTEX GameClearText[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX GoCreditText[4]
	{
		{ 480.f, 250.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1380.f, 250.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1380.f, 400.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 480.f, 400.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX BackTitleText[4]
	{

		{ 580.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1380.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1380.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 580.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	//---------------------------------------------
	//
	//     クレジット画面
	//
	//---------------------------------------------
		
	/*CUSTOMVERTEX Staff[4]
	{

		{ 0.f, .f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, .f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, .f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, .f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};*/
	CUSTOMVERTEX TeamLogo[4]
	{
		{ 225.f, 8500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1055.f, 8500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1055.f, 9220.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 225.f, 9220.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};

	CUSTOMVERTEX Staff1[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff2[4]
	{

		{ 0.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 1000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 1000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff3[4]
	{

		{ 0.f, 1000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 1000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 1500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 1500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff4[4]
	{

		{ 0.f, 1500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f,1500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f,2000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 2000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff5[4]
	{

		{ 0.f, 2000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 2000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 2500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 2500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff6[4]
	{

		{ 0.f, 2500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 2500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 3000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 3000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};

	CUSTOMVERTEX Staff7[4]
	{

		{ 0.f, 3000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 3000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 3500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 3500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff8[4]
	{

		{ 0.f, 3500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 3500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 4000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 4000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff9[4]
	{

		{ 0.f, 4000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 4000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 4500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 4500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff10[4]
	{
		{ 0.f, 4500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 4500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 5000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 5000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff11[4]
	{
		{ 0.f, 5000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 5000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 5500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 5500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff12[4]
	{
		{ 0.f, 5500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 5500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 6000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 6000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff13[4]
	{
		{ 0.f, 6000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 6000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 6500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 6500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff14[4]
	{
		{ 0.f, 6500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 6500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 7000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 7000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX Staff15[4]
	{
		{ 0.f, 7000.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 7000.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 7500.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 7500.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	for (int i = 0; i < 4; i++)
	{
		//ゲームオーバー画面
		GameOverText[i].x += g_textstate.TposX;
		GameOverText[i].y += g_textstate.TposY;
		PushEnterText[i].x += g_textstate.TposX;
		PushEnterText[i].y += g_textstate.TposY;
		//ゲームクリア画面
		GameClearText[i].x += g_textstate.TposX;
		GameClearText[i].y += g_textstate.TposY;
		GoCreditText[i].x += g_textstate.TposX;
		GoCreditText[i].y += g_textstate.TposY;
		BackTitleText[i].x += g_textstate.TposX;
		BackTitleText[i].y += g_textstate.TposY;
		TeamLogo[i].y += g_textstate.LogoposY;
		Staff1[i].y += g_textstate.SposY;
		Staff2[i].y += g_textstate.SposY;
		Staff3[i].y += g_textstate.SposY;
		Staff4[i].y += g_textstate.SposY;
		Staff5[i].y += g_textstate.SposY;
		Staff6[i].y += g_textstate.SposY;
		Staff7[i].y += g_textstate.SposY;
		Staff8[i].y += g_textstate.SposY;
		Staff9[i].y += g_textstate.SposY;
		Staff10[i].y += g_textstate.SposY;
		Staff11[i].y += g_textstate.SposY;
		Staff12[i].y += g_textstate.SposY;
		Staff13[i].y += g_textstate.SposY;
		Staff14[i].y += g_textstate.SposY;
		Staff15[i].y += g_textstate.SposY;

//		Staff[i].x += g_textstate.SposX;
//		Staff[i].y += g_textstate.SposY;
	}

	//シーンIDごとにとぶ
	switch (g_scene)
	{
	case TitleScene:
		if(g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[TITLE_TEXT], TitleText);
			g_textstate.TposX = 0;
			SetGameScene(g_pGameTexture[PUSHENTER_TEXT], PushEnterText);
		}
		break;
	case GameScene:
		g_textstate.TposX = 1100;
		break;
	case GameOverScene:
		if (g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[GAMEOVER_TEXT], GameOverText);
			SetGameScene(g_pGameTexture[PUSHENTER_TEXT], PushEnterText);
			if (g_textstate.TposX != 0)
			{
				g_textstate.TposX -= 10;
			}
		}
		break;
	case GameClearScene:
		if (g_playerstate.SceneHitFlag == false)
		{
			SetGameScene(g_pGameTexture[GAMECLEAR_TEXT], GameClearText);
			SetGameScene(g_pGameTexture[GOCREDIT_TEXT], GoCreditText);
			SetGameScene(g_pGameTexture[BACKTITLE_TEXT], BackTitleText);
			g_textstate.SposY = 1100;
			if (g_textstate.TposX != 0)
			{
				g_textstate.TposX -= 10;
			}
		}
		break;
	case GameCreditScene:
		if (TeamLogo[0].y > 3)
		{
			g_textstate.SposY -= 3;
			g_textstate.LogoposY -= 3;

			if (g_key[SPACE] == ON)//ゲームクリア画面テスト用
			{
				g_textstate.SposY -= 7;
				g_textstate.LogoposY -= 7;
			}
		}
		else
		{
			static int LogoTime = 0;
			
			LogoTime++;
			if (LogoTime == 60 * 4)
			{
				g_playerstate.SceneHitFlag = true;
				LogoTime = 0;
			}
		}
		
		SetGameScene(g_pGameTexture[TEAM_LOGO], TeamLogo);
		SetGameScene(g_pGameTexture[STAFF1], Staff1);
		SetGameScene(g_pGameTexture[STAFF2], Staff2);
		SetGameScene(g_pGameTexture[STAFF3], Staff3);
		SetGameScene(g_pGameTexture[STAFF4], Staff4);
		SetGameScene(g_pGameTexture[STAFF5], Staff5);
		SetGameScene(g_pGameTexture[STAFF6], Staff6);
		SetGameScene(g_pGameTexture[STAFF7], Staff7);
		SetGameScene(g_pGameTexture[STAFF8], Staff8);
		SetGameScene(g_pGameTexture[STAFF9], Staff9);
		SetGameScene(g_pGameTexture[STAFF10], Staff10);
		SetGameScene(g_pGameTexture[STAFF11], Staff11);
		SetGameScene(g_pGameTexture[STAFF12], Staff12);
		SetGameScene(g_pGameTexture[STAFF13], Staff13);
		SetGameScene(g_pGameTexture[STAFF14], Staff14);
		SetGameScene(g_pGameTexture[STAFF15], Staff15);
		//SetGameScene(g_pGameTexture[], Staff);
		break;
	};
}//ここまで


// ゲームシーンの解放関数
void GameSceneFree()
{
	// テクスチャを解放
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_pGameTexture[i]->Release();
	}
}


void Init_Csv()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//	アルファブレンドによる透明化を有効にする
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//	半透明ブレンディングの設定
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//	↑↑　とセット
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);		//	ディヒューズ色の設定

	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		//	ディヒューズ色の色引数の処理を有効化する

	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		//	カラーブレンディング処理を乗算にする

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//	ディヒューズ色の透過色引数の処理を有効化する

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//	アルファブレンディングの処理を乗算にする

	MapLoad("map01234.csv");

}