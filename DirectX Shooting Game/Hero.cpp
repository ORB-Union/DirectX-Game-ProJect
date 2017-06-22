#include"Common.h"
#include"Hero.h"


//방향키 정의
enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

Hero::Hero()
{
	HP = 5;
}

Hero::~Hero()
{

}

//클래스 함수 정의
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
		y_pos -= 10;
		break;

	case MOVE_DOWN:
		y_pos += 10;
		break;


	case MOVE_LEFT:
		x_pos -= 10;

		break;


	case MOVE_RIGHT:
		x_pos += 10;
		break;

	}

}


bool Hero::show()
{
	return bShow;

}

void Hero::active()
{
	bShow = true;

}

void Hero::hide()
{
	bShow = false;
}


/*
void Hero::fire()
{
	Hero hero;
	Bullet bullet;
	Bullet bulletc[100];

	if (GetKeyState(VK_SPACE && 0x8000))
	{
		for (int i = 0; i < 100; i++)
		{
			bulletc[i].active();   
			bulletc[i].init(hero.x_pos, hero.y_pos);
			if (bulletc[i].show() == true)
			{
				if (bulletc[i].x_pos > 650)
					bulletc[i].hide();
				else
					bulletc[i].move();
			}
		}
	}
	
}
*/

/*
void Hero::super_fire()
{
	if (Superbullet.show() == false)
	{
		if (KEY_DOWN(0x5A))
		{
			Superbullet.active();
			Superbullet.init(hero.x_pos, hero.y_pos);
		}
	}

	if (Superbullet.show() == true)
	{
		if (Superbullet.y_pos < -70)
			Superbullet.hide();
		else
			Superbullet.move();
	}
}
*/