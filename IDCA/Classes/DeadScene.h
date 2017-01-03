#pragma once

class InputLayer;

class DeadScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(DeadScene);
	static Scene* createScene();

	virtual bool init() override;
	virtual void update(float) override;

	void ChangeToHelloWorldScene();
	void TextTwinkle();

	float m_AcculmulateTime = 0.f;
	CC_SYNTHESIZE(bool, m_IsCharacterAppeared, IsCharacterAppeared);

	InputLayer* m_pInputLayer;
};

