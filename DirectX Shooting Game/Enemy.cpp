#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"Common.h"
#include"Enemy.h"



void Enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Enemy::move()
{
	x_pos -= 10;
}

bool Enemy::show()
{
	return bShow;

}

void Enemy::active()
{
	bShow = true;

}

void Enemy::hide()
{
	bShow = false;
}

