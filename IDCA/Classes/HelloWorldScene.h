#pragma once

/*
	HelloWorldScene
	작성자 : 이근원
	Title에 해당하는 씬.
	배경화면, 배경음악, 타이틀과 라벨로 이루어져 있다.
	InputLayer를 이용하여 조이스틱 / 키보드 입력을 모두 받을 수 있다.
	StageOne으로 이동 / 프로그램 종료를 담당.
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

