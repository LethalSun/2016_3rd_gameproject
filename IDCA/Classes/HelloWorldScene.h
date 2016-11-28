#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

class Player;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	Player *player;
	void menuNextCallback(cocos2d::Ref* pSender);
	void menuStage1(cocos2d::Ref * pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
