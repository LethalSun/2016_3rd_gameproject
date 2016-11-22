/************************************************************************/
/*
CLASS			: Character
Author			: 김현우
역할			: Playable Character와 Enemy Character의 추상클래스.
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once

#pragma once
class MakeAnimation;
class Character :public Sprite
{
public:
	static Character *create(const char const* filename, const char const* extention);
	void initOptions(const char const* filename, const char const* extention);

	void SetInput(int inputFromScene);
	//입력에 따라서 현재의 상태를 파악한다.
	void CheckCharacterState();
	//공격모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Attack(float dt);
	//이동모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Move(float dt);
	//정지모션을 스프라이트를 상속받은 이클래스에 넣어준다.
	void Stop(float dt);
	//매프레임마다 이스프라이트에 관련한 것들을 갱신한다. 상태 파악->모션
	void update(float dt);
	//스프라이트 캐쉬에 이미지를 올린다.
	void AddSpriteFramesWithFile(const char * filename);
	void AttackOff();
	void MoveOff();
	void StopOff();
	void AttackOn();
	void MoveOn();
	void StopOn();
	//캐릭터의 상태를 알아볼때 사용할수 있는 함수
	Vec2 GetCurrentDitection();
	Vec2 GetAttackRange();
	int GetCharacterState();
	int GetCharacterHP();
	//캐릭터의 체력을 변경하는 함수
	void SetHP(int hp);
	//체력바를 만드는 함수
	void MakeHpBar();
private:
	//체력
	int m_CurHP;
	//공격범위
	Vec2 m_AttackRange;
	//방향을 정할때 쓰는 함수
	bool IsTopOn(int m_MoveInput);
	bool IsBottomOn(int m_MoveInput);
	bool IsLeftOn(int m_MoveInput);
	bool IsRightOn(int m_MoveInput);
	bool IsErrorInput(int m_MoveInput);
	//공격,이동,정지 상태를 나타내는 변수
	int m_State;
	int m_BeforeState;
	//애니메이션중인지 아닌지를 나타내는 변수
	bool m_ActionAnimationOn;
	bool m_MoveAnimationOn;
	bool m_StopAnimationOn;
	//입력플래그를 처리하기 위한 변수
	int m_Input;
	int m_ActionInput;
	int m_MoveInput;
	int m_CurDirection;
	int m_BeforeDirection;
	int m_UnitVector[2];
	//애니메이션을 만들어주는 멤버
	MakeAnimation *m_pMakeAnimation;

	Character();
	~Character();
};
