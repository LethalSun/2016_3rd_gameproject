#include "pch.h"
#include "PlayerMenu.h"
#include "PlayerCharacter.h"

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



	scheduleUpdate();
	addChild(m_pFace);
	

	MakeMaxHPBox();

	MakeSkillBox();

	return true;
}

void PlayerMenu::update(float dt)
{
	MakeHPBox();


	//////юс╫ц
	auto hammer = m_pFace->getChildByName("hammer");
	auto position = hammer->getPosition();

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
	
	auto HPBarStart = Vec2(m_pFace->getContentSize().width +20, m_pFace->getContentSize().height/2);

	auto HPBarEnd = Vec2(HPBarStart.x + 200 , HPBarStart.y + 30);

	auto hpRatio = ((float) m_pPlayer->GetHP() / (float) m_pPlayer->GetMaxHP());

	auto range = Vec2(HPBarStart.x + 200*hpRatio, HPBarStart.y + 30.f);



	auto box = DrawNode::create();


	box->drawSolidRect(HPBarStart, range, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	m_pFace->addChild(box, 0, GREEN_BOX_SOLID_TAG);

	return 0;
}
int PlayerMenu::MakeMaxHPBox()
{

	auto HPBarStart = Vec2(m_pFace->getContentSize().width +20, m_pFace->getContentSize().height / 2);
	auto HPBarEnd = Vec2(HPBarStart.x + 200, HPBarStart.y + 30);

	auto box = DrawNode::create();
	box->drawSolidRect(HPBarStart, HPBarEnd, Color4F(1.0f, 0.0f, 0.0f, 1.0f));

	m_pFace->addChild(box,0,RED_BOX_SOLID_TAG);

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
	m_pFace->addChild(hammerSkill,5);


}