#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

//�������̒ǉ��_


CUSTOMVERTEX Title[4]
{
	{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1280.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1280.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 0.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};

//�����蔻��
CUSTOMVERTEX hitflg[]
{
	{ 1850.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1950.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1950.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 1850.f, 600.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};
void HitFlag()
{


	switch (g_scene)
	{
	case TitleScene:
		//�����蔻��`��
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
	case TitleScene://�^�C�g�����

		if (g_playerstate.TitlehitFlag == false)
		{
			SetGameScene(g_pGameTexture[TITLE_TEX], Title);
		}

		if (g_playerstate.TitlehitFlag == true)
		{

			//�^�C�g������Q�[���V�[���Ɉڍs
			g_scene = GameScene;
			p_scene = GamePlayer;
			g_playerstate.TitlehitFlag = false;
		}
		break;
	case GameScene:
		break;
	case GameOverScene://�Q�[���I�[�o�[


		if (g_playerstate.GameoverhitFlag == true)
		{
			g_playerstate.posX = 200;
			g_playerstate.posY = 320;
			//�Q�[���I�[�o�[����^�C�g��
			g_scene = TitleScene;
			p_scene = Normal;
			g_playerstate.GameoverhitFlag = false;
		}
		SetGameScene(g_pGameTexture[TITLE_TEX], Title);		//SetGameScene()��dx_tex����֐��Ăяo���A
		break;
	}
}