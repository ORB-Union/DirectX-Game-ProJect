#include"Common.h"

#define ENEMY_NUM 5

class Enemy :public entity {

public :
	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹üũ


	void init(float x, float y);
	void fire();
	void move();
	bool Visible;
};