#pragma once	

/*
	class Projectile
	투사체를 담당하는 기본 클래스.
	작성일자 : 16.12.01
	작성자 이근원
	투사체 클래스에는 뭐가 필요할까??
*/


class Projectile : public Node
{
public :
	Projectile();
	virtual ~Projectile() = 0;

private :
	Sprite* m_pSprite;
	int m_UnitVec[2];
};