#include"Common.h"

#define ENEMY_NUM 5

class Enemy :public entity {

public :
	void init(float x, float y);
	void fire();
	void move();
	bool Visible;
};