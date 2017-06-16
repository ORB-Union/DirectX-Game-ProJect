#pragma once
#include"Common.h"
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
class Bullet : public entity
{
public:
	bool bShow; // 보이는지 체크
	void init(float x, float y); // 초기화
	void move(); // 이동
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌 체크
};



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
