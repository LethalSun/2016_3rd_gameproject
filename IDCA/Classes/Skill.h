#pragma once

/************************************************************************/
/*
CLASS		: Skill
Author		: ������
����			: ��ų�� Ŭ���� ��ų������ ��ų���� �����͵��� �������ְ� ����ü�� ����� �Լ���
����� �ش�.
*/
/************************************************************************/
typedef std::function <void(const char*, Vec2, Vec2, Vec2, Vec2, bool)> pFunc;

class Skill :public Component
{
public:
	Skill();
	~Skill();

	static Skill* create(const char*, const char*, const char*, const char*);

	virtual bool init(const char*, const char*, const char*, const char*);

	//�������� �޾ƿ´�
	int GetDamage();
	//��ų�� ��밡������ �˾ƺ��� �Լ�
	bool IsSkillUsable();
	//��Ÿ�� ���� �Լ�
	float GetMaxCooltime();
	float GetRemainCooltime();

	//init
	void SetSkillOnOff(bool);
	void SetMaxCooltime(float);
	void SetDamage(int);

	//projectile info
	void SetStartPosition(Vec2);
	void SetDirection(Vec2);
	void SetMaxRange(Vec2);
	void SetColideRange(Vec2);

	void update(float);

	//��Ÿ���� ���� ��Ű�� �Լ�
	void IncreaseCooltime(float);

	//����ü ��� �Լ��� �޾ƿ��� �κ�
	void GetFunc(pFunc func);

	//��Ϲ��� �Լ��� ����Ѵ�
	void MakeProjectiles(bool);

private:
	//��ų �̸�
	String m_SkillName;

	bool m_IsUsable;
	float m_Cooltime;
	float m_MaxCooltime;
	int m_Damage;

	//�̹������� ���
	String m_UiImagePathUsable;
	String m_UiImagePathCoolDown;
	String m_projectileImagePath;

	//���� ��ġ
	Vec2 m_startPosition;
	//����
	Vec2 m_DirectionVec;
	//�ִ�� ���ư��� �Ÿ�
	Vec2 m_MaxRange;
	//�浹����
	Vec2 m_ColideRange;

	//����ü�� ������ִ� �Լ�
	pFunc MakeProjectile;
};
