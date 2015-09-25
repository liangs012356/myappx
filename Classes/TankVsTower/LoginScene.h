#ifndef _TANKVSTOWER_LOGINSCENE_H_
#define _TANKVSTOWER_LOGINSCENE_H_

#include "cocos2d.h"

class LoginScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
private:
	void click_weibo_menu(Ref* r);
};

#endif /*_TANKVSTOWER_LOGINSCENE_H_*/