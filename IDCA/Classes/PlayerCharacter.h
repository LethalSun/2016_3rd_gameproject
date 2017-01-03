#pragma once
class AnimationMaker;
class Skill;
#include <functional>

typedef std::function <void(const char*, Vec2, Vec2, Vec2, Vec2, bool)> pFunc;

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
	//�������� Ȯ���ϰ� �����ϴ� �Լ�
	int GetDamage();
	void SetDamage(int);

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

	//���� ��Ŀ����Ʈ�� Ȯ��,�����ϴ� �Լ�
	Vec2 GetAttackAnchorPoint();
	void SetAttackAnchorPoint(Vec2);

	//�ǰ��� ��Ŀ����Ʈ�� Ȯ��,�����ϴ� �Լ�
	Vec2 GetBodyAnchorPoint();
	void SetBodyAnchorPoint(Vec2);

	//������ ������ Ȯ��,�����ϴ� �Լ�
	Vec2 GetAttackRange();

	//�ǰ��� ������ Ȯ��,�����ϴ� �Լ�
	Vec2 GetBodyRange();

	//����׿� �����ǰ�����Ʈ Ȯ���ϴ� �Խ�
	void SetAttackAnchorPointForMakeDebugBox(Vec2);
	void SetBodyAnchorPointForMakeDebugBox(Vec2);

	//������ üũ �ߴ��� Ȯ���ϴ� �Լ�.
	bool IsAttackChecked();
	void SetAttackChecked();

	//�浹(������ �ްų� ������)�ϰ�� �浹 �Ŵ��� ���� ȣ�� �Ǵ� �Լ�
	void WhenCollided(int, int, int);

	//�ִϸ��̼��� �������� �ϴ��� Ȯ���ϴ� �Լ�
	bool IsAttackContinued();
	bool IsMoveContinued();
	bool IsSkillAttackContinued();
	//������ �޾����� ü���� ���� ��Ű�� �Լ�
	bool SetAttackedDamage(int);
	PlayerCharacter(const Vec2, const Vec2);
	~PlayerCharacter();

	//��ų�� �ߵ��Ǿ����� ȣ��Ǵ� �Լ������͸� �޾ƿ��� �κ�.
	void GetFunc(pFunc);

private:
	//ü��
	//TODO :ü�·��̺� ǥ���ϱ�.
	int m_MaxHP;
	int m_HP;
	Label* m_pHPLabel;

	//����
	int m_MaxSP;
	int m_SP;
	Label* m_pSPLabel;

	//������
	int m_Damage;

	//�̵�����
	int m_Direction;
	int m_BeforeDirection;

	//ĳ������ ����
	int m_State;
	int m_BeforeState;

	//��ų�� ������
	Skill* m_DefenseSkill;
	Skill* m_AttackSkill;

	//�����̻�����
	int m_Mezz;

	//���ݰ� �ǰݹ����� �±�
	const int m_RedBoxTag;
	const int m_GreenBoxTag;

	//�ִϸ��̼��� ����� �����ϴ� ����
	AnimationMaker* m_pAnimationMaker;

	//���� �������� ���¿� ������ �����ϴ� �Լ�
	void SaveBeforeStateAndDirection();

	//�ǰݹ����� ���ݹ����� ������ ǥ���ϴ� �Լ�
	void MakeBox(Vec2 position, Vec2 boxInfo, const int);

	//ü�¹ڽ��� ����� �Լ�.
	int MakeHPBox();
	//ĳ������ �ǰݹ��� �ǰ���,���ݹ��� �������� �����ϴ� ����
	Vec2 m_AttackAnchorPoint;
	Vec2 m_AttackAnchorPointForDebugBox;
	const Vec2 m_AttackRange;

	Vec2 m_BodyAnchorPoint;
	Vec2 m_BodyAnchorPointForDebugBox;
	const Vec2 m_BodyRange;

	//���������� �ߴ��� Ȯ���ϴ� ����(false�϶��� �浹 �Ŵ������� ������ ��)
	bool m_AttackChecked;

	Label* m_pLabel;
};
