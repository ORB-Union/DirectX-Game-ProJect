#include"Common.h"
#include<vector>

class Hero :public entity
{
private:

public:
	Hero();
	~Hero();

	void move(int i);
	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y);//충돌체크
	void init(float x, float y);

	bool Hero_hit = false;//히트애니메이션용
};
