#pragma once	

/*
	class Projectile
	투사체를 담당하는 기본 클래스.
	작성일자 : 16.12.01
	작성자 김현우
	투사체 클래스에는 뭐가 필요할까??
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