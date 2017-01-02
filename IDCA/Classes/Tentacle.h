#pragma once

/*
	Tentacle
	작성자 : 이근원
	인자로 플레이어의 포지션, 지연시간, 데미지를 받아서 생성되는 Boss의 공격 클래스.
*/

class Tentacle : public Node
{
public :

	virtual bool init(const Vec2, const float, const float, TMXTiledMap*);
	virtual void update(float deltaTime) override;

	/* Create Function Re-define */
	static Tentacle* create(const Vec2 initPosition, const float duration, const float damage, TMXTiledMap* mapPointer) {
		auto p = new Tentacle();
		if (p->init(initPosition, duration, damage, mapPointer)) {
			p->autorelease();
			return p;
		}
		else {
			delete p;
			return nullptr;
		}
	}

	/* Member Variable */
	CC_SYNTHESIZE(Vec2, m_CreatePosition, CreatePosition);
	CC_SYNTHESIZE(float, m_Duration, Duration);
	CC_SYNTHESIZE(float, m_Damage, Damage);
	CC_SYNTHESIZE(Vec2, m_PlayerPosition, PlayerPosition);
	CC_SYNTHESIZE(float, m_Distance, Distance);
	CC_SYNTHESIZE(Sprite*, m_pTentacleSprite, TentacleSprite);
	CC_SYNTHESIZE(Animation*, m_pTentacleAnimation, TentacleAnimation);
	CC_SYNTHESIZE(Animate*, m_pTentacleAnimate, TentacleAnimate);
	CC_SYNTHESIZE(TMXTiledMap*, m_pMapPointer, MapPointer);
	CC_SYNTHESIZE(float, m_AcculmulateTime, AcculmulateTime);
	CC_SYNTHESIZE(bool, m_IsAttackEnd, IsAttackEnd);


	/* Member Function */
	void MakeTentacleAnimation();
	void MakeCautionRange();
	void MakeTentacleDead();
};