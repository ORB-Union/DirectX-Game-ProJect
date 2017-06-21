#include"Common.h"

#define ENEMY_NUM 5

//�Ϲ���
class Enemy :public entity {

public :
	Enemy();
	~Enemy();
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



//Ư����(ȣ��)
class NewEnemy :public entity {

public:

	NewEnemy();
	~NewEnemy();

	bool up;
	bool down;
	bool moving; //�̵�
	bool stop; // ����
	void Uping(); // ����
	void downing(); // �Ʒ���
	void Stopping(); // ������Ű�� ��ó��

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




//����Ұ� ������Ʈ
class Mushroom:public entity {

public:

	Mushroom();
	~Mushroom();

	bool up;
	bool down;
	bool moving; //�̵�
	bool stop; // ����
	void Uping(); // ����
	void downing(); // �Ʒ���
	void Stopping(); // ������Ű�� ��ó��

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




//����
class BossEnemy :public entity {

public:
	BossEnemy();
	~BossEnemy();

	bool move_check = false;

	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y); // �浹üũ


	void init(float x, float y);
	void fire();
	void move(float x, float y);
	bool Visible;
	bool Boss_Check = false;
	bool Boss_Exist = false;
};
