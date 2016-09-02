#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"
#include "player.h"

float CalcAng(float y, float x) {
	float ang;

	ang = atan2(y, x);
	if (y < 0.0f) {
		ang += D3DX_PI * 2;
	}

	return ang;
}

CUSTOMVERTEX* MakeV(VPos pnt[])		//�S�_���o�[�e�b�N�X���쐬
{
	static CUSTOMVERTEX Body[8];

	for (int i = 0; i < 8; i++) {
		Body[i].z = 0.5f;
		Body[i].rhw = 1.0f;
		Body[i].color = 0xFFFFFFFF;
	}
	Body[0].x = pnt[3].x;	Body[0].y = pnt[3].y;
	Body[1].x = pnt[0].x;	Body[1].y = pnt[0].y;
	Body[6].x = pnt[2].x;	Body[6].y = pnt[2].y;
	Body[7].x = pnt[1].x;	Body[7].y = pnt[1].y;

	Body[3].x = (pnt[0].x + pnt[1].x) / 3;		Body[3].y = (pnt[0].y + pnt[1].y) / 3;
	Body[5].x = (pnt[0].x + pnt[1].x) / 3 * 2;	Body[5].y = (pnt[0].y + pnt[1].y) / 3 * 2;
	Body[2].x = (pnt[2].x + pnt[3].x) / 3;		Body[2].y = (pnt[2].y + pnt[3].y) / 3;
	Body[4].x = (pnt[2].x + pnt[3].x) / 3 * 2;	Body[4].y = (pnt[2].y + pnt[3].y) / 3 * 2;

	for (int i = 0; i < 8; i++) {
		Body[i].tu = Body[i].x / TEXTURESIZEW;
		Body[i].tv = Body[i].y / TEXTURESIZEH;
	}

	return Body;
}

void MakeLine(CUSTOMVERTEX pnt[], int s, int e, int per)
{
	float xl, yl;
	float base;
	float ang;

	xl = pnt[e].x - pnt[s].x;
	yl = pnt[e].y - pnt[s].y;

	base = sqrt(pow(xl, 2) + pow(yl, 2)) / 100.0f;

	ang = CalcAng(yl, xl);

	pnt[e].x += base * cos(ang) * per;
	pnt[e].y += base * sin(ang) * per;
	pnt[s].x -= base * cos(ang) * per;
	pnt[s].y -= base * sin(ang) * per;
}

void MakeBLine(CUSTOMVERTEX pnt[], int Per)	//Per % �Ŗc��܂���i�P�O�O�������̂܂܁j
{
	MakeLine(pnt, 2, 5, Per);
	MakeLine(pnt, 3, 4, Per);
}
int AnimeCtrl(PLAYERACT kind, bool init)
{
	if (init) {
		PlayerAct[kind].NowNo = 0;
		PlayerAct[kind].NowDispCnt = 0;
		PlayerAct[kind].dist = true;
	}
	else {
		if (++PlayerAct[kind].NowDispCnt > PlayerAct[kind].MaxDispCnt) {
			if (PlayerAct[kind].dist) {
				if (++PlayerAct[kind].NowNo > PlayerAct[kind].MaxNo) {
					if (PlayerAct[kind].DKind == ONEWAY) {
						PlayerAct[kind].NowNo = PlayerAct[kind].MinNo;
					}
					else {
						PlayerAct[kind].NowNo -= 2;
						PlayerAct[kind].dist = false;
					}
				}
			}
			else {
				if (--PlayerAct[kind].NowNo < PlayerAct[kind].MinNo) {
					PlayerAct[kind].NowNo += 2;
					PlayerAct[kind].dist = true;
				}
			}
			PlayerAct[kind].NowDispCnt = 0;
		}
	}
	return 0;
}

void PlayerDraw()
{
	int AnimeNo;

	CUSTOMVERTEX PlayerDraw[4]
	{
		{ 0.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 0.f }
	};

	CUSTOMVERTEX* cvpnt;

	AnimeNo = PlayerAct[PAction].NowNo;

	PlayerDraw[0].x = PlayerDraw[3].x = TextureBP[AnimeNo].x;
	PlayerDraw[1].x = PlayerDraw[2].x = TextureBP[AnimeNo].x + PLAYERW;
	PlayerDraw[0].y = PlayerDraw[1].y = TextureBP[AnimeNo].y;
	PlayerDraw[2].y = PlayerDraw[3].y = TextureBP[AnimeNo].y + PLAYERH;

	for (int i = 0; i < 4; i++)
	{
		PlayerDraw[i].tu = PlayerDraw[i].x / TEXTURESIZEW;
		PlayerDraw[i].tv = PlayerDraw[i].y / TEXTURESIZEH;
		PlayerDraw[i].x += g_playerstate.posX;
		PlayerDraw[i].y += g_playerstate.posY;
		PlayerDraw[i].x -= TextureBP[AnimeNo].x;
		PlayerDraw[i].y -= TextureBP[AnimeNo].y;
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

/////////////////////
	//////////////////////
	///////////////////////
	//�e�X�g
	static int cnt = 0;
	static int dper = 1;
	if (cnt++ > 10) {
		Pper += dper;
		cnt = 0;
	}
	if (Pper > 150 || Pper < 50) {
		dper *= -1;
	}
	/////////////////////
	//////////////////////




	if (g_key[UP] == PUSH && !g_playerstate.skyFlag)
	{
		g_playerstate.jumpFlag = true;
		g_playerstate.skyFlag = true;
		g_playerstate.a = JUMP_POWER;
		PAction = P_JUMP;
	}


	//�W�����v�������ɂ��̏����ɓ���
	if (g_playerstate.jumpFlag)
	{
		//�v���C���[�̉��̃}�b�v�`�b�v������
		int playerUpArrayY = int((g_playerstate.posY - 172) / TIPSIZE);
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

		int playerDownArrayY = int((g_playerstate.posY + 172) / TIPSIZE);

		if (map[playerDownArrayY][playerLeftDownArrayX] == 1 || map[playerDownArrayY][playerRightDownArrayX] == 1)
		{
			//�������łȂ��ƒ��n������s��Ȃ�
			if (g_playerstate.a > 0)
			{
				g_playerstate.jumpFlag = false;
				g_playerstate.skyFlag = false;
				PAction = P_RUN;
			}
		}
	}

	int playerDownArrayY = int((g_playerstate.posY + 172) / TIPSIZE);
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
			g_playerstate.posY = TIPSIZE * playerDownArrayY - 172;
			g_playerstate.a = 0.f;
			g_playerstate.skyFlag = false;
		}
	}

	AnimeCtrl(PAction, false);
}