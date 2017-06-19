#include"BackGround.h"

void BackGround::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void BackGround::Move()
{
	x_pos -= 8;
	if (x_pos <= -1240)
	{
		x_pos = 1240;
	}
}