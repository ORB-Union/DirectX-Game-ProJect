#pragma once
#include"Common.h"
#include<cmath>

/////////////////////////////////////////////////////////////////////
//영웅 총알
class Bullet : public entity
{
public:
	Bullet();
	~Bullet();
	bool bShow; // 보이는지 체크
	void init(float x, float y); // 초기화
	void move(); // 이동
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌 체크
};


//두번째 총알
class Bullet2 : public entity
{
public:
	Bullet2();
	~Bullet2();
	bool bShow; // 보이는지 체크
	void init(float x, float y); // 초기화
	void move(); // 이동
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌 체크
};



//세번째 총알
class Bullet3 : public entity
{
public:
	Bullet3();
	~Bullet3();
	bool bShow; // 보이는지 체크
	void init(float x, float y); // 초기화
	void move(); // 이동
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌 체크
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//적들 총알
class EnemyBullet : public entity
{
public:
	EnemyBullet();
	~EnemyBullet();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
};



///////////////////////////////////////////////////////////////////////////////////////////////////////
//호밍쏘는 특수적
class NewEnemyBullet : public entity
{
public:
	NewEnemyBullet();
	~NewEnemyBullet();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
	void HomingBullet(float& x, float& y, float mx, float my, float speed); // 탄환의 좌표, 메인 캐릭터의 좌표, 탄환의 속도
};


/////////////////////////////////////////////////////////////////////////////////////
//보스 총알
//단순 직선총알
class BossBullet1 : public entity
{
public:
	BossBullet1();
	~BossBullet1();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
};

//대각선탄
class BossBullet2 : public entity
{
public:
	float vx, vy;
	BossBullet2();
	~BossBullet2();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();

	void InitAimingBullet(float mx, float my, float ex, float ey, float speed, float& x, float& y, float& vx, float& vy); // 메인 캐릭터의 위치, 적기의 좌표, 탄환의 속도, 탄환의 좌표, 탄환의 속도 벡터
	void AimingBullet(float& x, float& y, float vx, float vy); // 탄환의 좌표, 탄환의 속도
};


//포물선탄
class BossBullet3 : public entity
{
public:
	float vx, vy;
	BossBullet3();
	~BossBullet3();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
	//포물선탄
	void InitAimingBullet2(float mx, float my, float ex, float ey, float speed, float& x, float& y, float& vx, float& vy); // 메인 캐릭터의 위치, 적기의 좌표, 탄환의 속도, 탄환의 좌표, 탄환의 속도 벡터
	void DroppingBullet_Up(float& x, float& y, float accel, float& vx, float& vy); // 탄환의 좌표, 가속도, 속도 벡터의 좌표

};


//포물선탄
class BossBullet4 : public entity
{
public:
	BossBullet4();
	~BossBullet4();
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
	//포물선탄
};