#include"Bullet.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//�Ϲ� �Ѿ� �߻�


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





///////////////////////////////////////////////////////////////////////////////////////////////////
//�ʻ��






////////////////////////////////////////////////////////////////////////////////////////////////
//�� �Ѿ�
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