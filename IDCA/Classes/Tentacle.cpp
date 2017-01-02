#include "pch.h"
#include "Tentacle.h"
#include "SimpleAudioEngine.h"

bool Tentacle::init(const Vec2 initPosition, const float duration, const float damage, TMXTiledMap* mapPointer)
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
	
	MakeCautionRange();

	scheduleUpdate();

	return true;
}

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

void Tentacle::MakeTentacleAnimation()
{
	setTentacleSprite(Sprite::createWithSpriteFrameName("AncientTreeE0.png"));
	getTentacleSprite()->setPosition(getCreatePosition());
	addChild(getTentacleSprite());

	setTentacleAnimation(Animation::create());
	getTentacleAnimation()->setDelayPerUnit(0.3f);

	for (int i = 0; i < 10; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("AncientTreeE%d.png", i));
		if (!frame)
		{
			break;
		}
		getTentacleAnimation()->addSpriteFrame(frame);
	}

	setTentacleAnimate(Animate::create(getTentacleAnimation()));
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Tentacle::MakeTentacleDead, this));
	auto seqAction = Sequence::create(getTentacleAnimate(), callfunc, nullptr);
	getTentacleSprite()->runAction(seqAction);

	return;
}

void Tentacle::MakeCautionRange()
{
	auto rangeSprite = Sprite::create("Monster/range.png");
	rangeSprite->setPosition(getCreatePosition());
	rangeSprite->setOpacity(0);
	addChild(rangeSprite);

	auto action = FadeIn::create(getDuration() * 1.7f);
	rangeSprite->runAction(action);

	return;
}

void Tentacle::MakeTentacleDead()
{
	getMapPointer()->removeChild(this);
	//auto action = RemoveSelf::create(false); 
	//this->runAction(action);
	//setIsAttackEnd(true);
	//this->removeFromParentAndCleanup(false);
	return;
}
