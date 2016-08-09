#include <d3d9.h>
#include <d3dx9.h>
#include <dx_tex.h>
#include "GameSceneDraw.h"

// ゲームシーンの画像情報を入れておく配列
LPDIRECT3DTEXTURE9			g_pGameTexture[TEXTURE_MAX];

void Render()
{
	CUSTOMVERTEX backGround[4]
	{
		{    0.f,   0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1280.f,   0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1280.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{    0.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	SetGameSceneStart(D3DFVF_CUSTOMVERTEX);		//SetGameSceneStart()はdx_texから関数呼び出し、
																	
	SetGameScene( g_pGameTexture[BACKGROUND_TEX], backGround);		//SetGameScene()はdx_texから関数呼び出し、
																	
	SetGameSceneEnd();	//SetGameSceneEnd()はdx_texから関数呼び出し

}
