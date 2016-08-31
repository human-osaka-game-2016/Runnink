#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

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
	{ 0.0f, TIPSIZE * -.5f, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 0.0f },
	{ TIPSIZE * 1.5, TIPSIZE * -.5, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE * 1.5, TIPSIZE * 1.5, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{    0.0f, TIPSIZE * 1.5, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 1.0f },
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
																	
	SetGameScene( g_pGameTexture[BACKGROUND_TEX], backGround);		//SetGameScene()はdx_texから関数呼び出し、
	PlayerDraw();
	MapDraw();
	UIRender();
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

		}
	}

}

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

	MapLoad("map(仮).csv");

}