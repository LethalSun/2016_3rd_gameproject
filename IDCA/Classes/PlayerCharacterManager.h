#pragma once
class PlayerCharacter;

class PlayerCharacterManager :public Node
{
public:
	//생성하는 함수
	static PlayerCharacterManager* create(const char * fileName, const char * fileExtention);
	virtual bool init(const char * fileName, const char * fileExtention);

	//캐릭터의 포인터를 멤버변수로 가지고 있고 그걸 반환한다
	PlayerCharacter* GetCharacter();
	Vec2			 getPlayerPosition();
	void			 setPlayerPosition(Vec2 position, Vec2 backgroundPosition);

	//상태를 확인할수 있는 함수
	int				 getState();

	//인풋레이어에서 인풋값을 읽어오는 함수
	void GetInput(int* input);
	void GetUnitVac(int* input);

	//업데이트 함수
	void update(float dt);

	//생성자 소멸자
	PlayerCharacterManager(const Vec2 AttackRange, const Vec2 BodyRange);
	~PlayerCharacterManager();

private:

	//인풋값
	int* m_pInput;

	int* m_pUnitVec;

	//스테이트 값
	int m_State;

	//방향값
	int m_direction;

	//캐릭터의 상태를 인풋으로부터 계산한다.
	void CalculatePlayerCharacterState();

	//그래서 캐릭터의 상태를 설정해준다.
	void SetPlayerCharacterState();

	//캐릭터의 방향을 인풋으로 부터 계산한다.
	void CalculatePlayerCharacterDirection();

	//캐릭터의 방향을 설정해 준다
	void SetPlayerCharacterDirection();

	//공격과 피격범위의 태그
	const int m_RedBoxTag;
	const int m_GreenBoxTag;
	//공격과 피격범위의 값 과 중심값
	Vec2 m_AttackAnchorPoint;
	Vec2 m_AttackAnchorPointForDebugBox;
	const Vec2 m_AttackRange;

	Vec2 m_BodyAnchorPoint;
	Vec2 m_BodyAnchorPointForDebugBox;
	const Vec2 m_BodyRange;

	/*공격범위의 중심 AttackAnchorpoint 와 피격범위의 중심인 BodyAnchorPoint를
	계산하고 반환하는 함수*/
	void CalculateAnchorPointForCollide();
	void CalculateAttackAnchorPoint();
	void CalculateBodyAnchorPoint();

	//캐릭터의 포인터
	PlayerCharacter* m_pCharacter;

	//캐릭터의 초기 위치
	Vec2 m_worldPosition;

	//상태조건 확인 함수
	bool IsInputAttackState();
	bool IsInputStopState();
	bool IsInputMoveStartState();
	bool IsInputMoveHoldState();

	//방향 조건 확인 함수
	bool IsUnitVecTop();
	bool IsUnitVecTopRight();
	bool IsUnitVecRight();
	bool IsUnitVecBottomRight();
	bool IsUnitVecBottom();
	bool IsUnitVecBottomLeft();
	bool IsUnitVecLeft();
	bool IsUnitVecTopLeft();
};
