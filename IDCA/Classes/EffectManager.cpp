#include "pch.h"
#include "EffectManager.h"


void EffectManager::MakeEffect(int damage)
{
	
	m_pEffect = Sprite::create("Effect/effect.png");
	
	m_pEffect->setPosition(Vec2(0, 50));
	m_pEffect->setScale(1.5f);
	addChild(m_pEffect);
	
	
	auto damageStr = itoa(damage,damageBuf,10);
	m_pDamageLabel = LabelBMFont::create( damageStr, "Effect/damageFont.fnt");
	m_pDamageLabel->setPosition(Vec2(30, 0));
	m_pDamageLabel->setScale(2.0f);
	m_pEffect->addChild(m_pDamageLabel);


	auto effectMove = MoveBy::create(0.8f, Vec2(0, 50.f));
	m_pEaseEffectMove = EaseElasticInOut::create(effectMove, 0.5f);

	auto callBack = CallFunc::create(CC_CALLBACK_0(EffectManager::afterEnd, this));
	auto sequence = Sequence::create(m_pEaseEffectMove, callBack,NULL);


	m_pEffect->runAction(sequence);
	

}

void EffectManager::afterEnd()
{
	//this->setposition(vec2(0, 0));
	removeChild(m_pEffect);
	removeChild(m_pDamageLabel);
}

bool EffectManager::init()
{
	if (!Node::init())
	{
		return false;

	}

	scheduleUpdate();
	return true;

}

