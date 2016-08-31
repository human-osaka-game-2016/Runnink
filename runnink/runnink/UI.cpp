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
	/*
	//UI_INK_ARMの頂点座標の入力
	CUSTOMVERTEX UI_INK_ARM[4]
	{
	//{},
	//{},
	//{},
	//{},
	};
	SetGameScene(g_pGameTexture[ARM_TEX], UI_INK_ARM);


	//UI_INK_LEGの頂点座標の入力
	CUSTOMVERTEX UI_INK_LEG[4]
	{
	//{}
	//{}
	//{}
	//{}
	SetGameScene(g_pGameTexture[UILEG_TEX], UI_INK_LEG);

	};


	CUSTOMVERTEX UI_INK_HP[4]
	{
	//{}
	//{}
	//{}
	//{}
	SetGameScene(g_pGameTexture[UIHP_TEX], UIICON);

	};*/
}

void UICON_DATE(void)
{
	int ARM_INK;
	int LEG_INK;
	int HP_INK;

	ARM_INK = 0;
	LEG_INK = 0;
	HP_INK = 0;

}