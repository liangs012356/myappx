#ifndef _TANKVSTOWER_MYAPPMACROS_H_
#define _TANKVSTOWER_MYAPPMACROS_H_

/*
	全局导演类宏定义
*/
#define gDirector cocos2d::Director::getInstance()
/*
	全局事件分发器
*/
#define gEventDispacther cocos2d::Director::getInstance()->getEventDispacther()
/*
	全局屏幕大小类
*/
#define gWinSize gDirector->getWinSize()
/*
	设置坐标点
*/
#define g_setPosition(_node_,_point_) _node->setPosition(_point_)
/*
设置本地精灵
*/
#define create_local_sprite(_name_) cocos2d::Sprite::create(_name_)
/*
	用arialnui.ttf创建中文字体
*/
#define menu_item_label_crete(_name_,_size_,callback1_) cocos2d::MenuItemLabel::create(\
	cocos2d::Label::createWithSystemFont(MyMathUtils::WStrToUTF8(_name_), "fonts/arialuni.ttf", _size_), \
	 CC_CALLBACK_1(callback1_ , this))


#endif /*_TANKVSTOWER_MYAPPMACROS_H_*/
