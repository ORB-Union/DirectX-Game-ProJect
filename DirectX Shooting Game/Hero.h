#include"Common.h"
#include<vector>

class Hero :public entity
{
private:

public:
	Hero();
	~Hero();

	void move(int i);
	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y);//�浹üũ
	void init(float x, float y);

	bool Hero_hit = false;//��Ʈ�ִϸ��̼ǿ�
};
