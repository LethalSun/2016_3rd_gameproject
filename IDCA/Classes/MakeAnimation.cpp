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
	for (int i = imageStartNumber; i < imageStartNumber + 10; i++)
	{
		sprintf(m_Buffer, "%smove%d%s", m_FrameName, i, m_FileNameExtention);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		if (frame == nullptr)
		{
			break;
		}
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
	for (int i = imageStartNumber; i < imageStartNumber + 10; i++)
	{
		sprintf(m_Buffer, "%shit%d%s", m_FrameName, i, m_FileNameExtention);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_Buffer);
		if (frame == nullptr)
		{
			break;
		}
		animFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animFrame, TEMP_DEFINE::HIT_ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);
	return m_pAnimate;
}