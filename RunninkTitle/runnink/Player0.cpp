#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

void MapDraw();

void PlayerDraw()
{

	CUSTOMVERTEX PlayerDraw[4]
	{
		{    0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{  200.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.f },
		{  200.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.25f },
		{    0.f, 240.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.25f }
	};

	for (int i = 0; i < 4; i++)
	{
		PlayerDraw[i].x += g_playerstate.posX;
		PlayerDraw[i].y += g_playerstate.posY;
	}

	

	SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);	

}

void PlayerControl()
{
	//�v���C���[�̍����̃}�b�v��x�ʒu
	int playerLeftDownArrayX = int((g_playerstate.posX - 100) / TIPSIZE);
	//�v���C���[�̉E���̃}�b�v��x�ʒu
	int playerRightDownArrayX = int((g_playerstate.posX + 100) / TIPSIZE);
	
	//�v���C���[�̉E�̃}�b�v��x�ʒu
	int playerArrayX = int((g_playerstate.posX + 200) / TIPSIZE);
	//�v���C���[�̃}�b�v��y�ʒu
	int playerArrayY = int(g_playerstate.posY / TIPSIZE);

	//if (g_playerstate.dispPosX == 420.f)
	//{
	//	g_playerstate.dispPosX += MOVESPEED;
	//}
	//else
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		g_mapTip1[i].x -= MOVESPEED;
	//		g_mapTip2[i].x -= MOVESPEED;
	//	}
	//}

	//if (g_key[UP] == ON)
	//{
	//	g_playerstate.jumpFlag = true;
	//	g_playerstate.skyFlag = true;
	//	g_playerstate.a = JUMP_POWER;
	//
	//}

	if (g_key[UP] == PUSH && !g_playerstate.skyFlag)
	{
		g_playerstate.jumpFlag = true;
		g_playerstate.skyFlag = true;
		g_playerstate.a = JUMP_POWER;
	}


	if (g_playerstate.jumpFlag)
	{
		if (g_playerstate.a < 0)
		{
			g_playerstate.a = 0.8f;
		}
	}



	//�W�����v�������ɂ��̏����ɓ���
	if (g_playerstate.jumpFlag)
	{
		//�v���C���[�̉��̃}�b�v�`�b�v������
		int playerUpArrayY = int((g_playerstate.posY - 240) / TIPSIZE);
		if (map[playerUpArrayY][playerLeftDownArrayX] != 0 || map[playerUpArrayY][playerRightDownArrayX] != 0)
		{
			//�㏸���łȂ��Ə㔻����s��Ȃ�
			if (g_playerstate.a < 0)
			{
				g_playerstate.a = 0.8f;
			}
		}
		//�����x����d�͂�����
		g_playerstate.a += GRAVITY;
		//���x���v���C���[�̍��W�ɓ����
		g_playerstate.posY += g_playerstate.a;
	
		int playerDownArrayY = int((g_playerstate.posY + 240) / TIPSIZE);
	
		if (map[playerDownArrayY][playerLeftDownArrayX] == 1 || map[playerDownArrayY][playerRightDownArrayX] == 1)
		{
			//�������łȂ��ƒ��n������s��Ȃ�
			if (g_playerstate.a > 0)
			{
				g_playerstate.jumpFlag = false;
				g_playerstate.skyFlag = false;
			}
		}
	}
	
	int playerDownArrayY = int((g_playerstate.posY + 240) / TIPSIZE);
	//�W�����v�������ȊO�̗�������
	if (map[playerDownArrayY][playerLeftDownArrayX] == 0 || map[playerDownArrayY][playerRightDownArrayX] == 0)
	{
		if (g_playerstate.jumpFlag == false)
		{
			g_playerstate.a += GRAVITY;
			g_playerstate.posY += g_playerstate.a;
			g_playerstate.skyFlag = true;
		}
	}
	
	//�W�����v�������ȊO�̒��n����
	if (map[playerDownArrayY][playerLeftDownArrayX] == 1 || map[playerDownArrayY][playerRightDownArrayX] == 1)
	{
		if (g_playerstate.jumpFlag == false)
		{
			//�����n�ʂȂ�L�����N�^�[�����̒n�ʂ̏�ɍ��W���ړ�����B
			g_playerstate.posY = TIPSIZE * playerDownArrayY - 240;
			g_playerstate.a = 0.f;
			g_playerstate.skyFlag = false;
		}
	}

	//if (g_key[Z] == ON)
	//{
	//
	//}
	//
	//if (g_key[X] == ON)
	//{
	//
	//}

}