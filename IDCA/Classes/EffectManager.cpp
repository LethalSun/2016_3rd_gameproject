#include "pch.h"
#include "EffectManager.h"
#include "Define.h"

void EffectManager::MakeEffect(int damage)
{
	
	m_pEffect = Sprite::create(EFFECT_IMAGE);
	
	m_pEffect->setPosition(Vec2(EFFECT_POSITION_X, EFFECT_POSITION_Y));
	m_pEffect->setScale(EFFECT_SCALE);
	addChild(m_pEffect);
	
	
	auto damageStr = itoa(damage,damageBuf,10);
	m_pDamageLabel = LabelBMFont::create( damageStr, DAMAGE_FONT);
	m_pDamageLabel->setPosition(Vec2(LABEL_POSITION_X, LABEL_POSITION_Y));
	m_pDamageLabel->setScale(LABEL_SCALE);
	m_pEffect->addChild(m_pDamageLabel);


	auto effectMove = MoveBy::create(EFFECT_MOVE_TIME, Vec2(EFFECT_POSITION_X, EFFECT_POSITION_Y));
	m_pEaseEffectMove = EaseElasticInOut::create(effectMove, EFFECT_ELASTIC_TIME);

	auto callBack = CallFunc::create(CC_CALLBACK_0(EffectManager::afterEnd, this));
	auto sequence = Sequence::create(m_pEaseEffectMove, callBack,NULL);


	m_pEffect->runAction(sequence);
	

}

void EffectManager::afterEnd()
{
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

