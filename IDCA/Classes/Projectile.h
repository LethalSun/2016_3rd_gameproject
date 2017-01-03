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
public:
	Projectile();
	~Projectile();

	static Projectile* create(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	virtual bool init(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	Sprite* GetSprite();
	Vec2 GetColideRange();
	Vec2 GetColidePosition();
	int GetDamage();
	bool IsFromCharacter();
	bool IsAttackChecked();
	bool IsDisappear();

	void SetStartPosition(Vec2);
	void SetDirection(Vec2);
	void SetMaxRange(Vec2);
	void SetColideRange(Vec2);
	void SetDamage(int);
	void SetOrign(bool);
	void SetIsAttackChecked(bool);
	void SetDisappear(bool);
	void SetInvisible();
	void Erase();
private:
	Sprite* m_pSprite;
	Vec2 m_startPosition;
	Vec2 m_DirectionVec;
	Vec2 m_MaxRange;
	Vec2 m_ColideRange;

	int m_damage;
	bool m_isCharacterOrignated;
	bool m_Disappeared;
	bool m_IsAttackChecked;
	bool SetSprite();
};