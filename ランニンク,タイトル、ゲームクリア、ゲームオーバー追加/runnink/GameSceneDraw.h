#ifndef GAME_SCENE_DRAW_H
#define GAME_SCENE_DRAW_H

#include <dx_lib.h>
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAP_HEIGHT 26
#define MAP_WIDTH 1873
#define TIPSIZE 32.f

extern CUSTOMVERTEX g_mapTip1[];

extern CUSTOMVERTEX g_mapTip2[];

//追加点
extern CUSTOMVERTEX hitflg[];

enum TEXTURE
{
	TITLE_TEX,//追加点
	BACKGROUND_TEX,
	MAP_GROUND_TEX,
	MAP_GROUND2_TEX,
	UICON1_TEX,
	PLAYER_TEX,
	SLIDING_TEX,
	PLAYER_DEATH_TEX,//追加点
	HIT_FLG,//追加点
	S_TEX,
	M_TEX,
	L_TEX,
	ENEMY_TEX,
	FIRE_TEX,
	//tu
	GAMEOVER_TEXT,
	PUSHENTER_TEXT,
	TITLE_TEXT,
	//ゲームクリア画面追加点
	GAMECLEAR_TEXT,
	BACKTITLE_TEXT,
	GOCREDIT_TEXT,
	//クレジット画面追加点
	TEAM_LOGO,
	STAFF1,
	STAFF2,
	STAFF3,
	STAFF4,
	STAFF5,
	STAFF6,
	STAFF7,
	STAFF8,
	STAFF9,
	STAFF10,
	STAFF11,
	STAFF12,
	STAFF13,
	STAFF14,
	STAFF15,
	//ここまで
	TEXTURE_MAX,
};

typedef struct
{
	float UI_posX, UI_posY;
}UISTATE;


extern LPDIRECT3DTEXTURE9			g_pGameTexture[TEXTURE_MAX];
extern int map[MAP_HEIGHT][MAP_WIDTH];

void Render();
void PlayerDraw();
void PlayerControl();
void PlayerSliding();
void PlayerPunch();
void titlescene();//追加点
void HitFlag();//追加点
void TextDraw();//追加点
void MapDraw();
void MapLoad(const char* mapdata);
void Init_Csv();
void UIRender();
void GameSceneFree();

#endif