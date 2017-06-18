#include"Common.h"
#include<vector>

class Hero :public entity
{

	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pSprite;

	D3DXVECTOR3			m_vPos;
	RECT				m_rect;
	D3DCOLOR			m_color;
	unsigned int		m_alpha;

	bool				m_bDraw;
	float				m_deltaTime;

	float				m_width;
	float				m_height;

	float				m_radius;

	float				m_AniTimer;
	int					m_AniNum;



public:
	Hero();
	~Hero();
	bool bShow; // ���̴��� üũ
	bool show(); // �����ֱ�
	void hide(); // �浹�� �ı�
	void active(); // ��ư ������ �Ѿ� �߻�
	bool check_collision(float x, float y);//�浹üũ
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
