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
	bool bShow; // ���̴��� üũ
	void init(float x, float y); // �ʱ�ȭ
	void move(); // �̵�
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹 üũ
};