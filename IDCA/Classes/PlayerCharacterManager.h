#pragma once
class PlayerCharacter;

class PlayerCharacterManager :public Node
{
public:
	//�����ϴ� �Լ�
	static PlayerCharacterManager* create(const char * fileName, const char * fileExtention);
	virtual bool init(const char * fileName, const char * fileExtention);

	//ĳ������ �����͸� ��������� ������ �ְ� �װ� ��ȯ�Ѵ�
	PlayerCharacter* GetCharacter();
	Vec2			 getPlayerPosition();
	void			 setPlayerPosition(Vec2 position, Vec2 backgroundPosition);

	//���¸� Ȯ���Ҽ� �ִ� �Լ�
	int				 getState();

	//��ǲ���̾�� ��ǲ���� �о���� �Լ�
	void GetInput(int* input);
	void GetUnitVac(int* input);

	//������Ʈ �Լ�
	void update(float dt);

	//������ �Ҹ���
	PlayerCharacterManager(const Vec2 AttackRange, const Vec2 BodyRange);
	~PlayerCharacterManager();

private:

	//��ǲ��
	int* m_pInput;

	int* m_pUnitVec;

	//������Ʈ ��
	int m_State;

	//���Ⱚ
	int m_direction;

	//ĳ������ ���¸� ��ǲ���κ��� ����Ѵ�.
	void CalculatePlayerCharacterState();

	//�׷��� ĳ������ ���¸� �������ش�.
	void SetPlayerCharacterState();

	//ĳ������ ������ ��ǲ���� ���� ����Ѵ�.
	void CalculatePlayerCharacterDirection();

	//ĳ������ ������ ������ �ش�
	void SetPlayerCharacterDirection();

	//���ݰ� �ǰݹ����� �±�
	const int m_RedBoxTag;
	const int m_GreenBoxTag;
	//���ݰ� �ǰݹ����� �� �� �߽ɰ�
	Vec2 m_AttackAnchorPoint;
	Vec2 m_AttackAnchorPointForDebugBox;
	const Vec2 m_AttackRange;

	Vec2 m_BodyAnchorPoint;
	Vec2 m_BodyAnchorPointForDebugBox;
	const Vec2 m_BodyRange;

	/*���ݹ����� �߽� AttackAnchorpoint �� �ǰݹ����� �߽��� BodyAnchorPoint��
	����ϰ� ��ȯ�ϴ� �Լ�*/
	void CalculateAnchorPointForCollide();
	void CalculateAttackAnchorPoint();
	void CalculateBodyAnchorPoint();

	//ĳ������ ������
	PlayerCharacter* m_pCharacter;

	//ĳ������ �ʱ� ��ġ
	Vec2 m_worldPosition;

	//�������� Ȯ�� �Լ�
	bool IsInputAttackState();
	bool IsInputStopState();
	bool IsInputMoveStartState();
	bool IsInputMoveHoldState();

	//���� ���� Ȯ�� �Լ�
	bool IsUnitVecTop();
	bool IsUnitVecTopRight();
	bool IsUnitVecRight();
	bool IsUnitVecBottomRight();
	bool IsUnitVecBottom();
	bool IsUnitVecBottomLeft();
	bool IsUnitVecLeft();
	bool IsUnitVecTopLeft();
};
