#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"Common.h"
#include"Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NewEnemy::NewEnemy()
{
	HP = 10;
}

NewEnemy::~NewEnemy()
{

}

void NewEnemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool NewEnemy::show()
{
	return bShow;

}

void NewEnemy::active()
{
	bShow = true;
}

void NewEnemy::hide()
{
	bShow = false;
}


void NewEnemy::move()
{
	x_pos -= 4;
}



/*
void NewEnemy:: Uping()
{
up = true;
down = false;
if(up == true)
{
y_pos += 5;
if (y_pos > 700)
{
up = false;
down = true;
}
}

void NewEnemy::downing()
{
if (down == true)
{
y_pos -= 5;
if (y_pos < 100)
{
up = true;
down = false;
}
}
}

void NewEnemy::move()
{
	x_pos -= 3;
	moving = true;
	stop = false;
	if (moving == true)
	{
	x_pos -= 5;
	if (x_pos < 1000)
	{
	moving = false;
	stop = true;
	}
	}
}


void NewEnemy::Stopping()
{
if (stop == true)
{
x_pos += 5;
if (x_pos > 1000)
{
moving = true;
stop = false;
}
}
}
*/