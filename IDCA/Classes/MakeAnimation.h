#pragma once
class MakeAnimation :public Node
{
public:
	static MakeAnimation* create(const char *fileName, const char *fileNameExtention);
	//Ŭ������ �ʱ�ȭ �Ѵ�.
	virtual bool init(const char *fileName, const char *fileNameExtention);

	//�̵� �ִϸ��̼��� ����� �����.
	Animate* AnimationMove(int direction);
	//���������� �ؽ��ĸ� �����.
	Animate* AnimationStop(int direction);
	//���� �ִϸ��̼��� �����.
	Animate* AnimationAttack(int direction);
	//���� �ִϸ��̼��� ��ȯ�Ѵ�.

	MakeAnimation() = default;
	~MakeAnimation() = default;
private:

	//����Ȯ����
	char m_FileNameExtention[10];
	//�����̸�
	char m_FrameName[100];
	//�������� �ҷ��ö� ����ϴ� ����
	char m_Buffer[256];

	Animation        *m_pAnimation;
	Animate          *m_pAnimate;
};
