#pragma once
class MakeAnimation :public Node
{
public:
	static MakeAnimation* create(const char *fileName, const char *fileNameExtention);
	virtual bool init(const char *fileName, const char *fileNameExtention);

	//�̵� �ִϸ��̼��� ����� �����.
	Animate* AnimationMove(int direction);
	//���������� �ؽ��ĸ� �����.
	Animate* AnimationStop(int direction);
	//���� �ִϸ��̼��� �����.
	Animate* AnimationAttack(int direction);
	//���� �ִϸ��̼��� ��ȯ�Ѵ�.
	Animate* GetAttackAnimation(int direction);
	//�̵� �ִϸ��̼��� ��ȯ�Ѵ�.
	Animate* GetMoveAnimation(int direction);
	//���� �ִϸ��̼��� ��ȯ�Ѵ�.
	Animate* GetStopAnimation(int direction);
	//Ŭ������ �ʱ�ȭ �Ѵ�.
	MakeAnimation() = default;
	//MakeAnimation(const char const *fileName, const char const * fileNameExtention);
	~MakeAnimation() = default;
private:

	//����Ȯ����
	char m_FileNameExtention[10];
	//�����̸�
	char m_FrameName[100];
	//�������� �ҷ��ö� ����ϴ� ����
	char m_Buffer[256];
	//�ʱ�ȭ�� ���� ������ �ִϸ��̼��� ��� �ִ� ������ ����
	Animate *m_pMoveUp;
	Animate *m_pMoveDown;
	Animate *m_pMoveRight;
	Animate *m_pMoveLeft;
	Animate *m_pMoveUpLeft;
	Animate *m_pMoveUpRight;
	Animate *m_pMoveDownRight;
	Animate *m_pMoveDownLeft;
	Animate *m_pAttackUpUpLeft;
	Animate *m_pAttackLeftDownLeft;
	Animate *m_pAttackDownDownRight;
	Animate *m_pAttackRightUpRight;
	Animate *m_pStopUp;
	Animate *m_pStopDown;
	Animate *m_pStopRight;
	Animate *m_pStopLeft;
	Animate *m_pStopUpLeft;
	Animate *m_pStopUpRight;
	Animate *m_pStopDownRight;
	Animate *m_pStopDownLeft;

	enum AnimateType
	{
		MoveUp, MoveDown, MoveRight,
		MoveLeft, MoveUpLeft, MoveUpRight,
		MoveDownRight, MoveDownLeft, AttackUpUpLeft,
		AttackLeftDownLeft, AttackDownDownRight, AttackRightUpRight,
		StopUp, StopDown, StopRight, StopLeft, StopUpLeft, StopUpRight,
		StopDownRight, StopDownLeft, AnimateNum
	};
	Animate *m_pAnimateArr[AnimateNum];

	Animation        *m_pAnimation;
	Animate          *m_pAnimate;
};
