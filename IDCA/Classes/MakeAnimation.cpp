#include "pch.h"
#include "MakeAnimation.h"
#include "TemporaryDefine.h"

bool MakeAnimation::init(const char * fileName, const char * fileNameExtention)
{
	if (!Node::init())
	{
		return false;
	}
	sprintf(m_FileNameExtention, "%s", fileNameExtention);
	sprintf(m_FrameName, "%s", fileName);
	m_pAnimateArr[MoveUp] = AnimationMove(1);
	m_pAnimateArr[MoveDown] = AnimationMove(2);
	m_pAnimateArr[MoveRight] = AnimationMove(4);
	m_pAnimateArr[MoveLeft] = AnimationMove(8);
	m_pAnimateArr[MoveUpLeft] = AnimationMove(9);
	m_pAnimateArr[MoveUpRight] = AnimationMove(5);
	m_pAnimateArr[MoveDownRight] = AnimationMove(6);
	m_pAnimateArr[MoveDownLeft] = AnimationMove(10);
	m_pAnimateArr[AttackUpUpLeft] = AnimationAttack(1);
	m_pAnimateArr[AttackLeftDownLeft] = AnimationAttack(8);
	m_pAnimateArr[AttackDownDownRight] = AnimationAttack(2);
	m_pAnimateArr[AttackRightUpRight] = AnimationAttack(4);
	m_pAnimateArr[StopUp] = AnimationStop(1);
	m_pAnimateArr[StopDown] = AnimationStop(2);
	m_pAnimateArr[StopRight] = AnimationStop(4);
	m_pAnimateArr[StopLeft] = AnimationStop(8);
	m_pAnimateArr[StopUpLeft] = AnimationStop(9);
	m_pAnimateArr[StopUpRight] = AnimationStop(5);
	m_pAnimateArr[StopDownRight] = AnimationStop(6);
	m_pAnimateArr[StopDownLeft] = AnimationStop(0);

	for (int i = 0; i < AnimateNum; ++i)
	{
		//addChild(m_pAnimateArr[i]);
	}

	return true;
}

MakeAnimation * MakeAnimation::create(const char * fileName, const char * fileNameExtention)
{
	MakeAnimation *pRet = new (std::nothrow) MakeAnimation();
	if (pRet && pRet->init(fileName, fileNameExtention))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//이동 애니메이션을 만든다.
Animate* MakeAnimation::AnimationMove(int direction)
{
	int imageStartNumber = direction * TEMP_DEFINE::NUM_OF_SPRITE_FILE_PER_ACTIONS;
	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 8; i++)
	{
		sprintf(m_Buffer, "%smove%d%s", m_FrameName, i, m_FileNameExtention);
		char buffer[256];
		sprintf(buffer, "inputKeyboard: %s", m_Buffer);
		cocos2d::log(buffer);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, TEMP_DEFINE::ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

//정지상태의 텍스쳐를 만든다.
Animate* MakeAnimation::AnimationStop(int direction)
{
	int imageStartNumber = direction % 10;
	Vector<SpriteFrame*> animFrame;
	sprintf(m_Buffer, "%sstop%d%s", m_FrameName, imageStartNumber, m_FileNameExtention);
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
	animFrame.pushBack(frame);
	m_pAnimation = Animation::createWithSpriteFrames(animFrame, TEMP_DEFINE::STOP_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

//공격 애니메이션을 만든다.
Animate* MakeAnimation::AnimationAttack(int direction)
{
	int imageStartNumber = (direction | TEMP_DEFINE::ACTIONS::ATTACK) * TEMP_DEFINE::NUM_OF_SPRITE_FILE_PER_ACTIONS;

	if (imageStartNumber < 170)
	{
		return nullptr;
	}

	Vector<SpriteFrame*> animFrame;
	for (int i = imageStartNumber; i < imageStartNumber + 7; i++)
	{
		sprintf(m_Buffer, "%shit%d%s", m_FrameName, i, m_FileNameExtention);
		char buffer[256];
		sprintf(buffer, "inputKeyboard: %s", m_Buffer);
		cocos2d::log(buffer);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		animFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, TEMP_DEFINE::HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}

Animate * MakeAnimation::GetAttackAnimation(int direction)
{
	if (direction == TEMP_DEFINE::ACTIONS::TOP || direction == TEMP_DEFINE::ACTIONS::TOP_LEFT)
	{
		return m_pAttackUpUpLeft;
	}
	else if (direction == TEMP_DEFINE::ACTIONS::LEFT || direction == TEMP_DEFINE::ACTIONS::BOTTOM_LEFT)
	{
		return m_pAttackLeftDownLeft;
	}
	else if (direction == TEMP_DEFINE::ACTIONS::BOTTOM || direction == TEMP_DEFINE::ACTIONS::BOTTOM_RIGHT)
	{
		return m_pAttackDownDownRight;
	}
	else if (direction == TEMP_DEFINE::ACTIONS::RIGHT || direction == TEMP_DEFINE::ACTIONS::TOP_RIGTH)
	{
		return m_pAttackRightUpRight;
	}

	return nullptr;
}

Animate * MakeAnimation::GetMoveAnimation(int direction)
{
	switch (direction)
	{
	case TEMP_DEFINE::ACTIONS::TOP:
	{
		return m_pMoveUp;
	}
	case TEMP_DEFINE::ACTIONS::TOP_LEFT:
	{
		return m_pMoveUpLeft;
	}
	case TEMP_DEFINE::ACTIONS::TOP_RIGTH:
	{
		return m_pMoveUpRight;
	}
	case TEMP_DEFINE::ACTIONS::RIGHT:
	{
		return m_pMoveRight;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM_RIGHT:
	{
		return m_pMoveDownRight;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM:
	{
		return m_pMoveDown;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM_LEFT:
	{
		return m_pMoveDownLeft;
	}
	case TEMP_DEFINE::ACTIONS::LEFT:
	{
		return m_pMoveLeft;
	}
	default:
	{
		return nullptr;
	}
	}
}

Animate * MakeAnimation::GetStopAnimation(int direction)
{
	switch (direction)
	{
	case TEMP_DEFINE::ACTIONS::TOP:
	{
		return m_pStopUp;
	}
	case TEMP_DEFINE::ACTIONS::TOP_LEFT:
	{
		return m_pStopUpLeft;
	}
	case TEMP_DEFINE::ACTIONS::TOP_RIGTH:
	{
		return m_pStopUpRight;
	}
	case TEMP_DEFINE::ACTIONS::RIGHT:
	{
		return m_pStopRight;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM_RIGHT:
	{
		return m_pStopDownRight;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM:
	{
		return m_pStopDown;
	}
	case TEMP_DEFINE::ACTIONS::BOTTOM_LEFT:
	{
		return m_pStopDownLeft;
	}
	case TEMP_DEFINE::ACTIONS::LEFT:
	{
		return m_pStopLeft;
	}
	default:
	{
		return nullptr;
	}
	}
	return nullptr;
}