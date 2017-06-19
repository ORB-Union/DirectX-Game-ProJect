#include"Common.h"

#define ENEMY_NUM 5

class Enemy :public entity {

public :
	Enemy();
	~Enemy();
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




class NewEnemy :public entity {

public:

	NewEnemy();
	~NewEnemy();

	bool up;
	bool down;
	bool moving; //이동
	bool stop; // 정지
	void Uping(); // 위쪽
	void downing(); // 아래쪽
	void Stopping(); // 정지시키는 것처럼

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





class BigestMissile :public entity {

public:

	BigestMissile();
	~BigestMissile();

	bool up;
	bool down;
	bool moving; //이동
	bool stop; // 정지
	void Uping(); // 위쪽
	void downing(); // 아래쪽
	void Stopping(); // 정지시키는 것처럼

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