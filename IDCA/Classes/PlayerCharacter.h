#pragma once
class AnimationMaker;
class Skill;
#include <functional>

typedef std::function <void(const char*, Vec2, Vec2, Vec2, Vec2, bool)> pFunc;

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
	//데미지를 확인하고 설정하는 함수
	int GetDamage();
	void SetDamage(int);

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

	//공격 앵커포인트를 확인,설정하는 함수
	Vec2 GetAttackAnchorPoint();
	void SetAttackAnchorPoint(Vec2);

	//피격의 앵커포인트를 확인,설정하는 함수
	Vec2 GetBodyAnchorPoint();
	void SetBodyAnchorPoint(Vec2);

	//공격의 범위를 확인,설정하는 함수
	Vec2 GetAttackRange();

	//피격의 범위를 확인,설정하는 함수
	Vec2 GetBodyRange();

	//디버그용 공격피격포인트 확인하는 함스
	void SetAttackAnchorPointForMakeDebugBox(Vec2);
	void SetBodyAnchorPointForMakeDebugBox(Vec2);

	//공격을 체크 했는지 확인하는 함수.
	bool IsAttackChecked();
	void SetAttackChecked();

	//충돌(공격을 받거나 했을때)일경우 충돌 매니져 에서 호출 되는 함수
	void WhenCollided(int, int, int);

	//애니메이션을 계속해줘야 하는지 확인하는 함수
	bool IsAttackContinued();
	bool IsMoveContinued();
	bool IsSkillAttackContinued();
	//공격을 받았을때 체력을 감소 시키는 함수
	bool SetAttackedDamage(int);
	PlayerCharacter(const Vec2, const Vec2);
	~PlayerCharacter();

	//스킬이 발동되었을때 호출되는 함수포인터를 받아오는 부분.
	void GetFunc(pFunc);

private:
	//체력
	//TODO :체력레이블 표시하기.
	int m_MaxHP;
	int m_HP;
	Label* m_pHPLabel;

	//마나
	int m_MaxSP;
	int m_SP;
	Label* m_pSPLabel;

	//데미지
	int m_Damage;

	//이동방향
	int m_Direction;
	int m_BeforeDirection;

	//캐릭터의 상태
	int m_State;
	int m_BeforeState;

	//스킬의 포인터
	Skill* m_DefenseSkill;
	Skill* m_AttackSkill;

	//상태이상정보
	int m_Mezz;

	//공격과 피격범위의 태그
	const int m_RedBoxTag;
	const int m_GreenBoxTag;

	//애니메이션을 만들고 관리하는 변수
	AnimationMaker* m_pAnimationMaker;

	//이전 프레임의 상태와 방향을 저장하는 함수
	void SaveBeforeStateAndDirection();

	//피격범위와 공격범위를 디버깅시 표시하는 함수
	void MakeBox(Vec2 position, Vec2 boxInfo, const int);

	//체력박스를 만드는 함수.
	int MakeHPBox();
	//캐릭터의 피격범위 피격점,공격범위 공격점을 저장하는 변수
	Vec2 m_AttackAnchorPoint;
	Vec2 m_AttackAnchorPointForDebugBox;
	const Vec2 m_AttackRange;

	Vec2 m_BodyAnchorPoint;
	Vec2 m_BodyAnchorPointForDebugBox;
	const Vec2 m_BodyRange;

	//공격판정을 했는지 확인하는 변수(false일때만 충돌 매니져에서 판정을 함)
	bool m_AttackChecked;

	Label* m_pLabel;
};
