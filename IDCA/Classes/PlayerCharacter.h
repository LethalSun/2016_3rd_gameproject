#pragma once
class AnimationMaker;
class Skill;

class PlayerCharacter :public Node
{
public:
	//어떤 직업인지 입력을 받는다.
	static PlayerCharacter* create(const char * fileName, const char * fileExtention);
	virtual bool init(const char * fileName, const char * fileExtention);

	//캐릭터의 상태를 확인하고 설정하는 함수
	int GetState();

	void SetState(int state);

	//캐릭터의 방향을 확인하고 설정하는 함수
	int GetDirection();

	void SetDirection(int direction);

	//캐릭터의 체력을 확인하고 설정하는 함수
	int GetHP();

	void SetHP(int hp);

	//캐릭터의 마나를 확인하고 설정하는 함수
	int GetSP();

	void SetSP(int sp);

	//업데이트 함수
	void update(float dt);

	//공격
	void Attack();

	//이동
	void Move();

	//정지
	void stop();

	//스킬
	void skill();

	//공격이 끝났는지 확인하는 함수
	void CheckStopState();

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

	//스킬의 포인터
	Skill* m_DefenseSkill;
	Skill* m_AttackSkill;

	//애니메이션을 만들고 관리하는 변수
	AnimationMaker* m_pAnimationMaker;

	//애니메이션을 계속해줘야 하는지 확인하는 함수
	bool IsAttackContinued();
	bool IsMoveContinued();

	//이전 프레임의 상태와 방향을 저장하는 함수
	void SaveBeforeStateAndDirection();
};
