#include"Common.h"
#include<vector>

class Hero :public entity
{
public:

	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y);//�浹üũ



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
