#pragma once

/*
	HelloWorldScene
	�ۼ��� : �̱ٿ�
	Title�� �ش��ϴ� ��.
	���ȭ��, �������, Ÿ��Ʋ�� �󺧷� �̷���� �ִ�.
	InputLayer�� �̿��Ͽ� ���̽�ƽ / Ű���� �Է��� ��� ���� �� �ִ�.
	StageOne���� �̵� / ���α׷� ���Ḧ ���.
*/

class InputLayer;

class HelloWorld : public cocos2d::Layer
{
public:
	CREATE_FUNC(HelloWorld);
	static cocos2d::Scene* createScene();

	virtual bool init() override;
	virtual void update(float) override;

	void ChangeToStageOne();
	void ExitGame();

	InputLayer* m_pInputLayer;
};

