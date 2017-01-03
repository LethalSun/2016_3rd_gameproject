#pragma once

/*
	EndingScene
	작성자 : 이근원
	플레이어가 승리했을 때 진입하는 씬.
	q를 누르면 다시 타이틀 씬으로 진입한다.
*/

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

