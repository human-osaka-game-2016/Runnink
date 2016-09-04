#include"stdio.h"
#include "GameSceneDraw.h"
#include <dx_lib.h>
#include "GameSceneControl.h"
#include"UI.h"
UISTATE g_uistate = { 210.f, 100.f, };
char leftsize = INK_M;
char HPsize = INK_L;
void UIRender(void)
{

	//UI_INK_ARMの頂点座標の入力
	CUSTOMVERTEX UI_INK_ARM[4]
	{
		{ 12.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 66.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, },
		{ 66.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 12.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, },
	};



	//UI_INK_LEGの頂点座標の入力
	CUSTOMVERTEX UI_INK_LEG[4]
	{
		{ 75.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 129.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, },
		{ 129.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 75.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, },
	};





	CUSTOMVERTEX UI_INK_HP[4]
	{
		{ 135.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 189.f, 10.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, },
		{ 189.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 135.f, 135.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, },

	};


	//UICONの頂点座標の入力
	CUSTOMVERTEX UIICON[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 200.f, 0.f, 1.f, 1.f, 0XFFFFFFFF, 1.f, 0.f, },
		{ 200.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 0.f, 160.f, 1.f, 1.f, 0XFFFFFFFF, 0.f, 1.f, },
	};
	SetGameScene(g_pGameTexture[UICON1_TEX], UIICON);
	if (leftsize == INK_S)
	{
		SetGameScene(g_pGameTexture[S_TEX], UI_INK_ARM);
		SetGameScene(g_pGameTexture[L_TEX], UI_INK_LEG);
	}
	else if (leftsize == INK_M)
	{
		SetGameScene(g_pGameTexture[M_TEX], UI_INK_ARM);
		SetGameScene(g_pGameTexture[M_TEX], UI_INK_LEG);
	}
	else if (leftsize == INK_L)
	{
		SetGameScene(g_pGameTexture[L_TEX], UI_INK_ARM);
		SetGameScene(g_pGameTexture[S_TEX], UI_INK_LEG);
	}
	if (HPsize == INK_S)
	{
		SetGameScene(g_pGameTexture[S_TEX], UI_INK_HP);
	}
	else if (HPsize == INK_M)
	{
		SetGameScene(g_pGameTexture[M_TEX], UI_INK_HP);
	}
	else if (HPsize == INK_L)
	{
		SetGameScene(g_pGameTexture[L_TEX], UI_INK_HP);
	}

}



void UIDATE(void)
{
	if (g_key[Z] == PUSH)
	{
		if (leftsize == INK_S)
		{
			leftsize = INK_M;
		}
		else if (leftsize == INK_M)
		{
			leftsize = INK_L;
		}
	}
	if (g_key[X] == PUSH){
		if (leftsize == INK_L)
		{
			leftsize = INK_M;
		}
		else if (leftsize == INK_M)
		{
			leftsize = INK_S;
		}

	}



	//-----------------------------------------------------
	//以下デバック用
	//-----------------------------------------------------
	if (g_key[M] == PUSH)
		if (HPsize == INK_L)
		{
			HPsize = INK_M;
		}
		else if (HPsize == INK_M)
		{

			HPsize = INK_S;
		}
		else if (HPsize == INK_S)
		{
			HPsize = INK_None;
		}

}



//SetGameScene(g_pGameTexture[S_TEX], UI_INK_ARM);
//SetGameScene(g_pGameTexture[L_TEX], UI_INK_HP);
//SetGameScene(g_pGameTexture[M_TEX], UI_INK_LEG);