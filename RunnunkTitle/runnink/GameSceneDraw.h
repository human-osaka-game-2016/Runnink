#ifndef GAME_SCENE_DRAW_H
#define GAME_SCENE_DRAW_H

#include <dx_lib.h>
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAP_HEIGHT 15
#define MAP_WIDTH 40
#define TIPSIZE 64.f

extern CUSTOMVERTEX g_mapTip1[];

extern CUSTOMVERTEX g_mapTip2[];

//�ǉ��_
extern CUSTOMVERTEX hitflg[];

enum TEXTURE
{
	TITLE_TEX,//�ǉ��_
	BACKGROUND_TEX,
	MAP_GROUND_TEX,
	MAP_GROUND2_TEX,
	UICON1_TEX,
	PLAYER_TEX,
	PLAYER_DEATH_TEX,//�ǉ��_
	HIT_FLG,//�ǉ��_
	S_TEX,
	M_TEX,
	L_TEX,
	TEXTURE_MAX,
	//�ǉ��_
	GAMEOVER_TEXT,
	PUSHENTER_TEXT,
	TITLE_TEXT,
	//�����܂�
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
void titlescene();//�ǉ��_
void HitFlag();//�ǉ��_
void TextDraw();//�ǉ��_
void MapDraw();
void MapLoad(const char* mapdata);
void GameSceneFree();
void Init_Csv();
void UIRender();

#endif