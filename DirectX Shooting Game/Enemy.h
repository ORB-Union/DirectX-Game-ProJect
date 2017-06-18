#include"Common.h"

#define ENEMY_NUM 5

class Enemy :public entity {

public :
	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌체크


	void init(float x, float y);
	void fire();
	void move();
	bool Visible;
};