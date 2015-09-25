#ifndef _TESTSECENE_H_
#define _TESTSECENE_H_

#include "cocos2d.h"

USING_NS_CC;

class TestScene : public Layer
{
public:
	static Scene * createScene();
	
	virtual bool init();
	virtual bool onTouchBegan(Touch *toch, Event * eevent);
	
	CREATE_FUNC(TestScene);

	void addSpriteAtPosition(Vec2 p);
};

#endif //_TESTSECENE_H_