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
	void			 setPlayerPosition(Vec2);
	int				 getState();

	//인풋레이어에서 인풋값을 읽어오는 함수
	void GetInput(int* input);
	void GetUnitVac(int* input);

	//업데이트 함수
	void update(float dt);

	PlayerCharacterManager();
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

	//캐릭터의 포인터
	PlayerCharacter* m_pCharacter;
};
