#include "pch.h"
#include "Tentacle.h"
#include "SimpleAudioEngine.h"
#include "CollideManager.h"

// �˼� �ʱ�ȭ �Լ�.
bool Tentacle::init(const Vec2 initPosition, const float duration, const int damage, 
	TMXTiledMap* mapPointer, CollideManager* collideManager, const bool cautionExist)
{
	if (!Node::init())
	{
		return false;
	}

	setCreatePosition(initPosition);
	setDuration(duration);
	setDamage(damage);
	setMapPointer(mapPointer);
	setAcculmulateTime(0);
	setIsAttackEnd(false);
	setInnerCollideManager(collideManager);
	
	if (cautionExist)
	{
		MakeCautionRange();
	}

	scheduleUpdate();

	return true;
}

// �ʱ�ȭ�� �� �޾Ҵ� �����ð��� �Ѿ�� �˼� �ִϸ��̼��� ��ȯ�ϰ� ���带 ����Ѵ�.
void Tentacle::update(float deltaTime)
{
	m_AcculmulateTime += deltaTime;
	
	if (m_AcculmulateTime > getDuration())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AncientTree_attack.wav", false);
		MakeTentacleAnimation();
	}

	return;
}

// �˼��� ������ �ִϸ��̼��� �����, �ִϸ��̼� ���� ������ ó���ϴ� �Լ�.
void Tentacle::MakeTentacleAnimation()
{
	setTentacleSprite(Sprite::createWithSpriteFrameName("AncientTreeE0.png"));
	getTentacleSprite()->setPosition(getCreatePosition());
	addChild(getTentacleSprite());

	setTentacleAnimation(Animation::create());
	getTentacleAnimation()->setDelayPerUnit(TENTACLE_ANIMAION_DELAY);

	for (int i = 0; i < TENTACLE_MAX_FRAME_NUM; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("AncientTreeE%d.png", i));
		if (!frame)
		{
			break;
		}
		getTentacleAnimation()->addSpriteFrame(frame);
	}

	// �ִϸ��̼� ��, �˼� Ÿ���� ������ Ȯ���ϰ� �ڱ� �ڽ��� remove�Ѵ�.
	setTentacleAnimate(Animate::create(getTentacleAnimation()));
	auto hitfunc = CallFunc::create(CC_CALLBACK_0(Tentacle::CheckTentacleHit, this));
	auto deadfunc = CallFunc::create(CC_CALLBACK_0(Tentacle::MakeTentacleDead, this));
	auto seqAction = Sequence::create(getTentacleAnimate(), hitfunc, deadfunc, nullptr);
	
	removeChild(getRangeSprite());
	getTentacleSprite()->runAction(seqAction);

	return;
}

// �˼��� ������ �� �̸� ������ �˷��ִ� ��������Ʈ�� ���� �Լ�.
void Tentacle::MakeCautionRange()
{
	setRangeSprite(Sprite::create("Monster/range.png"));
	getRangeSprite()->setPosition(getCreatePosition());
	getRangeSprite()->setOpacity(0);
	reorderChild(getRangeSprite(), 0);
	addChild(getRangeSprite());

	auto action = FadeIn::create(getDuration() * TENTACLE_FADE_IN_CORRECTION_VALUE);
	getRangeSprite()->runAction(action);

	return;
}

// �˼��� �� �����Ϳ��� �ڱ� �����θ� �����ִ� �Լ�.
void Tentacle::MakeTentacleDead()
{
	getMapPointer()->removeChild(this);

	return;
}

// CollideManager���� �ڽ��� ������ ��ġ�� ���� �ݰ��� �Ѱ��ְ� �÷��̾�� �������� �ִ� �Լ�.
void Tentacle::CheckTentacleHit()
{
	getInnerCollideManager()->CheckTentacleAttack(getCreatePosition(), TENTACLE_ATTACK_RANGE, getDamage(), getMapPointer());
	return;
}
