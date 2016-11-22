#pragma once
class MakeAnimation :public Node
{
public:
	static MakeAnimation* create(const char *fileName, const char *fileNameExtention);
	virtual bool init(const char *fileName, const char *fileNameExtention);

	//이동 애니메이션을 만들어 만든다.
	Animate* AnimationMove(int direction);
	//정지상태의 텍스쳐를 만든다.
	Animate* AnimationStop(int direction);
	//공격 애니메이션을 만든다.
	Animate* AnimationAttack(int direction);
	//공격 애니메이션을 반환한다.
	Animate* GetAttackAnimation(int direction);
	//이동 애니메이션을 반환한다.
	Animate* GetMoveAnimation(int direction);
	//정지 애니메이션을 반환한다.
	Animate* GetStopAnimation(int direction);
	//클래스를 초기화 한다.
	MakeAnimation() = default;
	//MakeAnimation(const char const *fileName, const char const * fileNameExtention);
	~MakeAnimation() = default;
private:

	//파일확장자
	char m_FileNameExtention[10];
	//파일이름
	char m_FrameName[100];
	//프레임을 불러올때 사용하는 버퍼
	char m_Buffer[256];
	//초기화때 만든 각각의 애니메이션을 들고 있는 포인터 변수
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
