#ifndef _TANKVSTOWER_SMALLSTAGESCENE_H_
#define _TANKVSTOWER_SMALLSTAGESCENE_H_


#include "cocos2d.h"

class SmallStageScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* scene();
	
	bool init();

	CREATE_FUNC(SmallStageScene);

public:
	void init_ui();
	void contrl_click_handler(Ref* r);
	void stage_click_handler(Ref* r);
};


#endif	/*_TANKVSTOWER_SMALLSTAGESCENE_H_*/