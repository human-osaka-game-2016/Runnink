#define TEXTURESIZEW (1024.0f)
#define TEXTURESIZEH (1024.0f)
#define PLAYERW (160.0f)
#define PLAYERH (172.0f)

enum ANIKIND {
	RUN1,
	RUN2,
	RUN3,
	ATTACK1,
	ATTACK2,
	JUMP,
	SLIDING,
	ANIKINDMAX
};

enum PLAYERACT {
	P_RUN,
	P_ATTACK,
	P_JUMP,
	P_SLIDING,
	P_ACTMAX
};

struct VPos {
	float x;
	float y;
};

VPos TextureBP[] = {
	{    0.0f,   0.0f },
	{  160.0f,   0.0f },
	{  320.0f,   0.0f },
	{  480.0f,   0.0f },
	{  640.0f,   0.0f },
	{  800.0f,   0.0f },
	{  160.0f, 172.0f },
};

struct BodyInfo {
	VPos Vertex[8][4];
};

BodyInfo PBody[ANIKINDMAX] =
{
	{ {
		{ { 95.0f, 28.0f }, { 88.0f, 45.0f }, { 72.0f, 47.0f }, { 61.0f, 35.0f } },
		{ { 61.0f, 35.0f }, { 72.0f, 47.0f }, { 67.0f, 60.0f }, { 57.0f, 60.0f } },
		{ { 115.0f, 69.0f }, { 125.0f, 53.0f }, { 134.0f, 66.0f }, { 135.0f, 88.0f } },
		{ { 135.0f, 88.0f }, { 134.0f, 66.0f }, { 138.0f, 59.0f }, { 149.0f, 65.0f } },
		{ { 69.0f, 85.0f }, { 83.0f, 110.0f }, { 56.0f, 126.0f }, { 56.0f, 106.0f } },
		{ { 56.0f, 106.0f }, { 56.0f, 126.0f }, { 24.0f, 108.0f }, { 26.0f, 95.0f } },
		{ { 83.0f, 110.0f }, { 99.0f, 90.0f }, { 116.0f, 127.0f }, { 100.0f, 137.0f } },
		{ { 100.0f, 137.0f }, { 116.0f, 127.0f }, { 130.0f, 160.0f }, { 121.0f, 168.0f } },
	}, },

	{ {
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 247.0f, 88.0f }, { 249.0f, 83.0f }, { 252.0f, 84.0f }, { 251.0f, 92.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 244.0f, 96.0f }, { 247.0f, 89.0f }, { 253.0f, 94.0f }, { 250.0f, 101.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 239.0f, 129.0f }, { 233.0f, 140.0f }, { 221.0f, 136.0f }, { 224.0f, 126.0f } },
		{ { 218.0f, 107.0f }, { 242.0f, 97.0f }, { 260.0f, 136.0f }, { 239.0f, 129.0f } },
		{ { 239.0f, 129.0f }, { 260.0f, 136.0f }, { 239.0f, 165.0f }, { 223.0f, 161.0f } },
	}, },

	{ {
		{ { 403.0f, 25.0f }, { 394.0f, 40.0f }, { 383.0f, 40.0f }, { 380.0f, 27.0f } },
		{ { 380.0f, 27.0f }, { 383.0f, 40.0f }, { 374.0f, 48.0f }, { 364.0f, 43.0f } },
		{ { 422.0f, 50.0f }, { 427.0f, 33.0f }, { 441.0f, 39.0f }, { 445.0f, 54.0f } },
		{ { 445.0f, 54.0f }, { 441.0f, 39.0f }, { 449.0f, 29.0f }, { 459.0f, 32.0f } },
		{ { 375.0f, 83.0f }, { 396.0f, 93.0f }, { 372.0f, 127.0f }, { 360.0f, 115.0f } },
		{ { 360.0f, 115.0f }, { 372.0f, 127.0f }, { 352.0f, 151.0f }, { 340.0f, 142.0f } },
		{ { 396.0f, 93.0f }, { 407.0f, 70.0f }, { 445.0f, 110.0f }, { 413.0f, 102.0f } },
		{ { 413.0f, 102.0f }, { 445.0f, 10.0f }, { 402.0f, 123.0f }, { 397.0f, 113.0f } },
	}, },

	{ {
		{ { 560.0f, 28.0f }, { 545.0f, 46.0f }, { 521.0f, 39.0f }, { 546.0f, 29.0f } },
		{ { 546.0f, 29.0f }, { 521.0f, 39.0f }, { 539.0f, 21.0f }, { 546.0f, 29.0f } },
		{ { 586.0f, 59.0f }, { 587.0f, 40.0f }, { 598.0f, 49.0f }, { 620.0f, 69.0f } },
		{ { 620.0f, 69.0f }, { 598.0f, 40.0f }, { 598.0f, 49.0f }, { 620.0f, 69.0f } },
		{ { 545.0f, 93.0f }, { 567.0f, 103.0f }, { 545.0f, 134.0f }, { 531.0f, 120.0f } },
		{ { 531.0f, 120.0f }, { 545.0f, 134.0f }, { 515.0f, 156.0f }, { 505.0f, 147.0f } },
		{ { 567.0f, 103.0f }, { 581.0f, 76.0f }, { 618.0f, 124.0f }, { 587.0f, 115.0f } },
		{ { 587.0f, 115.0f }, { 618.0f, 124.0f }, { 574.0f, 135.0f }, { 567.0f, 124.0f } },
	}, },

	{ {
		{ { 707.0f, 34.0f }, { 697.0f, 52.0f }, { 687.0f, 47.0f }, { 676.0f, 36.0f } },
		{ { 676.0f, 36.0f }, { 687.0f, 47.0f }, { 687.0f, 47.0f }, { 674.0f, 53.0f } },
		{ { 738.0f, 62.0f }, { 747.0f, 45.0f }, { 766.0f, 48.0f }, { 757.0f, 62.0f } },
		{ { 757.0f, 62.0f }, { 766.0f, 48.0f }, { 782.0f, 51.0f }, { 776.0f, 61.0f } },
		{ { 685.0f, 99.0f }, { 707.0f, 117.0f }, { 701.0f, 132.0f }, { 683.0f, 131.0f } },
		{ { 683.0f, 131.0f }, { 685.0f, 149.0f }, { 668.0f, 157.0f }, { 658.0f, 143.0f } },
		{ { 707.0f, 117.0f }, { 715.0f, 85.0f }, { 743.0f, 142.0f }, { 712.0f, 124.0f } },
		{ { 712.0f, 124.0f }, { 743.0f, 142.0f }, { 700.0f, 143.0f }, { 703.0f, 129.0f } },
	}, },

	{ {
		{ { 886.0f, 70.0f }, { 872.0f, 84.0f }, { 862.0f, 82.0f }, { 858.0f, 69.0f } },
		{ { 858.0f, 69.0f }, { 862.0f, 82.0f }, { 847.0f, 91.0f }, { 840.0f, 82.0f } },
		{ { 901.0f, 102.0f }, { 907.0f, 85.0f }, { 921.0f, 94.0f }, { 922.0f, 112.0f } },
		{ { 922.0f, 112.0f }, { 921.0f, 94.0f }, { 932.0f, 85.0f }, { 943.0f, 90.0f } },
		{ { 845.0f, 129.0f }, { 872.0f, 137.0f }, { 849.0f, 176.0f }, { 841.0f, 152.0f } },
		{ { 841.0f, 152.0f }, { 849.0f, 176.0f }, { 816.0f, 153.0f }, { 821.0f, 141.0f } },
		{ { 872.0f, 137.0f }, { 885.0f, 111.0f }, { 920.0f, 112.0f }, { 912.0f, 131.0f } },
		{ { 912.0f, 131.0f }, { 920.0f, 112.0f }, { 946.0f, 134.0f }, { 941.0f, 147.0f } },
	}, },

	{ {
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
	}, },

};

enum DISPKIND {
	ONEWAY,
	ROUND,
	DISPKINDMAX
};

struct ANICTRL {
	int NowNo;
	int MinNo;
	int MaxNo;
	int MaxDispCnt;
	int NowDispCnt;
	DISPKIND DKind;
	bool dist;
};

ANICTRL PlayerAct[P_ACTMAX] = {
	{ 0, 0, 2, 10, 0, ONEWAY, true },	//P_RUN,
	{ 0, 0, 2, 20, 0, ONEWAY, true },	//P_ATTACK,
	{ 5, 5, 5, 20, 0, ONEWAY, true },	//P_JUMP,
	{ 0, 0, 1, 20, 0, ONEWAY, true },	//P_SLIDING,
};

PLAYERACT PAction = P_RUN;
int Pper[2] = { 100, 100 };


CUSTOMVERTEX* MakeV(VPos pnt[]);		//４点よりバーテックスを作成
void MakeBLine(CUSTOMVERTEX pnt[], int Per);	//Per % で膨らませる（１００％がそのまま）
void PlayerDraw(void);
int AnimeCtrl(PLAYERACT kind, bool init = false);

void MapDraw();
