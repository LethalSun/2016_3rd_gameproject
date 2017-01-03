#pragma once

class InputLayer;

class EndingScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(EndingScene);
	static Scene* createScene();

	virtual bool init() override;
	virtual void update(float) override;

	void ChangeToHelloWorldScene();
	void TextTwinkle();

	float m_AcculmulateTime = 0.f;
	CC_SYNTHESIZE(bool, m_IsVictoryAppeared, IsVictoryAppeared);

	InputLayer* m_pInputLayer;
};

