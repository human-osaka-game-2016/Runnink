#define MOVESPEED 10
#define SCROOLSPEED 0.0005f
#define JUMP_POWER -15.f
#define GRAVITY 0.6f
#define BULLETMAX 3

struct PLAYERSTATE
{
	int  HP;
	float posX, posY;
	float dispPosX, dispPosY;
	//
	float a;
	bool animReverse;
	bool jumpFlag;
	bool skyFlag;
	//フラグ
	bool TitlehitFlag;//
	bool GameoverhitFlag;//
	bool BlackoutFlag;//
	bool GBlackoutFlag;//
};
struct TEXTSTATE
{
	float TposX, TposY;//
	float PEposX, PEposY;//
};

//シーンＩＤ
enum SceneID
{
	TitleScene,
	GameScene,
	GameOverScene,
};

//プレイヤーのシーンID
enum PlayerSceneID
{
	Normal,
	TitlePlayer,
	GamePlayer,
	GameOverPlayer,
};

extern SceneID g_scene;//

extern PlayerSceneID p_scene;//


extern KEYSTATE g_key[KEY_MAX];
extern PLAYERSTATE g_playerstate;//
extern TEXTSTATE g_textstate;//

void Control();
void PlayerControl();
//シーンを変える関数
void ChangeScene();//