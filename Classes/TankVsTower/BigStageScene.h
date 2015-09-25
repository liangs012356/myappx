#ifndef _TANKVSTOWER_BIGSTAGESCENE_H_
#define _TANKVSTOWER_BIGSTAGESCENE_H_

#include "cocos2d.h"

class BigStageScene : cocos2d::LayerColor
{
public:
	virtual bool init();

	static cocos2d::Scene* scene();

	CREATE_FUNC(BigStageScene);

private:

	void init_ui();
	void contrl_click_handler(Ref* r);
	void stage_click_handler(Ref* r);
};

#endif /*_TANKVSTOWER_BIGSTAGESCENE_H_*/