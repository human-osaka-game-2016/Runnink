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

	//RoadTex("chara.png", &g_pGameTexture[PLAYER_TEX]);

	RoadTex("Player.png", &g_pGameTexture[PLAYER_TEX]);

	RoadTex("Block03.png", &g_pGameTexture[MAP_GROUND_TEX]);

	RoadTex("Block02.png", &g_pGameTexture[MAP_GROUND2_TEX]);

	RoadTex("U,01,I,01.png", &g_pGameTexture[UICON1_TEX]);

	RoadTex("インクバーS.png", &g_pGameTexture[S_TEX]);
	
	RoadTex("インクバーM.png", &g_pGameTexture[M_TEX]);

	RoadTex("インクバーL.png", &g_pGameTexture[L_TEX]);

	//RoadTex("", &g_GameTexture[];);


	Init_Csv();

	g_playerstate = { 1, 210.f, 335.f, false, false, 0, false, false, false };


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
