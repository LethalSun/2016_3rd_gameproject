#pragma once
class AnimationMaker;
class Skill;

class PlayerCharacter :public Sprite
{
public:
	static PlayerCharacter* create();
	virtual bool init();

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
	AnimationMaker* animationMaker;
};
