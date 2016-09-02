#include <windows.h>
#include <d3d9.h>
#include <dx_lib.h>
#include "GameSceneDraw.h"
#include "GameSceneControl.h"

#define WINDOW_W 1280					// �E�B���h�E��
#define WINDOW_H 720					// �E�B���h�E����
#define WINDOW_TITLE TEXT("Runnink")	// �E�B���h�E��
//#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

//LPDIRECT3D9			g_pDirect3D = NULL;		// DirectX�I�u�W�F�N�g�̃|�C���^
//LPDIRECT3DDEVICE9	g_pDirect3DDevice = NULL;	// DirectX�f�o�C�X�̃|�C���^
//D3DDISPLAYMODE		g_D3DdisplayMode;
//D3DPRESENT_PARAMETERS D3dPre5sentParameters;

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, mes, wParam, lParam);
}


// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//---------------------------------------------------------------------
	//							�E�B���h�E��������
	//---------------------------------------------------------------------

	MSG msg;			// ���b�Z�[�W���i�[����\����
	HWND hWnd;			// �E�B���h�E�n���h��
	WNDCLASS winc;

	//Windows���̐ݒ�
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOW_TITLE;	//�N���X��

	//Window�̓o�^
	if (!RegisterClass(&winc)) return 0;
	//Window�̐���
	hWnd = CreateWindow(
		WINDOW_TITLE,						//�E�B���h�E�̃N���X��
		WINDOW_TITLE, 						//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		WINDOW_W,							// Width�i���j
		WINDOW_H,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
		);
	if (!hWnd) return 0;


	ShowWindow(hWnd, SW_SHOW);		

	InitDirect3D(hWnd);		//dx_Init����֐��Ăяo��

	Init_Tex();		//dx_Init����֐��Ăяo��

	Init_Dinput();
	Init_Dinput_Key( hWnd);

	// DisplayMode�̎擾
	pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&D3DdisplayMode);

	RoadTex("background.png", &g_pGameTexture[BACKGROUND_TEX]); //�摜�̓ǂݍ��݁ARoadTex��dx_tex����֐��Ăяo��

	//RoadTex("chara.png", &g_pGameTexture[PLAYER_TEX]);

	RoadTex("Player.png", &g_pGameTexture[PLAYER_TEX]);

	RoadTex("Block03.png", &g_pGameTexture[MAP_GROUND_TEX]);

	RoadTex("Block02.png", &g_pGameTexture[MAP_GROUND2_TEX]);

	RoadTex("U,01,I,01.png", &g_pGameTexture[UICON1_TEX]);

	RoadTex("�C���N�o�[S.png", &g_pGameTexture[S_TEX]);
	
	RoadTex("�C���N�o�[M.png", &g_pGameTexture[M_TEX]);

	RoadTex("�C���N�o�[L.png", &g_pGameTexture[L_TEX]);

	RoadTex("T,H.png", &g_pGameTexture[TITLE_TEX]);//
	RoadTex("C,03,P.png", &g_pGameTexture[PUSHENTER_TEXT]);
	RoadTex("T,01,R,01.png", &g_pGameTexture[TITLE_TEXT]);
	RoadTex("white.png", &g_pGameTexture[HIT_FLG]);
	RoadTex("G,02,G,01.png", &g_pGameTexture[GAMEOVER_TEXT]);
	RoadTex("G,02,G,02.png", &g_pGameTexture[PLAYER_DEATH_TEX]);//


	//RoadTex("", &g_GameTexture[];);


	Init_Csv();

	g_playerstate = { 1, 210.f, 335.f, false, false, 0, false, false, false, false, false,true,true };//
	g_textstate = { 0.f,0.f,0.f,0.f };//

	//---------------------------------------------------------------------
	//							�Q�[�����[�v
	//---------------------------------------------------------------------


	DWORD SyncOld = timeGetTime();	//	�V�X�e�����Ԃ��擾
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
			if (SyncNow - SyncOld >= 1000 / 60) //	1�b�Ԃ�60�񂱂̒��ɓ���
			{

				Render();
				Control();
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	GameSceneFree();				// �Q�[���V�[���̉���֐�

	pD3Device->Release();	// DirectX�̃f�o�C�X�̉��
	pDirect3D->Release();			// DirectX�I�u�W�F�N�g�̉��

	return (int)msg.wParam;
}