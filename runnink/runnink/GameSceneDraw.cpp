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
	{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ TIPSIZE, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ TIPSIZE, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{ 0.0f, TIPSIZE, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};


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
																	
	SetGameScene( g_pGameTexture[BACKGROUND_TEX], backGround);		//SetGameScene()��dx_tex����֐��Ăяo���A
	PlayerDraw();
	MapDraw();
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
				// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
				pD3Device->SetTexture(0, g_pGameTexture[MAP_GROUND_TEX]);
				// �`��
				pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawMapVertex, sizeof(CUSTOMVERTEX));
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
