#define MOVESPEED 10
#define SCROOLSPEED 0.0005f
#define JUMP_POWER -15.f
#define GRAVITY 0.6f

struct PLAYERSTATE
{
	int  HP;
	float posX, posY;
	float dispPosX, dispPosY;
	float deathPX, deathPY;//追加点
	//
	float a;
	bool animReverse;
	bool jumpFlag;
	bool slidingFlag;
	bool PunchFlag;
	bool skyFlag;
	bool SceneHitFlag;//追加点
};
//追加点
struct TEXTSTATE
{
	float TposX, TposY;
	float SposX, SposY;
	float LogoposY;
};
//シーンＩＤ 追加点
enum SceneID
{
	TitleScene,
	GameScene,
	GameOverScene,
	GameClearScene,
	GameCreditScene,
};

//プレイヤーのシーンID 追加点
enum PlayerSceneID
{
	Normal,
	TitlePlayer,
	GamePlayer,
	GameOverPlayer,
	GameClearPlayer,
};

extern SceneID g_scene;//追加点


extern PlayerSceneID p_scene;//追加点

extern KEYSTATE g_key[KEY_MAX];
extern PLAYERSTATE g_playerstate;
extern TEXTSTATE g_textstate;//追加点

void Control();
void PlayerControl();

//シーンを変える関数 追加点
void ChangeScene();