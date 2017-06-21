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
//두번째 총알(아래방향)

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
//세번째 총알(위쪽방향)

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
EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

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
NewEnemyBullet::NewEnemyBullet()
{
	HP = 3;
}

NewEnemyBullet::~NewEnemyBullet()
{
}

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

void NewEnemyBullet::HomingBullet(float& x, float& y, float mx, float my, float speed) // 탄환의 좌표, 메인 캐릭터의 좌표, 탄환의 속도
{
	float d = sqrt((mx - x)*(mx - x) + (my - y)*(my - y)); // 목표까지의 거리

	float vx, vy;

	// 목표까지의 거리 d가 0일 때는 속도 벡터를 화면 아래쪽으로 함
	if (d)
	{
		vx = (mx - x) / d*speed;
		vy = (my - y) / d*speed;
	}
	else
	{
		vx = 0;
		vy = speed;
	}
	x += vx;
	y += vy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//보스 총알(종류는 세가지)
//첫번째 총알 직선 총알
BossBullet1::BossBullet1()
{

}

BossBullet1::~BossBullet1()
{

}

void BossBullet1::move()
{
	x_pos -= 15;
}

void BossBullet1::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool BossBullet1::show()
{
	return bShow;
}


void BossBullet1::active()
{
	bShow = true;
}


void BossBullet1::hide()
{
	bShow = false;
}

//////////////////////////////////
//보스 두번째 총알
BossBullet2::BossBullet2()
{

}

BossBullet2::~BossBullet2()
{

}

void BossBullet2::move()
{
	x_pos -= 15;
}

void BossBullet2::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool BossBullet2::show()
{
	return bShow;
}


void BossBullet2::active()
{
	bShow = true;
}


void BossBullet2::hide()
{
	bShow = false;
}

// 대각선 직진탄선언
void BossBullet2:: InitAimingBullet(float mx, float my, float ex, float ey, float speed, float& x, float& y, float& vx, float& vy) // 메인 캐릭터의 위치, 적기의 좌표, 탄환의 속도, 탄환의 좌표, 탄환의 속도 벡터
{
	x = ex;
	y = ey;

	float d = sqrt((mx - ex)*(mx - ex) + (my - ey)*(my - ey));

	if (d)
	{
		vx = (mx - ex) / d*speed;
		vy = (my - ey) / d*speed;
	}
	else
	{
		vx = 0;
		vy = speed;
	}
}

//대각선 직진탄
void BossBullet2::AimingBullet(float& x, float& y, float vx, float vy) // 탄환의 좌표, 탄환의 속도
{
	x += vx;
	y += vy;
}

/////////////////////////////////////////////////////
//보스 총알(세번째)

BossBullet3::BossBullet3()
{

}

BossBullet3::~BossBullet3()
{

}

void BossBullet3::move()
{
	x_pos -= 15;
}

void BossBullet3::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool BossBullet3::show()
{
	return bShow;
}


void BossBullet3::active()
{
	bShow = true;
}


void BossBullet3::hide()
{
	bShow = false;
}

// 포물선탄 위쪽
void BossBullet3:: DroppingBullet_Up(float& x, float& y, float accel, float& vx, float& vy) // 탄환의 좌표, 가속도, 속도 벡터의 좌표
{
	vx += 0.12;
	vy += accel;
	x += vx;
	y += vy;
}


/////////////////////////////////////////////////////
//보스 총알(네번째)
BossBullet4::BossBullet4()
{

}

BossBullet4::~BossBullet4()
{

}

void BossBullet4::move()
{
	x_pos -= 15;
}

void BossBullet4::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}


bool BossBullet4::show()
{
	return bShow;
}


void BossBullet4::active()
{
	bShow = true;
}


void BossBullet4::hide()
{
	bShow = false;
}

//포물선탄 아래쪽
void BossBullet4::DroppingBullet_Down(float& x, float& y, float accel, float& vx, float& vy) // 탄환의 좌표, 가속도, 속도 벡터의 좌표
{
	vx -= 0.12;
	vy += accel;
	x += vx;
	y += vy;
}

/*
사용법
InitAimingBullet(hero.x_pos, hero.y_pos, f_boss.x_pos + 32, f_boss.y_pos + 32, 4, f_boss_bullet_bomb1.x_pos, f_boss_bullet_bomb1.y_pos, f_boss_bullet_bomb1.vx, f_boss_bullet_bomb1.vy); // 대각선 직진탄
AimingBullet(f_boss_bullet_bomb1.x_pos, f_boss_bullet_bomb1.y_pos, f_boss_bullet_bomb1.vx, f_boss_bullet_bomb1.vy);
DroppingBullet_Up(f_boss_bullet_bomb2.x_pos, f_boss_bullet_bomb2.y_pos, Rand_DroppingBullet, f_boss_bullet_bomb2.vx, f_boss_bullet_bomb2.vy); 
DroppingBullet_Down(f_boss_bullet_bomb3.x_pos, f_boss_bullet_bomb3.y_pos, Rand_DroppingBullet, f_boss_bullet_bomb3.vx, f_boss_bullet_bomb3.vy);
*/