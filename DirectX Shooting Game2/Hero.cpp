#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"Common.h"
#include"Hero.h"

//����Ű ����
enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

//Ŭ���� �Լ� ����
void Hero::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_UP:
		y_pos -= 5;
		break;

	case MOVE_DOWN:
		y_pos += 5;
		break;


	case MOVE_LEFT:
		x_pos -= 5;
		break;


	case MOVE_RIGHT:
		x_pos += 5;
		break;

	}

}

void Hero::fire()
{

}

void Hero::super_fire()
{

}