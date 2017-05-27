#include"Common.h"

class Enemy :public entity {

public :
	void init(float x, float y);
	void fire();
	void move();
};