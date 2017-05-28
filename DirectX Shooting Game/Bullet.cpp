#include"Bullet.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//일반 총알 발사


//bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

/*
bool Bullet::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {
		return false;
	}
}
*/

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

