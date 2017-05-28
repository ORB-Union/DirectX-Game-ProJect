#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"Common.h"
#include"Hero.h"
#include<iostream>
#include"Bullet.h"


//방향키 정의
enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

//클래스 함수 정의
void Hero::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}
 
void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_UP:
		y_pos -= 10;
		break;

	case MOVE_DOWN:
		y_pos += 10;
		break;


	case MOVE_LEFT:
		x_pos -= 10;
		break;


	case MOVE_RIGHT:
		x_pos += 10;
		break;

	}

}



void Hero::fire()
{
	Hero hero;
	Bullet bullet;

	if(GetKeyState(VK_SPACE))
	{
		bullet.active();
		bullet.init(hero.x_pos, hero.y_pos);
	}

	if (bullet.show() == true)
	{
		if (bullet.x_pos > 650)
			bullet.hide();
		else
			bullet.move();
	}

}

/*
void Hero::super_fire()
{
	if (Superbullet.show() == false)
	{
		if (KEY_DOWN(0x5A))
		{
			Superbullet.active();
			Superbullet.init(hero.x_pos, hero.y_pos);
		}
	}

	if (Superbullet.show() == true)
	{
		if (Superbullet.y_pos < -70)
			Superbullet.hide();
		else
			Superbullet.move();
	}
}
*/