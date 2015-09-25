#ifndef _TANKVSTOWER_PAUSELAYER_H_
#define _TANKVSTOWER_PAUSELAYER_H_

#include "cocos2d.h"


class PauseLayer : public cocos2d::LayerColor
{
public:

	bool init();

	CREATE_FUNC(PauseLayer);

	void onExit() override;

public:
	void resume_bottom_handler(Ref* ta);

	void exit_bottom_handler(Ref* ta);
};



#endif /* _TANKVSTOWER_PAUSELAYER_H_*/