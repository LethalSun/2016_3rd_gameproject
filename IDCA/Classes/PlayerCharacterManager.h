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
	void			 setPlayerPosition(Vec2);
	int				 getState();

	//��ǲ���̾�� ��ǲ���� �о���� �Լ�
	void GetInput(int* input);
	void GetUnitVac(int* input);

	//������Ʈ �Լ�
	void update(float dt);

	PlayerCharacterManager();
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

	//ĳ������ ������
	PlayerCharacter* m_pCharacter;
};
