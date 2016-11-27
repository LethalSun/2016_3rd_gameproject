#pragma once
class AnimationMaker;
class Skill;

class PlayerCharacter :public Sprite
{
public:
	static PlayerCharacter* create();
	virtual bool init();

	PlayerCharacter();
	~PlayerCharacter();

private:
	//체력
	int m_MaxHP;
	int m_HP;

	//마나
	int m_MaxSP;
	int m_SP;

	//이동방향
	int m_Direction;
	int m_BeforeDirection;

	//캐릭터의 상태
	int m_State;
	int m_BeforeState;

	//스킬 일단 스킬의 포인터를 정
	Skill* m_DefenseSkill;
	Skill* m_AttackSkill;

	//애니메이션을 만드는 변수
	AnimationMaker* animationMaker;
};
