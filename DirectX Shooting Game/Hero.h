#include"Common.h"
#include<vector>

class Hero :public entity
{
public:
	Hero();
	~Hero();
	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y);//충돌체크
	bool Hero_Hit;


	void init(float x, float y);
	void fire();
	void super_fire();
	void move(int i);
	void Move();
	


	/*
	bool getVisible();
	void setVisible(BOOL bVisible);
	void playAni();
	void stopAni();
	void addimage(Hero *pImage);
	void Update();
	*/
};
