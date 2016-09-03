#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

// �Q�[���V�[���̉摜�������Ă����z��
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

TEXTSTATE g_textstate;//�ǉ��_

// �}�b�v�`�b�v�̃f�[�^���i�[���Ă�񎟌��z��
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

	SetGameSceneStart(D3DFVF_CUSTOMVERTEX);		//SetGameSceneStart()��dx_tex����֐��Ăяo���A
	

	//�V�[��ID���ƂɂƂԁ@�ǉ��_
	switch (g_scene)
	{
	case TitleScene://�^�C�g�����
		titlescene();//�^�C�g���V�[���̕`��
		HitFlag();//�����蔻��
		PlayerDraw();//�v���C���[�`��
		TextDraw();//�����̕`��
		break;
	case GameScene://�v���C���
		SetGameScene(g_pGameTexture[BACKGROUND_TEX], backGround);		//SetGameScene()��dx_tex����֐��Ăяo���A
		PlayerDraw();
		MapDraw();//�}�b�v�`��
		UIRender();
		break;
	case GameOverScene://�Q�[���I�[�o�[
		titlescene();
		TextDraw();
		HitFlag();//�����蔻��
		PlayerDraw();
		MapDraw();
		break;
	};//�����܂�


	SetGameSceneEnd();	//SetGameSceneEnd()��dx_tex����֐��Ăяo��

}

// Csv�̓ǂݍ��݊֐�
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

// �Q�[���V�[���̉���֐�
void GameSceneFree()
{
	// �e�N�X�`�������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_pGameTexture[i]->Release();
	}
}

void TextDraw()//�ǉ��_
{
	//�����`��
	CUSTOMVERTEX GameOverText[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX TitleText[4]
	{
		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 350.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};
	CUSTOMVERTEX PushEnterText[4]
	{

		{ 0.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 0.f },
		{ 1280.f, 0.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 0.f },
		{ 1280.f, 720.f, 1.f, 1.0f, 0xFFFFFFFF, 1.0f, 1.f },
		{ 0.f, 720.f, 1.f, 1.0f, 0xFFFFFFFF, 0.0f, 1.f }
	};

	for (int i = 0; i < 4; i++)
	{
		GameOverText[i].x += g_textstate.TposX;
		GameOverText[i].y += g_textstate.TposY;
	}


	for (int i = 0; i < 4; i++)
	{
		PushEnterText[i].x += g_textstate.PEposX;
		PushEnterText[i].y += g_textstate.PEposY;
	}

	//�V�[��ID���ƂɂƂ�
	switch (g_scene)
	{
	case TitleScene:
		SetGameScene(g_pGameTexture[TITLE_TEXT], TitleText);

		SetGameScene(g_pGameTexture[PUSHENTER_TEXT], PushEnterText);
		break;
	case GameScene:
		g_textstate.TposX = 1100;
		g_textstate.PEposX = 1100;
		break;
	case GameOverScene:
		SetGameScene(g_pGameTexture[GAMEOVER_TEXT], GameOverText);
		SetGameScene(g_pGameTexture[PUSHENTER_TEXT], PushEnterText);
		if (g_textstate.PEposX != 0)
		{
			g_textstate.TposX -= 10;
			g_textstate.PEposX -= 10;
		}

		break;
	};
}//�����܂�

void Init_Csv()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//	�A���t�@�u�����h�ɂ�铧������L���ɂ���
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//	�������u�����f�B���O�̐ݒ�
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//	�����@�ƃZ�b�g
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);		//	�f�B�q���[�Y�F�̐ݒ�

	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		//	�f�B�q���[�Y�F�̐F�����̏�����L��������

	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		//	�J���[�u�����f�B���O��������Z�ɂ���

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//	�f�B�q���[�Y�F�̓��ߐF�����̏�����L��������

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//	�A���t�@�u�����f�B���O�̏�������Z�ɂ���

	MapLoad("map(��).csv");

}