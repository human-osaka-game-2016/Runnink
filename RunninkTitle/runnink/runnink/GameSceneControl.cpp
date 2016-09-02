#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneControl.h"

KEYSTATE g_key[KEY_MAX];

PLAYERSTATE g_playerstate;

SceneID g_scene = TitleScene;//

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
	KeyCheck(&g_key[RETURN], DIK_RETURN);//

	//�V�[����ς���
	ChangeScene();

	PlayerControl();

}

//�V�[����ς���
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
			p_scene = GameOverPlayer;//
		}
	}

}