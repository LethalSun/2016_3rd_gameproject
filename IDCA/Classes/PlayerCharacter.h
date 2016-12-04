#pragma once
class AnimationMaker;
class Skill;

class PlayerCharacter :public Node
{
public:
	//� �������� �Է��� �޴´�.
	static PlayerCharacter* create(const char * fileName, const char * fileExtention);
	virtual bool init(const char * fileName, const char * fileExtention);

	//ĳ������ ���¸� Ȯ���ϰ� �����ϴ� �Լ�
	int GetState();

	void SetState(int state);

	//ĳ������ ������ Ȯ���ϰ� �����ϴ� �Լ�
	int GetDirection();

	void SetDirection(int direction);

	//ĳ������ ü���� Ȯ���ϰ� �����ϴ� �Լ�
	int GetHP();

	void SetHP(int hp);

	//ĳ������ ������ Ȯ���ϰ� �����ϴ� �Լ�
	int GetSP();

	void SetSP(int sp);

	//������Ʈ �Լ�
	void update(float dt);

	//����
	void Attack();

	//�̵�
	void Move();

	//����
	void stop();

	//��ų
	void skill();

	//������ �������� Ȯ���ϴ� �Լ�
	void CheckStopState();

	PlayerCharacter();
	~PlayerCharacter();

private:
	//ü��
	int m_MaxHP;
	int m_HP;

	//����
	int m_MaxSP;
	int m_SP;

	//�̵�����
	int m_Direction;
	int m_BeforeDirection;

	//ĳ������ ����
	int m_State;
	int m_BeforeState;

	//��ų�� ������
	Skill* m_DefenseSkill;
	Skill* m_AttackSkill;

	//�ִϸ��̼��� ����� �����ϴ� ����
	AnimationMaker* m_pAnimationMaker;

	//�ִϸ��̼��� �������� �ϴ��� Ȯ���ϴ� �Լ�
	bool IsAttackContinued();
	bool IsMoveContinued();

	//���� �������� ���¿� ������ �����ϴ� �Լ�
	void SaveBeforeStateAndDirection();
};
