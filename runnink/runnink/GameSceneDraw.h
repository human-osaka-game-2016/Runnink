#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAP_HEIGHT 23
#define MAP_WIDTH 105
#define TIPSIZE 64.f

extern CUSTOMVERTEX g_mapTip1[];

enum TEXTURE
{
	BACKGROUND_TEX,
	MAP_GROUND_TEX,
	PLAYER_TEX,
	TEXTURE_MAX
};

extern LPDIRECT3DTEXTURE9			g_pGameTexture[TEXTURE_MAX];
extern int map[MAP_HEIGHT][MAP_WIDTH];

void Render();
void PlayerDraw();
void PlayerControl();
void MapDraw();
void MapLoad(const char* mapdata);
void GameSceneFree();