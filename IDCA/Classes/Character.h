/************************************************************************/
/*
CLASS			: Character
Author			: ������
����			: Playable Character�� Enemy Character�� �߻�Ŭ����.
���� ��������	:
���� ������		:
���� ��������	:
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
	//�Է¿� ���� ������ ���¸� �ľ��Ѵ�.
	void CheckCharacterState();
	//���ݸ���� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Attack(float dt);
	//�̵������ ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Move(float dt);
	//��������� ��������Ʈ�� ��ӹ��� ��Ŭ������ �־��ش�.
	void Stop(float dt);
	//�������Ӹ��� �̽�������Ʈ�� ������ �͵��� �����Ѵ�. ���� �ľ�->���
	void update(float dt);
	//��������Ʈ ĳ���� �̹����� �ø���.
	void AddSpriteFramesWithFile(const char * filename);
	void AttackOff();
	void MoveOff();
	void StopOff();
	void AttackOn();
	void MoveOn();
	void StopOn();
	//ĳ������ ���¸� �˾ƺ��� ����Ҽ� �ִ� �Լ�
	Vec2 GetCurrentDitection();
	Vec2 GetAttackRange();
	int GetCharacterState();
	int GetCharacterHP();
	//ĳ������ ü���� �����ϴ� �Լ�
	void SetHP(int hp);
	//ü�¹ٸ� ����� �Լ�
	void MakeHpBar();
private:
	//ü��
	int m_CurHP;
	//���ݹ���
	Vec2 m_AttackRange;
	//������ ���Ҷ� ���� �Լ�
	bool IsTopOn(int m_MoveInput);
	bool IsBottomOn(int m_MoveInput);
	bool IsLeftOn(int m_MoveInput);
	bool IsRightOn(int m_MoveInput);
	bool IsErrorInput(int m_MoveInput);
	//����,�̵�,���� ���¸� ��Ÿ���� ����
	int m_State;
	int m_BeforeState;
	//�ִϸ��̼������� �ƴ����� ��Ÿ���� ����
	bool m_ActionAnimationOn;
	bool m_MoveAnimationOn;
	bool m_StopAnimationOn;
	//�Է��÷��׸� ó���ϱ� ���� ����
	int m_Input;
	int m_ActionInput;
	int m_MoveInput;
	int m_CurDirection;
	int m_BeforeDirection;
	int m_UnitVector[2];
	//�ִϸ��̼��� ������ִ� ���
	MakeAnimation *m_pMakeAnimation;

	Character();
	~Character();
};
