#pragma once
#include"Common.h"
#include<cmath>

/////////////////////////////////////////////////////////////////////
//���� �Ѿ�
class Bullet : public entity
{
public:
	Bullet();
	~Bullet();
	bool bShow; // ���̴��� üũ
	void init(float x, float y); // �ʱ�ȭ
	void move(); // �̵�
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹 üũ
};


//�ι�° �Ѿ�
class Bullet2 : public entity
{
public:
	Bullet2();
	~Bullet2();
	bool bShow; // ���̴��� üũ
	void init(float x, float y); // �ʱ�ȭ
	void move(); // �̵�
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹 üũ
};



//����° �Ѿ�
class Bullet3 : public entity
{
public:
	Bullet3();
	~Bullet3();
	bool bShow; // ���̴��� üũ
	void init(float x, float y); // �ʱ�ȭ
	void move(); // �̵�
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹 üũ
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//���� �Ѿ�
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
//ȣ�ֽ�� Ư����
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
	void HomingBullet(float& x, float& y, float mx, float my, float speed); // źȯ�� ��ǥ, ���� ĳ������ ��ǥ, źȯ�� �ӵ�
};


/////////////////////////////////////////////////////////////////////////////////////
//���� �Ѿ�
//�ܼ� �����Ѿ�
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

//�밢��ź
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

	void InitAimingBullet(float mx, float my, float ex, float ey, float speed, float& x, float& y, float& vx, float& vy); // ���� ĳ������ ��ġ, ������ ��ǥ, źȯ�� �ӵ�, źȯ�� ��ǥ, źȯ�� �ӵ� ����
	void AimingBullet(float& x, float& y, float vx, float vy); // źȯ�� ��ǥ, źȯ�� �ӵ�
};


//������ź
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
	//������ź
	void InitAimingBullet2(float mx, float my, float ex, float ey, float speed, float& x, float& y, float& vx, float& vy); // ���� ĳ������ ��ġ, ������ ��ǥ, źȯ�� �ӵ�, źȯ�� ��ǥ, źȯ�� �ӵ� ����
	void DroppingBullet_Up(float& x, float& y, float accel, float& vx, float& vy); // źȯ�� ��ǥ, ���ӵ�, �ӵ� ������ ��ǥ

};


//������ź
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
	//������ź
};