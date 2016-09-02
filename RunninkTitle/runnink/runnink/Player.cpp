#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"
#include "player.h"

//�v���C���[�̕`��V�[��
PlayerSceneID p_scene = Normal;//

float CalcAng(float y, float x) {
	float ang;

	ang = atan2(-y, x);
	if (y > 0.0f) {
		ang += D3DX_PI * 2;
	}

	return ang;
}

void MakeV(VPos pnt[], CUSTOMVERTEX Body[])		//�S�_���o�[�e�b�N�X���쐬
{
	for (int i = 0; i < 8; i++) {
		Body[i].z = 0.5f;
		Body[i].rhw = 1.0f;
		Body[i].color = 0xFFFFFFFF;
	}
	Body[0].x = pnt[0].x;	Body[0].y = pnt[0].y;
	Body[1].x = pnt[1].x;	Body[1].y = pnt[1].y;
	Body[6].x = pnt[3].x;	Body[6].y = pnt[3].y;
	Body[7].x = pnt[2].x;	Body[7].y = pnt[2].y;

	Body[3].x = (pnt[1].x * 2 + pnt[2].x) / 3;	Body[3].y = (pnt[1].y * 2 + pnt[2].y) / 3;
	Body[5].x = (pnt[1].x + pnt[2].x * 2) / 3;	Body[5].y = (pnt[1].y + pnt[2].y * 2) / 3;
	Body[2].x = (pnt[0].x * 2 + pnt[3].x) / 3;	Body[2].y = (pnt[0].y * 2 + pnt[3].y) / 3;
	Body[4].x = (pnt[0].x + pnt[3].x * 2) / 3;	Body[4].y = (pnt[0].y + pnt[3].y * 2) / 3;

	for (int i = 0; i < 8; i++) {
		Body[i].tu = Body[i].x / TEXTURESIZEW;
		Body[i].tv = Body[i].y / TEXTURESIZEH;
	}
}

void MakeLine(CUSTOMVERTEX pnt[], int s, int e, int per)
{
	float xl, yl;
	float base;
	float ang;
	float pt;

	xl = pnt[e].x - pnt[s].x;
	yl = pnt[e].y - pnt[s].y;

	base = sqrt(pow(xl, 2) + pow(yl, 2));

	ang = CalcAng(yl, xl);
	pt = (per - 100) / 100.0f;

	pnt[e].x += base * cos(ang) * pt;
	pnt[e].y -= base * sin(ang) * pt;
	pnt[s].x -= base * cos(ang) * pt;
	pnt[s].y += base * sin(ang) * pt;
}

void MakeBLine(CUSTOMVERTEX pnt[], int Per)	//Per % �Ŗc��܂���i�P�O�O�������̂܂܁j
{
	MakeLine(pnt, 2, 3, Per);
	MakeLine(pnt, 4, 5, Per);
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

void SetNowPnt(int Ano, CUSTOMVERTEX* pnt)
{
	for (int i = 0; i < 8; i++)
	{
		pnt[i].x += g_playerstate.posX;
		pnt[i].y += g_playerstate.posY;
		pnt[i].x -= TextureBP[Ano].x;
		pnt[i].y -= TextureBP[Ano].y;
	}

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

	CUSTOMVERTEX cvpnt[8];

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

	for (int i = 0; i < 4; i++)//
	{
		if (PlayerDraw[i].x == hitflg[i].x)//PlayerDraw.x��hitflg.x�Ɠ�������
		{
			g_playerstate.TitlehitFlag = true;
		}
	}//
	switch (g_scene)
	{
	case TitleScene:
		SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);
		break;
	case GameScene:
		g_playerstate.posX = 200;
		g_playerstate.posY = 280;
		SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);
		break;
	case GameOverScene:

		g_playerstate.posY = 320;
		if (g_playerstate.posX != 600)
		{
			g_playerstate.posX += 10;
		}
		if (p_scene != GameOverPlayer)
		{
			SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);
			//				SetGameScene(g_pGameTexture[PLAYER_DEATH_TEX], PlayerDraw);//
		}
		else
		{
			SetGameScene(g_pGameTexture[PLAYER_TEX], PlayerDraw);
		}

		break;
	}
	//�v���C���[�̃V�[���Ǘ�
	switch (p_scene)
	{
	case TitlePlayer:
		g_playerstate.posX += 11;
		break;
	case GamePlayer:

		break;
	case GameOverPlayer:

		break;
	}


//�葫�̕`��
	for (int part = 0; part < 8; part++) {
		if (PBody[AnimeNo].Vertex[part][0].x == 0.0f && PBody[AnimeNo].Vertex[part][0].y == 0.0f) {
			continue;
		}
		MakeV(PBody[AnimeNo].Vertex[part], cvpnt);	//�葫�p�̒��_�����
		SetNowPnt(AnimeNo, cvpnt);

		MakeBLine(cvpnt, Pper[part / 4]);
		pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 6, cvpnt, sizeof(CUSTOMVERTEX));

	}

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

	if (g_playerstate.dispPosX == 420.f)
	{
		g_playerstate.dispPosX += MOVESPEED;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			g_mapTip1[i].x -= MOVESPEED;
			g_mapTip2[i].x -= MOVESPEED;
		}
	}

/////////////////////
	//////////////////////
	///////////////////////
	//�e�X�g
	static int cnt = 0;
	static int dper[2] = { 3, 2 };
	if (cnt++ > 1) {
		Pper[0] += dper[0];
		Pper[1] += dper[1];
		cnt = 0;
	}
	if (Pper[0] > 150 || Pper[0] < 80) {
		dper[0] *= -1;
	}
	if (Pper[1] > 150 || Pper[1] < 80) {
		dper[1] *= -1;
	}
	/////////////////////
	//////////////////////




	if (g_key[SPACE] == PUSH && !g_playerstate.skyFlag)
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
				PAction = P_RUN;
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

	AnimeCtrl(PAction, false);
}