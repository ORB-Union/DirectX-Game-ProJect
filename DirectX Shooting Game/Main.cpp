// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#include"Common.h"
#include"Enemy.h"
#include"Hero.h"
#include"Bullet.h"

using namespace std;

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 800
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define ENEMY_NUM 7


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
ID3DXFont *font; // 점수
RECT fRectangle;
std::string message;


bool KeyCheck;

// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite

//플레이어
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_superbullet; // 필살기


//적
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemybullet;


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

//Bullet bullet;
//SuperBullet Superbullet;
//EnemyBullet enemybullet;


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

	hWnd = CreateWindow(L"WindowClass", L"Our Direct3D Program",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

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

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Panel4.png",    // the file name
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
		&sprite);    // load to sprite


	//플레이어
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"SonicSprite1.png",    // the file name
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

bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}



//총알 발사시 적과의 충돌
bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 40, x, y, 40) == true)
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
	if (sphere_collision_check(x_pos, y_pos, 40, x, y, 40) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}


void init_game(void)
{
	//객체 초기화 
	hero.init(50, 300);


	//적 초기화 
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT);
		
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
	static int counter = 0;

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

	//적들 처리 
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].x_pos < 0)
			enemy[i].init((float)(SCREEN_WIDTH + (rand() % 200)), rand() % SCREEN_HEIGHT);
		else
			enemy[i].move();
	}

	//적 총알 처리
	for (int j = 0; j < ENEMY_NUM; j++)
	{
		if (Ebullet[j].show() == false)
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
			if (Ebullet[t].x_pos < SCREEN_WIDTH)
				Ebullet[t].hide();
			else
				Ebullet[t].move();
		}


		if (Ebullet[t].check_collision(hero.x_pos, hero.y_pos) == true)
		{
			Ebullet[t].hide();
		}
	}


	//총알 연사처리
	if (KEY_DOWN(VK_SPACE) && 0x80000)
	{
		counter++;
		if(counter % 5 == 0)
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

			//충돌 처리 
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				if (bull[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
				{
					enemy[j].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT);
				}
			}
		}
	}
	/*
	for (int k = 0; k < 100; k++)
	{
		if(bull[k].show() == false)
		{
		if (GetKeyState(VK_SPACE))
		{
			bull[k].init(hero.x_pos, hero.y_pos);
			bull[k].active();
		}
		}
		if (bull[k].show() == true)
		{
			if (bull[k].x_pos > 1300)
			{
				bull[k].hide();
			}
			else
				bull[k].move();
		}
	}

	*/
	
	/*
	
	if (bullet.show() == false)
	{
		if (KEY_DOWN(VK_SPACE))
		{
			bullet.active();
			bullet.init(hero.x_pos, hero.y_pos);
		}
	}
	

	
	if (bullet.show() == true)
	{
		if (bullet.x_pos > 1300)
			bullet.hide();
		else
			bullet.move();
	*/
			

		/*
		//충돌 처리
		for (int i = 0; i<ENEMY_NUM; i++)
		{
			if (bullet.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				enemy[i].init((float)(rand() % 300), rand() % 200 - 300);

			}
		}
		}
		*/
	
}

// this is the function used to render a single frame
void render_frame(void)
{
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

	RECT part6;
	SetRect(&part6, 0, 0, 640, 480);
	D3DXVECTOR3 center6(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position6(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite, &part6, &center6, &position6, D3DCOLOR_ARGB(255, 255, 255, 255));


	//주인공 
	RECT part;
	SetRect(&part, 0, 0, 60, 60);
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

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
	SetRect(&part4, 0, 0, 64, 64);
	D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

	for (int i = 0; i < ENEMY_NUM; i++)
	{
			D3DXVECTOR3 position4(Ebullet[i].x_pos, Ebullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_enemybullet, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));	
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


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite->Release();
	d3ddev->Release();
	d3d->Release();
	font->Release();
	//객체 해제 
	sprite_hero->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();
	sprite_superbullet->Release();
	sprite_enemybullet->Release();

	return;
}
