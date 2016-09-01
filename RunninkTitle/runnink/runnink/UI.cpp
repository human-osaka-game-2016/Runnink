//include"UI.h"
#include"stdio.h"
#include "GameSceneDraw.h"
#include <dx_lib.h>
#include "GameSceneControl.h"

UISTATE g_uistate = { 100.f, 100.f };

void UIRender(void)
{
	//UICONの頂点座標の入力
	CUSTOMVERTEX UIICON[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 200.f, 0.f, 1.f, 1.f, 0XFFFFFFFF, 1.f, 0.f, },
		{ 200.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 0.f, 160.f, 1.f, 1.f, 0XFFFFFFFF, 0.f, 1.f, },
	};
	SetGameScene(g_pGameTexture[UICON1_TEX], UIICON);
	
	//UI_INK_ARMの頂点座標の入力
	CUSTOMVERTEX UI_INK_S[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 40.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f,},
		{ 40.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f,},
		{ 0.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f,},
	};
	SetGameScene(g_pGameTexture[S_TEX], UI_INK_S);


	//UI_INK_LEGの頂点座標の入力
	CUSTOMVERTEX UI_INK_M[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 40.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, },
		{ 40.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 0.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, },
	};
	SetGameScene(g_pGameTexture[M_TEX], UI_INK_M);

	


	CUSTOMVERTEX UI_INK_L[4]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f, },
		{ 40.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f, },
		{ 40.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f, },
		{ 0.f, 160.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f, },
	};
	SetGameScene(g_pGameTexture[L_TEX], UI_INK_L);

	
}


