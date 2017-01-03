#pragma once

/*
	Tentacle
	�ۼ��� : �̱ٿ�
	���ڷ� �÷��̾��� ������, �����ð�, ������, �浹 �Ŵ����� �޾Ƽ� �����Ǵ� Boss�� ���� Ŭ����.
	������ bool�� ���ڴ� �̸� ������ ������ ������ �ƴ��� �Ǵ��Ѵ�.
	�Ϲ� ������ ��쿡�� �̸� ������ �����ְ� (true)
	Strike�� ��쿡�� ������ �������� �ʴ´� (false)
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