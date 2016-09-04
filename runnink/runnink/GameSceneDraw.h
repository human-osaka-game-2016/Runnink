#ifndef GAME_SCENE_DRAW_H
#define GAME_SCENE_DRAW_H

#include <dx_lib.h>
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAP_HEIGHT 26
#define MAP_WIDTH 1873
#define TIPSIZE 32.f

extern CUSTOMVERTEX g_mapTip1[];

extern CUSTOMVERTEX g_mapTip2[];

enum TEXTURE
{
	BACKGROUND_TEX,
	MAP_GROUND_TEX,
	MAP_GROUND2_TEX,
	UICON1_TEX,
	PLAYER_TEX,
	SLIDING_TEX,
	S_TEX,
	M_TEX,
	L_TEX,
	ENEMY_TEX,
	FIRE_TEX,
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
void MapDraw();
void MapLoad(const char* mapdata);
void Init_Csv();
void UIRender();
void GameSceneFree();

#endif