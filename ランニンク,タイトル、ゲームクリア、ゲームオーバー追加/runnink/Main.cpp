#include <windows.h>
#include <d3d9.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

#define WINDOW_W 1280					// ウィンドウ幅
#define WINDOW_H 720					// ウィンドウ高さ
#define WINDOW_TITLE TEXT("Runnink")	// ウィンドウ名
//#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

//LPDIRECT3D9			g_pDirect3D = NULL;		// DirectXオブジェクトのポインタ
//LPDIRECT3DDEVICE9	g_pDirect3DDevice = NULL;	// DirectXデバイスのポインタ
//D3DDISPLAYMODE		g_D3DdisplayMode;
//D3DPRESENT_PARAMETERS D3dPre5sentParameters;

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, mes, wParam, lParam);
}


// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//---------------------------------------------------------------------
	//							ウィンドウ生成処理
	//---------------------------------------------------------------------

	MSG msg;			// メッセージを格納する構造体
	HWND hWnd;			// ウィンドウハンドル
	WNDCLASS winc;

	//Windows情報の設定
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOW_TITLE;	//クラス名

	//Windowの登録
	if (!RegisterClass(&winc)) return 0;
	//Windowの生成
	hWnd = CreateWindow(
		WINDOW_TITLE,						//ウィンドウのクラス名
		WINDOW_TITLE, 						//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WINDOW_W,							// Width（幅）
		WINDOW_H,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
		);
	if (!hWnd) return 0;


	ShowWindow(hWnd, SW_SHOW);		

	InitDirect3D(hWnd);		//dx_Initから関数呼び出し

	Init_Tex();		//dx_Initから関数呼び出し

	Init_Dinput();
	Init_Dinput_Key( hWnd);

	// DisplayModeの取得
	pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&D3DdisplayMode);

	RoadTex("background.png", &g_pGameTexture[BACKGROUND_TEX]); //画像の読み込み、RoadTexはdx_texから関数呼び出し

	RoadTex("Player.png", &g_pGameTexture[PLAYER_TEX]);

	RoadTex("Block03.png", &g_pGameTexture[MAP_GROUND_TEX]);

	RoadTex("Block02.png", &g_pGameTexture[MAP_GROUND2_TEX]);

	RoadTex("U,01,I,01.png", &g_pGameTexture[UICON1_TEX]);

	RoadTex("インク瓶完成.png", &g_pGameTexture[SLIDING_TEX]);

	RoadTex("インクバーS.png", &g_pGameTexture[S_TEX]);
	
	RoadTex("インクバーM.png", &g_pGameTexture[M_TEX]);

	RoadTex("インクバーL.png", &g_pGameTexture[L_TEX]);

	RoadTex("En2,03,M,1.png", &g_pGameTexture[ENEMY_TEX]);

	RoadTexEx("fire.png", &g_pGameTexture[FIRE_TEX], 255, 0, 255, 0, true);


	//追加点
	//タイトル画像
	RoadTex("T,H.png", &g_pGameTexture[TITLE_TEX]);//画像の読み込み、RoadTexはdx_texから関数呼び出し
	RoadTex("C,03,P.png", &g_pGameTexture[PUSHENTER_TEXT]);
	RoadTex("T,01,R,01.png", &g_pGameTexture[TITLE_TEXT]);
	//衝突判定用
	RoadTex("white.png", &g_pGameTexture[HIT_FLG]);//
	//ゲームオーバー画像
	RoadTex("G,02,G,01.png", &g_pGameTexture[GAMEOVER_TEXT]);
	RoadTex("G,02,G,02.png", &g_pGameTexture[PLAYER_DEATH_TEX]);
	//ゲームクリア画面
	RoadTex("C,03,C.png", &g_pGameTexture[GAMECLEAR_TEXT]);
	RoadTex("C,03,E.png", &g_pGameTexture[BACKTITLE_TEXT]);
	RoadTex("C,03,S.png", &g_pGameTexture[GOCREDIT_TEXT]);
	//スタッフロール
	/*
	CG Kazuki Yamaguchi.png
	CG Yuna Kohigashi.png
	CG Takuya Kotera.png
	CG Ryou Yasunaga.png
	PG Takuma Ueno.png
	PG Fumihiro Irino.png
	PG Kenta Kumagai.png
	PG Ryouya Ichikawa.png
	PG Shouhei Sumikura.png
	PG Yuto Morioka.png
	PL Hayata Nagayoshi.png
	PL Michiya Hamamoto.png
	PL Nobuhiro Iwatuki.png
	PL Norikazu Kawakami.png
	PL So Minamikawa.png
	*/
	RoadTex("チームロゴ修正版.png", &g_pGameTexture[TEAM_LOGO]);
	RoadTex("CG Kazuki Yamaguchi.png", &g_pGameTexture[STAFF1]);
	RoadTex("CG Yuna Kohigashi.png", &g_pGameTexture[STAFF2]);
	RoadTex("CG Takuya Kotera.png", &g_pGameTexture[STAFF3]);
	RoadTex("CG Ryou Yasunaga.png", &g_pGameTexture[STAFF4]);
	RoadTex("PG Takuma Ueno.png", &g_pGameTexture[STAFF5]);
	RoadTex("PG Fumihiro Irino.png", &g_pGameTexture[STAFF6]);
	RoadTex("PG Kenta Kumagai.png", &g_pGameTexture[STAFF7]);
	RoadTex("PG Ryouya Ichikawa.png", &g_pGameTexture[STAFF8]);
	RoadTex("PG Shouhei Sumikura.png", &g_pGameTexture[STAFF9]);
	RoadTex("PG Yuto Morioka.png", &g_pGameTexture[STAFF10]);
	RoadTex("PL Hayata Nagayoshi.png", &g_pGameTexture[STAFF11]);
	RoadTex("PL Michiya Hamamoto.png", &g_pGameTexture[STAFF12]);
	RoadTex("PL Nobuhiro Iwatuki.png", &g_pGameTexture[STAFF13]);
	RoadTex("PL Norikazu Kawakami.png", &g_pGameTexture[STAFF14]);
	RoadTex("PL So Minamikawa.png", &g_pGameTexture[STAFF15]);
	//	RoadTex("", &g_pGameTexture[]);

	//ここまで


	Init_Csv();

	//追加点 deathPX 0.0f, deathPY 335.f, SceneHitFlag false
	g_playerstate = { 1, 210.f, 300.f, false, false, 0.f, 335.f, 0, false, false, false, false, false, false ,};//プレイヤーの指定座標
	//追加点
	g_textstate = { 0.f, 0.f,0.f };

	//---------------------------------------------------------------------
	//							ゲームループ
	//---------------------------------------------------------------------


	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) //	1秒間に60回この中に入る
			{

				Render();
				Control();
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	GameSceneFree();				// ゲームシーンの解放関数

	pD3Device->Release();	// DirectXのデバイスの解放
	pDirect3D->Release();			// DirectXオブジェクトの解放

	return (int)msg.wParam;
}
