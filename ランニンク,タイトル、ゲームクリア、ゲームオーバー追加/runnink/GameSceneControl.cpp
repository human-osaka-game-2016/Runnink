#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneControl.h"
#include "UI.h"
#include "Enemy.h"

KEYSTATE g_key[KEY_MAX];

PLAYERSTATE g_playerstate;

//追加点
SceneID g_scene = TitleScene;
void Control()
{
	KeyCheck(&g_key[LEFT], DIK_LEFT);
	KeyCheck(&g_key[RIGHT], DIK_RIGHT);
	KeyCheck(&g_key[UP], DIK_UP);
	KeyCheck(&g_key[DOWN], DIK_DOWN);
	KeyCheck(&g_key[SPACE], DIK_SPACE);
	KeyCheck(&g_key[RETURN], DIK_RETURN);//追加点
	KeyCheck(&g_key[Z], DIK_Z);
	KeyCheck(&g_key[X], DIK_X);
	KeyCheck(&g_key[C], DIK_C);
	KeyCheck(&g_key[M], DIK_M);

	//----------------------------------
	//
	//	デバッグ用コマンド
	//
	//---------------------------------

	KeyCheck(&g_key[L], DIK_L);
	KeyCheck(&g_key[K], DIK_K);
	KeyCheck(&g_key[A], DIK_A);

	//シーンを変える　追加点
	ChangeScene();

	Comand();

	UIDATE();
	PlayerControl();


}

//シーンを変える　追加点
void ChangeScene()
{

	//タイトルからゲーム画面へ
	if (g_key[RETURN] == ON && g_scene != GameScene)
	{
	p_scene = TitlePlayer;
	}
	//ゲーム画面からゲームオーバー、またはゲームクリアへ
	/*テスト用　消しても構わない*/
	if (g_scene == GameScene)
	{

		if (g_key[Z] == ON)//テストでZ
		{
			g_scene = GameOverScene;
		}
		if (g_key[X] == ON)//テストでX
		{
			g_scene = GameClearScene;
		}
	}



	if (g_scene == GameOverScene)
	{
		if (g_key[RETURN] == ON && g_scene != GameScene)
		{
			p_scene = GameOverPlayer;
		}
	}
	if (g_scene == GameClearScene)
	{
		if (g_key[RETURN] == ON && g_scene != GameScene)//ゲームクリア画面テスト用
		{
			p_scene = GameClearPlayer;
		}
		if (g_key[SPACE] == ON && g_scene != GameScene)//ゲームクリア画面テスト用
		{
			g_scene = GameCreditScene;
		}
	}

}//ここまで