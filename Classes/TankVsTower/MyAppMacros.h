#ifndef _TANKVSTOWER_MYAPPMACROS_H_
#define _TANKVSTOWER_MYAPPMACROS_H_

/*
	ȫ�ֵ�����궨��
*/
#define gDirector cocos2d::Director::getInstance()
/*
	ȫ���¼��ַ���
*/
#define gEventDispacther cocos2d::Director::getInstance()->getEventDispacther()
/*
	ȫ����Ļ��С��
*/
#define gWinSize gDirector->getWinSize()
/*
	���������
*/
#define g_setPosition(_node_,_point_) _node->setPosition(_point_)
/*
���ñ��ؾ���
*/
#define create_local_sprite(_name_) cocos2d::Sprite::create(_name_)
/*
	��arialnui.ttf������������
*/
#define menu_item_label_crete(_name_,_size_,callback1_) cocos2d::MenuItemLabel::create(\
	cocos2d::Label::createWithSystemFont(MyMathUtils::WStrToUTF8(_name_), "fonts/arialuni.ttf", _size_), \
	 CC_CALLBACK_1(callback1_ , this))


#endif /*_TANKVSTOWER_MYAPPMACROS_H_*/
