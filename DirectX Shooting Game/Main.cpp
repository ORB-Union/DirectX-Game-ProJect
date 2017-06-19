// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

//배경음
#include<mmsystem.h>
#include <Digitalv.h>

#include"Common.h"
#include"Enemy.h"
#include"Hero.h"
#include"Bullet.h"
#include"BackGround.h"
using namespace std;

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 800
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define ENEMY_NUM 7
#define NewENEMY_NUM 3
#define BackNum 2



// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//음악 재생
#pragma comment (lib, "winmm.lib")
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_STATUS_PARMS mciStatus;

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
ID3DXFont *font; // 점수
RECT fRectangle;
std::string message;


bool KeyCheck;

int Time;
int counter;

// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite

//플레이어
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
//플레이어 애니메이션
//총알
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_superbullet; // 필살기


//적
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemybullet;

LPDIRECT3DTEXTURE9 sprite_Newenemy;    // the pointer to the sprite


////////////////////////////////////////////////////////////
//백그라운드
//타이틀
LPDIRECT3DTEXTURE9 sprite_Title;    // 타이틀

//인게임 배경화면
LPDIRECT3DTEXTURE9 sprite_BackGround1;    // 배경화면
LPDIRECT3DTEXTURE9 sprite_BackGround2;    // 배경화면

//게임 오버
LPDIRECT3DTEXTURE9 sprite_over;    // 게임오버


bool Title; // 타이틀
bool InGame; // 인게임
bool Game_over; // 게임오버

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);
//bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//객체 생성
Hero hero;
//Bullet bullet;
Bullet bull[100];
Enemy enemy[ENEMY_NUM];
EnemyBullet Ebullet[ENEMY_NUM];
NewEnemy newenemy[ENEMY_NUM];
BackGround back[2];

//Bullet bullet;
//SuperBullet Superbullet;
//EnemyBullet enemybullet;

//음악재생 관련
UINT wDeviceID = 0;
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;
	mciOpen.lpstrDeviceType = L"MPEGVideo";
	//재생타입

	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (Result)
	{
		return Result;
	}

	wDeviceID = mciOpen.wDeviceID;
	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)	
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindow(L"WindowClass", L"DirectX Shooting Game",
		WS_OVERLAPPEDWINDOW, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	DWORD Sound1, Sound2;
	Sound1 = LoadWAV(hWnd, L"Yowamushi Pedal OST - Sakamichi.mp3");
	Sound2 = LoadWAV(hWnd, L"Family.mp3");
	//Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);


	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();
		render_frame();
		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	//화면 전환을 위한 선언
	Title = true;
	InGame = false;
	Game_over = false;


	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object

	//타이틀
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Sonic_Title.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Title);    // load to sprite

	//인게임
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"sonic_sprite_background_1.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_BackGround1);    // load to sprite

	//인게임
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"sonic_sprite_background_2.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_BackGround2);    // load to sprite


	 //게임오버
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Sonic_GameOver.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_over);    // load to sprite

	///////////////////////////////////////////////////////////////////
	//인게임

	//플레이어
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"SonicSprite1.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero);    // load to sprite

    //플레이어 총알
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBulletsprite.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet);    // load to sprite

	//필살기
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_superbullet);    // load to sprite


	//적
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"EnemySonic.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite



	//적총알
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"EnemyBullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemybullet);    // load to sprite


	//거대 소닉
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"NewEnemy.png",    // the file name
		100,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemy);    // load to sprite


	/*
	font = NULL;
	HRESULT hr = D3DXCreateFont(d3ddev, 40, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FF_DONTCARE, L"Arial", &font);
	if (!SUCCEEDED(hr))
	{
		return;
	}

	SetRect(&fRectangle, 0, 0, 300, 200);
	message = "Shooting Game";
	*/
	return;
}

//충돌
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}



//적과의 충돌
bool Hero::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 60, x, y, 60) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


//적 충돌
bool Enemy::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


bool NewEnemy::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 50) == true)
	{
		bShow = false;
		return true;

	}
	else {
		return false;
	}
}


//총알 발사시 적과의 충돌
bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


//적의 총알	발사시 캐릭터와의 충돌
bool EnemyBullet::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}


void Death()
{
	hero.HP -= 1;
	if (hero.HP <= 0)
	{
		Game_over = true;
	}
}


void init_game(void)
{
	//배경화면 초기화
	back[0].init(0, 0);
	back[1].init(SCREEN_WIDTH, 0);


	//플레이어 초기화 
	hero.init(50, 300);
	hero.HP = 10;

	//적 초기화 
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT-50);
		
	}

	//새로운적 초기화
	for (int i = 0; i < NewENEMY_NUM; i++)
	{
		newenemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT-50);

	}

	//총알 초기화
	for (int i = 0; i < 100; i++)
	{
		bull[i].init(hero.x_pos, hero.y_pos);
	}

	//적 총알 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		Ebullet[i].init(enemy[i].x_pos, enemy[i	].y_pos);
	}

	//Superbullet.init(hero.x_pos, hero.y_pos);

}

void do_game_logic(void)
{
	if (InGame == true)
	{
		//배경화면 처리
		for (int i = 0; i < BackNum; i++)
		{
			back[i].Move();
		}
		//주인공 처리 
		if (KEY_DOWN(VK_UP))
		{
			hero.move(MOVE_UP);
		}

		if (KEY_DOWN(VK_DOWN))
		{
			hero.move(MOVE_DOWN);
		}

		if (KEY_DOWN(VK_LEFT))
		{
			hero.move(MOVE_LEFT);
		}

		if (KEY_DOWN(VK_RIGHT))
		{
			hero.move(MOVE_RIGHT);
		}

		Death();

		//총알 연사처리
		if (KEY_DOWN(VK_SPACE) && 0x80000)
		{
			counter++;
			if (counter % 5 == 0)
			{
				for (int i = 0; i < 100; i++)
				{
					if (bull[i].show() == false)
					{
						bull[i].active();

						bull[i].init(hero.x_pos, hero.y_pos);
						//bull[i].move();
						break;
					}

				}
			}
		}
		//총알처리
		for (int i = 0; i < 100; i++)
		{
			if (bull[i].show() == true)
			{
				if (bull[i].x_pos > SCREEN_WIDTH)
					bull[i].hide();
				else
					bull[i].move();

				//일반 적 충돌 처리 
				for (int j = 0; j < ENEMY_NUM; j++)
				{
					if (bull[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
					{
						enemy[j].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
					}
				}

				//새로운 적 충돌 처리
				for (int t = 0; t < NewENEMY_NUM; t++)
				{
					if (bull[i].check_collision(newenemy[t].x_pos, newenemy[t].y_pos) == true)
					{
						newenemy[t].HP -= 1;
						if (newenemy[t].HP <= 0)
						{
							//이후 생성 안되는 버그 해결
							newenemy[t].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
							newenemy[t].HP = 10;
						}

					}

				}
			}
		}

		/////////////////////
		//적들 충돌 처리  및 생성
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].show() == false)
			{
				enemy[i].active();
				enemy[i].init((float)(SCREEN_WIDTH + (rand() % 200)), rand() % SCREEN_HEIGHT - 50);
			}
			if (enemy[i].show() == true)
			{
				if (enemy[i].x_pos < -100)
				{
					enemy[i].hide();
				}
				else
					enemy[i].move();
			}

			if (enemy[i].check_collision(hero.x_pos, hero.y_pos) == true)
			{
				enemy[i].hide();
			}


			if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				Death();
			}
		}

		//적 총알 처리
		for (int j = 0; j < ENEMY_NUM; j++)
		{
			if (enemy[j].x_pos < (SCREEN_WIDTH - 300) + rand() % 150 && Ebullet[j].show() == false)
			{
				Ebullet[j].active();
				Ebullet[j].init(enemy[j].x_pos, enemy[j].y_pos);
			}
		}
		//적 총알 처리
		for (int t = 0; t < ENEMY_NUM; t++)
		{
			if (Ebullet[t].show() == true)
			{
				if (Ebullet[t].x_pos < -100)
					Ebullet[t].hide();
				else
					Ebullet[t].move();
			}

			if (Ebullet[t].check_collision(hero.x_pos, hero.y_pos) == true)
			{
				Ebullet[t].hide();
			}

			if (hero.check_collision(Ebullet[t].x_pos, Ebullet[t].y_pos) == true)
			{
				Death();
			}

		}



		/////////////////////////////////////////////
		for (int i = 0; i < NewENEMY_NUM; i++)
		{
			if (newenemy[i].show() == false && Time % 8 == 0)
			{
				newenemy[i].active();
				newenemy[i].init((float)(SCREEN_WIDTH + (rand() % 400)), rand() % SCREEN_HEIGHT);
			}


			if (newenemy[i].show() == true)
			{
				if (newenemy[i].x_pos < -100)
				{
					newenemy[i].hide();
				}
				//if(newenemy[i].x_pos > -100)
				else
				{
					newenemy[i].move();
					//newenemy[i].Stopping();					
				}
				/*
				else
				{
					newenemy[i].Uping();
					newenemy[i].downing();
				}
				*/

			}

			if (newenemy[i].check_collision(hero.x_pos, hero.y_pos) == true || newenemy[i].HP <= 0)
			{
				newenemy[i].hide();
			}


			if (hero.check_collision(newenemy[i].x_pos, newenemy[i].y_pos) == true)
			{
				Death();
			}

		}
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
	////////////////////////////////////////////////////////////
	//타이틀
	if (KEY_DOWN(VK_SPACE))
	{
		Title = false;
		InGame = true;
	}

	if (Title == true)
	{
		//음악 재생
		mciSendCommand(2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		//mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */


		RECT part8;
		SetRect(&part8, 0, 0, 1240, 800);
		D3DXVECTOR3 center8(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position8(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_Title, &part8, &center8, &position8, D3DCOLOR_ARGB(255, 255, 255, 255));

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		
		//폰트

		return;
	}

	////////////////////////////////////////////////////////////////////
	//인게임

	if (InGame == true)
	{

		//음악닫고 재생
		mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */

		//배경화면
		RECT part6;
		SetRect(&part6, 0, 0, 1240, 800);
		D3DXVECTOR3 center6(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position6(back[0].x_pos, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_BackGround1, &part6, &center6, &position6, D3DCOLOR_ARGB(255, 255, 255, 255));

		//배경화면2
		RECT part7;
		SetRect(&part7, 0, 0, 1240, 800);
		D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position7(back[1].x_pos, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_BackGround2, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));


		//주인공 애니메이션
		RECT part_1;
		SetRect(&part_1, 0, 0, 60, 60);
		D3DXVECTOR3 center_1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position_1(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_hero, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));


		////총알
		for (int i = 0; i < 100; i++)
		{
			if (bull[i].bShow == true)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 40, 40);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bull[i].x_pos, bull[i].y_pos + 5.0f, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}


		/*

		////슈퍼총알
		if (Superbullet.bShow == true)
		{
			RECT part3;
			SetRect(&part3, 0, 0, 100, 100);
			D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position3(Superbullet.x_pos, Superbullet.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_superbullet, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		*/


		////에네미 
		RECT part2;
		SetRect(&part2, 0, 0, 60, 60);
		D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//적총알


		RECT part4;
		SetRect(&part4, 0, 0, 30, 30);
		D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner	


		for (int i = 0; i < ENEMY_NUM; i++)
		{
			D3DXVECTOR3 position4(Ebullet[i].x_pos, Ebullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth		
			d3dspt->Draw(sprite_enemybullet, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));
		}


		//새로운 적
		RECT part5;
		SetRect(&part5, 0, 0, 100, 100);
		D3DXVECTOR3 center5(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < NewENEMY_NUM; i++)
		{
			D3DXVECTOR3 position5(newenemy[i].x_pos, newenemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_Newenemy, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (font)
		{
			font->DrawTextA(NULL, message.c_str(), -1, &fRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
		}



		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		//폰트

		return;
	}

	///////////////////////////////////////////////////////////
	//게임오버

	if (hero.HP <= 0)
	{
		InGame = false;
		Game_over = true;
	}

	if (Game_over == true)
	{
		mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */

												 //배경화면

		RECT part9;
		SetRect(&part9, 0, 0, 1240, 800);
		D3DXVECTOR3 center9(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position9(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_over, &part9, &center9, &position9, D3DCOLOR_ARGB(255, 255, 255, 255));

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		//폰트

		return;
	}
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
	font->Release();
	//배경화면 해제 
	sprite_BackGround1->Release();
	sprite_BackGround2->Release();

	//플레이어 해제
	sprite_hero->Release();
	sprite_bullet->Release();
	sprite_superbullet->Release();

	//적 해제
	sprite_enemy->Release();
	sprite_enemybullet->Release();

	//타이틀 / 게임오버 해제
	sprite_Title->Release();
	sprite_over->Release();

	//음악 닫기
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	return;
}




