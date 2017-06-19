#include"Common.h"

#define ENEMY_NUM 5

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





class BigestMissile :public entity {

public:

	BigestMissile();
	~BigestMissile();

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