#include <d3d9.h>
#include <d3dx9.h>
#include <dx_lib.h>
#include "GameSceneControl.h"
#include "UI.h"
#include "Enemy.h"

KEYSTATE g_key[KEY_MAX];

PLAYERSTATE g_playerstate;

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
	KeyCheck(&g_key[M], DIK_M);

	//----------------------------------
	//
	//	デバッグ用コマンド
	//
	//---------------------------------

	KeyCheck(&g_key[L], DIK_L);
	KeyCheck(&g_key[K], DIK_K);
	KeyCheck(&g_key[A], DIK_A);

	Comand();

	UIDATE();
	PlayerControl();


}
