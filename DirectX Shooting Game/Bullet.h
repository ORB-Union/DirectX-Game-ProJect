#pragma once
#include"Common.h"
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

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
class EnemyBullet : public Bullet
{
public:
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
};



class NewEnemyBullet : public Bullet
{
public:
	int Hp;
	bool bShow;
	void move();
	bool check_collision(float x, float y);
	void init(float x, float y);
	bool show();
	void active();
	void hide();
};