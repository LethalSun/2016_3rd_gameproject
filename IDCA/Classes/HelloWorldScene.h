#pragma once

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

