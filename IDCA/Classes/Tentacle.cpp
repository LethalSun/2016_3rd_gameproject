#include "pch.h"
#include "Tentacle.h"
#include "SimpleAudioEngine.h"
#include "CollideManager.h"

// 촉수 초기화 함수.
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

// 초기화할 때 받았던 지연시간이 넘어가면 촉수 애니메이션을 소환하고 사운드를 재생한다.
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

// 촉수가 나오는 애니메이션을 만들고, 애니메이션 후의 과정을 처리하는 함수.
void Tentacle::MakeTentacleAnimation()
{
	setTentacleSprite(Sprite::createWithSpriteFrameName("AncientTreeE0.png"));
	getTentacleSprite()->setPosition(getCreatePosition());
	addChild(getTentacleSprite());

	setTentacleAnimation(Animation::create());
	getTentacleAnimation()->setDelayPerUnit(0.05f);

	for (int i = 0; i < 10; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("AncientTreeE%d.png", i));
		if (!frame)
		{
			break;
		}
		getTentacleAnimation()->addSpriteFrame(frame);
	}

	// 애니메이션 후, 촉수 타격이 들어갔는지 확인하고 자기 자신을 remove한다.
	setTentacleAnimate(Animate::create(getTentacleAnimation()));
	auto hitfunc = CallFunc::create(CC_CALLBACK_0(Tentacle::CheckTentacleHit, this));
	auto deadfunc = CallFunc::create(CC_CALLBACK_0(Tentacle::MakeTentacleDead, this));
	auto seqAction = Sequence::create(getTentacleAnimate(), hitfunc, deadfunc, nullptr);
	
	removeChild(getRangeSprite());
	getTentacleSprite()->runAction(seqAction);

	return;
}

// 촉수가 나오기 전 미리 범위를 알려주는 스프라이트를 띄우는 함수.
void Tentacle::MakeCautionRange()
{
	setRangeSprite(Sprite::create("Monster/range.png"));
	getRangeSprite()->setPosition(getCreatePosition());
	getRangeSprite()->setOpacity(0);
	this->reorderChild(getRangeSprite(), 0);
	addChild(getRangeSprite());

	auto action = FadeIn::create(getDuration() * 1.2f);
	getRangeSprite()->runAction(action);

	return;
}

// 촉수가 맵 포인터에서 자기 스스로를 지워주는 함수.
void Tentacle::MakeTentacleDead()
{
	getMapPointer()->removeChild(this);

	return;
}

// CollideManager에게 자신이 생성된 위치와 폭발 반경을 넘겨주고 플레이어에게 데미지를 주는 함수.
void Tentacle::CheckTentacleHit()
{
	getInnerCollideManager()->CheckTentacleAttack(getCreatePosition(), 90, 20, getMapPointer());
	return;
}
