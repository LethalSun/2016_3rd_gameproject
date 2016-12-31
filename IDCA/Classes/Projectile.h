#pragma once	

/*
	class Projectile
	����ü�� ����ϴ� �⺻ Ŭ����.
	�ۼ����� : 16.12.01
	�ۼ��� ������
	����ü Ŭ�������� ���� �ʿ��ұ�??
*/


class Projectile : public Node
{
public :
	Projectile();
	~Projectile();

	Sprite* GetSprite();
	Vec2 GetColideRange();
	int GetDamage();

	void SetStartPosition(Vec2);
	void SetDirection(Vec2);
	void SetMaxRange(Vec2);
	void SetColideRange(Vec2);
	
	
private :
	Sprite* m_pSprite;
	Vec2 m_startPosition;
	Vec2 m_DirectionVec;
	Vec2 m_MaxRange;
	Vec2 m_ColideRange;

	int m_damage;
};