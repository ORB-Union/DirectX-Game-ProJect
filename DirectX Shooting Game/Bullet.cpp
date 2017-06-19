#include"Bullet.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//일반 총알 발사

//bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

Bullet::Bullet()
{

}


Bullet::~Bullet()
{

}

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

///////////////////////////////////////
//두번째 총알

Bullet2::Bullet2()
{

}


Bullet2::~Bullet2()
{

}

void Bullet2::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}

bool Bullet2::show()
{
	return bShow;

}

void Bullet2::active()
{
	bShow = true;

}

void Bullet2::move()
{
	x_pos += 20;
	y_pos += 5;

}

void Bullet2::hide()
{
	bShow = false;
}



///////////////////////////////////////
//세번째 총알

Bullet3::Bullet3()
{

}


Bullet3::~Bullet3()
{

}

void Bullet3::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}

bool Bullet3::show()
{
	return bShow;

}

void Bullet3::active()
{
	bShow = true;

}

void Bullet3::move()
{
	y_pos -= 5;
	x_pos += 20;
	
}

void Bullet3::hide()
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



/////////////////////////////////////////////
void NewEnemyBullet::move()
{
	x_pos -= 15;
}

void NewEnemyBullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool NewEnemyBullet::show()
{
	return bShow;
}


void NewEnemyBullet::active()
{
	bShow = true;
}


void NewEnemyBullet::hide()
{
	bShow = false;
}