#include "pch.h"
#include "PlayerMenu.h"
#include "PlayerCharacter.h"
#include "Skill.h"

PlayerMenu* PlayerMenu::create(PlayerCharacter* player)
{
	auto self = new (std::nothrow) PlayerMenu();

	if (self && self->init(player))
	{
		self->autorelease();
		return self;
	}
	else
	{
		delete(self);
		self = nullptr;
		return self;
	}
		
}


bool PlayerMenu::init(PlayerCharacter* player)
{
	if (!Node::init())
	{
		return false;
	}

	m_pFace = Sprite::create("Board/archbishop.PNG");
	m_pFace->setScale(2);
	m_pFace->setAnchorPoint(Vec2(0, 1));
	m_pFace->setPosition(10, 750);

	m_pPlayer = player;
	m_pSkill1 = player->GetAttackSkillPointer();
	
	skill1_MaxCoolTime = m_pSkill1->GetMaxCooltime();


	addChild(m_pFace);
	

	MakeMaxHPBox();

	MakeSkillBox();




	scheduleUpdate();
	return true;
}

void PlayerMenu::update(float dt)
{
	MakeHPBox();
	CheckCoolTime(m_pSkill1);



}

PlayerMenu::PlayerMenu()
{

}


PlayerMenu::~PlayerMenu()
{

}




int PlayerMenu::MakeHPBox()
{
	if (m_pFace->getChildByTag(GREEN_BOX_SOLID_TAG) != nullptr)
	{
		m_pFace->removeChildByTag(GREEN_BOX_SOLID_TAG);
	}
	



	auto hpCurrent = Sprite::create("Board/hp.png");
	hpCurrent->setPosition(Vec2(m_pFace->getContentSize().width + 20, m_pFace->getContentSize().height / 2));
	hpCurrent->setAnchorPoint(Vec2(0,0));
	
	auto hpRatio = ((float)m_pPlayer->GetHP() / (float)m_pPlayer->GetMaxHP());
	
	hpCurrent->setScaleY(0.8);
	hpCurrent->setScaleX(hpRatio*0.8);

	m_pFace->addChild(hpCurrent, 0, GREEN_BOX_SOLID_TAG);

	return 0;
}
int PlayerMenu::MakeMaxHPBox()
{


	auto hpMax = Sprite::create("Board/hpMax.png");
	hpMax->setPosition(Vec2(m_pFace->getContentSize().width + 20, m_pFace->getContentSize().height / 2));

	hpMax->setAnchorPoint(Vec2(0, 0));
	hpMax->setScaleY(0.8);
	hpMax->setScaleX(0.8);
	m_pFace->addChild(hpMax, 1 ,RED_BOX_SOLID_TAG);

	return 0;
}


void PlayerMenu::MakeSkillBox()
{
	auto hammerSkill = Sprite::create("Hammer.png");
	hammerSkill->setScale(0.2);

	auto size = hammerSkill->getContentSize();
	auto position = size * 0.2 * 2;
	position.height *= -1;

	hammerSkill->setPosition(hammerSkill->getContentSize().width*0.5, hammerSkill->getPosition().y );
	

	hammerSkill->setName("hammer");
	m_pFace->addChild(hammerSkill);

	auto hammerGray = Sprite::create("HammerGray.png");
	hammerGray->setScale(0.2);
	hammerGray->setPosition(hammerSkill->getPosition());
	hammerGray->setName("hammerGray");
	m_pFace->addChild(hammerGray);


}

void PlayerMenu::CheckCoolTime(Skill* skill)
{
	auto remainCoolTime = skill->GetRemainCooltime();

	if (remainCoolTime == 0)
	{
		auto hammerGray = m_pFace->getChildByName("hammerGray");
		hammerGray->setVisible(false);

		auto biggerAction = ScaleTo::create(0.3f, 1.25f *0.2);
		auto smallerAction = ScaleTo::create(0, 0.8f *0.2);

		auto seqAction = Sequence::create(biggerAction, smallerAction, nullptr);

		auto hammer = m_pFace->getChildByName("hammer");
		hammer->runAction(seqAction);

	}
	else
	{
		auto hammerGray = m_pFace->getChildByName("hammerGray");
		hammerGray->setVisible(true);

	}



	

	
}