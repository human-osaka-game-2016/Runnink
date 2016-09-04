#define MOVESPEED 10
#define SCROOLSPEED 0.0005f
#define JUMP_POWER -15.f
#define GRAVITY 0.6f

struct PLAYERSTATE
{
	int  HP;
	float posX, posY;
	float dispPosX, dispPosY;
	//
	float a;
	bool animReverse;
	bool jumpFlag;
	bool slidingFlag;
	bool PunchFlag;
	bool skyFlag;
};


extern KEYSTATE g_key[KEY_MAX];
extern PLAYERSTATE g_playerstate;

void Control();
void PlayerControl();