#pragma once

/*
	Tentacle
	작성자 : 이근원
	인자로 플레이어의 포지션, 지연시간, 데미지, 충돌 매니저를 받아서 생성되는 Boss의 공격 클래스.
	마지막 bool값 인자는 미리 범위를 보여줄 것인지 아닌지 판단한다.
	일반 공격의 경우에는 미리 범위를 보여주고 (true)
	Strike의 경우에는 범위를 보여주지 않는다 (false)
*/

class CollideManager;

class Tentacle : public Node
{
public :

	virtual bool init(const Vec2, const float, const int, TMXTiledMap*, CollideManager*, const bool);
	virtual void update(float deltaTime) override;

	/* Create Function Re-define */
	static Tentacle* create(const Vec2 initPosition, const float duration, const int damage,
		TMXTiledMap* mapPointer, CollideManager* collideManager, const bool cautionExist) 

	{
		auto p = new Tentacle();
		if (p->init(initPosition, duration, damage, mapPointer, collideManager, cautionExist)) {
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
	CC_SYNTHESIZE(int, m_Damage, Damage);
	CC_SYNTHESIZE(float, m_Range, Range);
	CC_SYNTHESIZE(Sprite*, m_pTentacleSprite, TentacleSprite);
	CC_SYNTHESIZE(Animation*, m_pTentacleAnimation, TentacleAnimation);
	CC_SYNTHESIZE(Animate*, m_pTentacleAnimate, TentacleAnimate);
	CC_SYNTHESIZE(TMXTiledMap*, m_pMapPointer, MapPointer);
	CC_SYNTHESIZE(float, m_AcculmulateTime, AcculmulateTime);
	CC_SYNTHESIZE(bool, m_IsAttackEnd, IsAttackEnd);
	CC_SYNTHESIZE(Sprite*, m_RangeSprite, RangeSprite);
	CC_SYNTHESIZE(CollideManager*, m_pInnerCollideManager, InnerCollideManager);


	/* Member Function */
	void MakeTentacleAnimation();
	void MakeCautionRange();
	void MakeTentacleDead();
	void CheckTentacleHit();
};