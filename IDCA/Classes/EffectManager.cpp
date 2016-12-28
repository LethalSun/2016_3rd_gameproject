#include "pch.h"
#include "EffectManager.h"


void EffectManager::makeEffect(int damage)
{
	
	auto effect = Sprite::create("Effect//effect.png");
	
	effect->setPosition(Vec2(0, 50));
	


	addChild(effect);
	



}


bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;

	}

	return true;

}

