#ifndef _ENTRSCENE_H_
#define _ENTRSCENE_H_


#include "cocos2d.h"


class EntryScene : public cocos2d::LayerColor
{
public:
	virtual bool init();

	static cocos2d::Scene* scene();

	CREATE_FUNC(EntryScene);

private:
	void init_ui();

	void click_event_handler(Ref* ref);
};

#endif /*_ENTRSCENE_H_*/