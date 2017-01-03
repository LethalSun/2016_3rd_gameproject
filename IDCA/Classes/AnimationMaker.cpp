#include "pch.h"
#include "AnimationMaker.h"

//생성
AnimationMaker * AnimationMaker::create(const char * fileName, const char * fileExtention)
{
	auto pMaker = new(std::nothrow)AnimationMaker();
	if (pMaker && pMaker->init(fileName, fileExtention))
	{
		pMaker->autorelease();
		return pMaker;
	}
	else
	{
		delete pMaker;
		pMaker = nullptr;
		return nullptr;
	}
}

//생성하는 함수에서 초기화를 진행하는 함수.
bool AnimationMaker::init(const char * fileName, const char * fileExtention)
{
	if (!Node::init())
	{
		return false;
	}
	sprintf(m_FileName, "%s", fileName);
	sprintf(m_FileNameExtention, "%s", fileExtention);

	m_pSprite = Sprite::create();
	addChild(m_pSprite);
	m_IsAnimationOn = false;
	m_State = STATE::STOP;

	m_pAnimation = nullptr;
	m_pAnimate = nullptr;

	return true;
}

//애니메이션을 만들고 더해준다 단 그림을 매번 만들지 않고 저장하고 불러온다.

Sprite* AnimationMaker::AddAnimation(int directionNum)
{
	MakeAnimationName(directionNum);

	auto animationCache = AnimationCache::getInstance();

	auto cachedAnimation = animationCache->getAnimation(m_AnimationName);

	if (cachedAnimation == nullptr)
	{
		int imageStartNumber = directionNum * MAX_FRAME_NUM;

		Vector<SpriteFrame*> animationFrame;

		for (int i = imageStartNumber; i < imageStartNumber + MAX_FRAME_NUM; ++i)
		{
			MakeAnimationFrameName(i);
			m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_FrameNameBuffer);

			if (m_pFrame == nullptr)
			{
				break;
			}

			animationFrame.pushBack(m_pFrame);
		}

		m_pAnimation = Animation::createWithSpriteFrames(animationFrame, m_AnimationSpeed);
		animationCache->addAnimation(m_pAnimation, m_AnimationName);
		m_pAnimate = Animate::create(m_pAnimation);
	}
	else
	{
		m_pAnimate = Animate::create(cachedAnimation);
	}

	auto animationOn = CallFunc::create(CC_CALLBACK_0(AnimationMaker::AnimationOn, this));
	auto animationOff = CallFunc::create(CC_CALLBACK_0(AnimationMaker::AnimationOff, this));
	auto sequence = Sequence::create(animationOn, m_pAnimate, animationOff, NULL);

	sequence->setTag(ANIMATION_TAG);

	m_pSprite->stopActionByTag(ANIMATION_TAG);
	m_pSprite->runAction(sequence);

	return m_pSprite;
}

int AnimationMaker::whichAnimationContinued()
{
	if (m_IsAnimationOn == true)
	{
		return m_State;
	}
	else
	{
		return -1;
	}
}

Sprite * AnimationMaker::GetSprite()
{
	return m_pSprite;
}

//어떤 애니메이션인지 설정 animationMaker->SetAnimationAttack(); 처럼 사용한다.
void AnimationMaker::SetAnimationAttack()
{
	m_State = STATE::ATTACK;
}

void AnimationMaker::SetAnimationMove()
{
	m_State = STATE::MOVE;
}

void AnimationMaker::SetAnimationStop()
{
	m_State = STATE::STOP;
}

void AnimationMaker::SetAnimationSkill()
{
	m_State = STATE::SKILL;
}

//애니메이션을 시작하고 끝날때 변수를 바꿔주는 함수
void AnimationMaker::AnimationOn()
{
	m_IsAnimationOn = true;
}

void AnimationMaker::AnimationOff()
{
	m_IsAnimationOn = false;
}

//애니메이션을 만들기위해 파일이름을 만든다.
void AnimationMaker::MakeAnimationFrameName(int fileNumber)
{
	if (m_State == STATE::ATTACK)
	{
		sprintf(m_FrameNameBuffer, "%sA%d%s", m_FileName, fileNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::MOVE)
	{
		sprintf(m_FrameNameBuffer, "%sM%d%s", m_FileName, fileNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::SKILL)
	{
		sprintf(m_FrameNameBuffer, "%sA%d%s", m_FileName, fileNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::STOP)
	{
		sprintf(m_FrameNameBuffer, "%sS%d%s", m_FileName, fileNumber, m_FileNameExtention);
	}

	m_AnimationSpeed = ANIMATION_SPEED;
}

//애니메이션을 캐쉬해놓고 불러올때 쓸 이름을 만드는 함수.
void AnimationMaker::MakeAnimationName(int directionNumber)
{
	if (m_State == STATE::ATTACK)
	{
		sprintf(m_AnimationName, "%sA%d%s", m_FileName, directionNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::MOVE)
	{
		sprintf(m_AnimationName, "%sM%d%s", m_FileName, directionNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::SKILL)
	{
		sprintf(m_AnimationName, "%sK%d%s", m_FileName, directionNumber, m_FileNameExtention);
	}
	else if (m_State == STATE::STOP)
	{
		sprintf(m_AnimationName, "%sS%d%s", m_FileName, directionNumber, m_FileNameExtention);
	}
}