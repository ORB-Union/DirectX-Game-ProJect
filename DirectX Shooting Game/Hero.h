#include"Common.h"
#include<vector>

class Hero :public entity
{
private :

public:
	Hero();
	~Hero();

	void move(int i);
	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y);//�浹üũ
	bool Hero_Hit;

	void init(float x, float y);









};
