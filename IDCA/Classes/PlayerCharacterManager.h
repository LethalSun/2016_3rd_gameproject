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

	//��ǲ���̾�� ��ǲ���� �о���� �Լ�
	void GetInput();

	//������Ʈ �Լ�
	void update(float dt);

	PlayerCharacterManager();
	~PlayerCharacterManager();
private:

	//��ǲ��
	int* m_pInput;

	//������Ʈ ��
	int m_State;

	//���Ⱚ
	int m_direction;

	//ĳ������ ���¸� ��ǲ���κ��� ����Ѵ�.
	void CalculatePlayerCharacterState();

	//�׷��� ĳ������ ���¸� �������ش�.
	void SetPlayerCharacterState();

	//ĳ������ ������ ������ �ش�
	void SetPlayerCharacterDirection();

	//������Ʈ����
	int PlayerCharacterState;

	//ĳ������ ������
	PlayerCharacter* m_pCharacter;
};
