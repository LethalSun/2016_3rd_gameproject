#pragma once


class InputLayer;

class EscMenu : public Layer
{


public:
	CREATE_FUNC(EscMenu);

	static Scene*			createScene();
	bool					init(void);
	void					update(float delta);
	void					returnToMain(cocos2d::Ref * pSender);
	void					returnToGame(cocos2d::Ref * pSender);

	InputLayer*				m_pInputLayer;


};

