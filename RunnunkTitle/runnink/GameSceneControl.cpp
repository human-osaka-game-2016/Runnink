#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneControl.h"
#include "UI.h"

KEYSTATE g_key[KEY_MAX];

PLAYERSTATE g_playerstate;

//�ǉ��_
SceneID g_scene = TitleScene;

void Control()
{
	KeyCheck(&g_key[LEFT], DIK_LEFT);
	KeyCheck(&g_key[RIGHT], DIK_RIGHT);
	KeyCheck(&g_key[UP], DIK_UP);
	KeyCheck(&g_key[DOWN], DIK_DOWN);
	KeyCheck(&g_key[SPACE], DIK_SPACE);
	KeyCheck(&g_key[Z], DIK_Z);
	KeyCheck(&g_key[X], DIK_X);
	KeyCheck(&g_key[C], DIK_C);
	KeyCheck(&g_key[RETURN], DIK_RETURN);//�ǉ��_

	//�V�[����ς���@�ǉ��_
	ChangeScene();

	UIDATE();
	PlayerControl();

}

//�V�[����ς���@�ǉ��_
void ChangeScene()
{

	//�^�C�g������Q�[����ʂ�
	if (g_key[RETURN] == ON)
	{

		p_scene = TitlePlayer;
	}
	//�Q�[����ʂ���Q�[���I�[�o�[��
	if (g_scene == GameScene)
	{
		/*�e�X�g�p�@�����Ă��\��Ȃ�*/
		if (g_key[Z] == ON)//�e�X�g��Z
		{
			g_scene = GameOverScene;
		}
	}



	if (g_scene == GameOverScene)
	{
		if (g_key[RETURN] == ON)//�Q�[���I�[�o�[��ʃe�X�g�p
		{
			//		g_scene = TitleScene;//�m�F�p
			p_scene = GameOverPlayer;
		}
	}

}//�����܂�