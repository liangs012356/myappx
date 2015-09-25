#ifndef _LABELTEST_H_
#define _LABELTEST_H_

#include "cocos2d.h"


class LabelTest : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();

	virtual bool init();



	CREATE_FUNC(LabelTest);

};

#endif