#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"Common.h"
#include"Hero.h"
#include<iostream>
#include"Bullet.h"
#include"Enemy.h"


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)




Hero hero;
Bullet bullet;
Enemy enemy[ENEMY_NUM];

LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite

//플레이어
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_superbullet; // 필살기


//적
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemybullet;



enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

void init_game(void)
{
	//객체 초기화 
	hero.init(50, 300);


	//적 및 총알들 초기화 
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
		//enemybullet.init(enemy[i].x_pos, enemy[i].y_pos);
	}

	//총알 초기화 
	//bullet.init(hero.x_pos, hero.y_pos);
	//Superbullet.init(hero.x_pos, hero.y_pos);

}

void do_game_logic(void)
{


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
		if (enemy[i].y_pos > 500)
		{
			enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
		}
		else
		{
			enemy[i].move();
		}
	}


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
	if (bullet.bShow == true)
	{
		RECT part1;
		SetRect(&part1, 0, 0, 64, 64);
		D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
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
	SetRect(&part2, 0, 0, 64, 64);
	D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	/*
	//적총알
	if (enemybullet.bShow == true)
	{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
	RECT part4;
	SetRect(&part4, 0, 0, 64, 64);
	D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position4(enemybullet.x_pos, enemybullet.y_pos, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite_enemybullet, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	}
	*/

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

