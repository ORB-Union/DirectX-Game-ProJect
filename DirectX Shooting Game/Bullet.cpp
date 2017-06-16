#include"Bullet.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//일반 총알 발사


//bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


void Bullet::init(float x, float y)
{
	
	x_pos = x;
	y_pos = y;

}

bool Bullet::show()
{
	return bShow;

}

void Bullet::active()
{
	bShow = true;

}

void Bullet::move()
{
	x_pos += 25;
}

void Bullet::hide()
{
	bShow = false;
}





///////////////////////////////////////////////////////////////////////////////////////////////////
//필살기






////////////////////////////////////////////////////////////////////////////////////////////////
//적 총알



void EnemyBullet::move()
{
	x_pos -= 15;
}



void EnemyBullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool EnemyBullet::show()
{
	return bShow;
}


void EnemyBullet::active()
{
	bShow = true;
}


void EnemyBullet::hide()
{
	bShow = false;
}
