/************************************************************************/
/*
CLASS		: AnimationMaker
Author		: ������
����			: ������ ĳ����, ���ʹ̰� �� Ŭ������ �ν��Ͻ��� ���� �ְ� �ִϸ��̼��� �ڽſ���
			  �ֵ��ؼ� �ִϸ��̼��� �����. �׸��� �ִϸ��̼��� ������ Ȯ���ϴ� �Լ��� �����ְ� �� �Լ��� �ִϸ��̼���
			  ������ 0, �����̸� 1, �̵��̸� 2, ��ų�̸� 3�� ��ȯ�Ѵ�.
*/
/************************************************************************/
#pragma once
class AnimationMaker :public Node
{
public:
	static AnimationMaker* create(const char *fileName, const char *fileExtention);

	virtual bool init(const char *fileName, const char *fileExtention);

	//� �ִϸ��̼����� ����
	void SetAnimationAttack();
	void SetAnimationMove();
	void SetAnimationStop();
	void SetAnimationSkill();

	//�ִϸ��̼��� ���Ѵ�.
	Sprite* AddAnimation(int directionNum);

	//�ִϸ��̼� ������ Ȯ���Ѵ�.
	int whichAnimationContinued();

	Sprite* GetSprite();

	AnimationMaker() = default;
	~AnimationMaker() = default;

private:
	//�ִϸ��̼��� �����ϰ� ������ ȣ��Ǵ� �Լ�.
	void AnimationOn();
	void AnimationOff();

	//������ �̸��� ����� �Լ�
	void MakeAnimationFrameName(int fileNumber);

	//�±׸� �̿��� ���ϵ带 ����� �Լ�
	//void RemoveChileByTag();

	//�ִϸ޼������� �����ִ� ����
	bool m_IsAnimationOn;

	//���� Ȯ����
	char m_FileNameExtention[10];

	//���� �̸�
	char m_FileName[100];

	//���¸� �����ϰ� �ִ� ����
	int m_State;

	//�������� �ҷ��� �� ����ϴ� ������
	char m_FrameNameBuffer[256];

	Animation *m_pAnimation;

	Animate *m_pAnimate;

	SpriteFrame * m_pFrame;

	Sprite* m_pSprite;

	float m_AnimationSpeed;

	//�ִϸ��̼��̸��� ����� �Լ�
	void MakeAnimationName(int);

	//�ִϸ��̼��� �ҷ��� �� ����ϴ� ����
	char m_AnimationName[256];
};
