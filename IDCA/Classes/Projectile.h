#pragma once

/************************************************************************/
/*
CLASS		: PlayerCharacterManager
Author		: 김현우
역할			: 투사체 함수, 입력값으로 이미지,시작위치,방향,최대거리,충돌범위,누가 만들었는지를 입력받아서
투사체를 스스로 만든다. 최대거리로 가면 스스로 보이지 않게 된다.

*/
/************************************************************************/
class Projectile : public Node
{
public:
	Projectile();
	~Projectile();

	static Projectile* create(const char*, Vec2, Vec2, Vec2, Vec2, bool);

	virtual bool init(const char*, Vec2, Vec2, Vec2, Vec2, bool);
	//스프라이트 충돌범위 충돌위치 데미지 누가 발사했는지 한번 충돌체크가 되었는지 사라진 상태인지 확인 하는 함수들
	Sprite* GetSprite();

	Vec2 GetColideRange();

	Vec2 GetColidePosition();

	int GetDamage();

	bool IsFromCharacter();

	bool IsAttackChecked();

	bool IsDisappear();

	//기본값들을 받는 함수
	void SetStartPosition(Vec2);

	void SetDirection(Vec2);

	void SetMaxRange(Vec2);

	void SetColideRange(Vec2);

	void SetDamage(int);

	void SetOrign(bool);

	//충돌시 투사체를 처리 해주기 위해서 사용하는 함수들
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