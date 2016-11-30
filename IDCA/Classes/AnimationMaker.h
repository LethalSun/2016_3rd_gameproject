/************************************************************************/
/*
CLASS		: AnimationMaker
Author		: 김현우
역할			: 각각의 캐릭터, 에너미가 이 클래스의 인스턴스를 갖고 있고 애니메이션을 자신에게
			  애드해서 애니메이션을 만든다. 그리고 애니메이션이 중인지 확인하는 함수를 갖고있고 이 함수는 애니메이션이
			  정지면 0, 공격이면 1, 이동이면 2, 스킬이면 3을 반환한다.

최종 수정일자	:
최종 수정자	:
최종 수정사유	:
Comment		:
*/
/************************************************************************/
#pragma once
class AnimationMaker :public Node
{
public:
	static AnimationMaker* create(const char *fileName, const char *fileExtention);

	virtual bool init(const char *fileName, const char *fileExtention);

	//어떤 애니메이션인지 설정
	void SetAnimationAttack();
	void SetAnimationMove();
	void SetAnimationStop();
	void SetAnimationSkill();

	//애니메이션을 더한다.
	bool AddAnimation(int directionNum);

	//애니메이션 중인지 확인한다.
	int IsAnimationContinued();

	AnimationMaker() = default;
	~AnimationMaker() = default;

private:
	//애니메이션이 시작하고 끝날때 호출되는 함수.
	void AnimationOn();
	void AnimationOff();

	//프레임 이름을 만드는 함수
	void MakeAnimationFrameName(int fileNumber);

	//애니메션중인지 갖고있는 변수
	bool m_IsAnimationOn;

	//파일 확장자
	char m_FileNameExtention[10];

	//파일 이름
	char m_FileName[100];

	//상태를 저장하고 있는 변수
	int m_State;

	//프레임을 불러올 때 사용하는 변수들
	char m_FrameNameBuffer[256];

	Animation *m_pAnimation;

	Animate *m_pAnimate;

	SpriteFrame * m_pFrame;

	char* m_ActionName[4];

	float m_AnimationSpeed;
};
