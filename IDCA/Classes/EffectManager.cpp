#include "pch.h"
#include "EffectManager.h"


void EffectManager::MakeEffect(int damage)
{
	
	auto effect = Sprite::create("Effect/effect.png");
	
	effect->setPosition(Vec2(0, 50));
	
	addChild(effect);
	
	auto effectMove = MoveBy::create(0.5f, Vec2(0, 50.f));
	m_pEaseEffectMove = EaseElasticInOut::create(effectMove, 0.5f);

	runAction(m_pEaseEffectMove);

}




bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;

	}

	return true;

}

