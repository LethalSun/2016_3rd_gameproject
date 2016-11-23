#pragma once
class MakeAnimation :public Node
{
public:
	static MakeAnimation* create(const char *fileName, const char *fileNameExtention);
	//클래스를 초기화 한다.
	virtual bool init(const char *fileName, const char *fileNameExtention);

	//이동 애니메이션을 만들어 만든다.
	Animate* AnimationMove(int direction);
	//정지상태의 텍스쳐를 만든다.
	Animate* AnimationStop(int direction);
	//공격 애니메이션을 만든다.
	Animate* AnimationAttack(int direction);
	//공격 애니메이션을 반환한다.

	MakeAnimation() = default;
	~MakeAnimation() = default;
private:

	//파일확장자
	char m_FileNameExtention[10];
	//파일이름
	char m_FrameName[100];
	//프레임을 불러올때 사용하는 버퍼
	char m_Buffer[256];

	Animation        *m_pAnimation;
	Animate          *m_pAnimate;
};
