#include "MyAppMacros.h"
#include "MyMathUtils.h"

#include "LoginScene.h"



USING_NS_CC;

enum LocalTag
{
	QQ,
	SINA,
	SOUHU,
	MY
};
Scene* LoginScene::scene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);

	return scene;
}
bool LoginScene::init()
{
	if (!Layer::init())
	{
		CCASSERT(false, "Login::Layer::init() Failed");
		return false;
	}

	auto qq_weibo_login_item = menu_item_label_crete(L"ÌÚÑ¶Î¢²©", 15, LoginScene::click_weibo_menu);
	qq_weibo_login_item->setTag(QQ);
	auto sina_weibo_login_item = menu_item_label_crete(L"ÌÚÑ¶Î¢²©", 15, LoginScene::click_weibo_menu);
	sina_weibo_login_item->setTag(SINA);
	auto souhu_weibo_login_item = menu_item_label_crete(L"ÌÚÑ¶Î¢²©", 15, LoginScene::click_weibo_menu);
	souhu_weibo_login_item->setTag(SOUHU);
	auto my_weibo_login_item = menu_item_label_crete(L"ÌÚÑ¶Î¢²©", 15, LoginScene::click_weibo_menu);
	my_weibo_login_item->setTag(MY);

	auto login_menu = Menu::create(qq_weibo_login_item, sina_weibo_login_item, souhu_weibo_login_item, my_weibo_login_item, nullptr);
	login_menu->alignItemsVerticallyWithPadding(15);
	login_menu->setPosition(gWinSize / 2);
	addChild(login_menu);



	return true;
}

void LoginScene::click_weibo_menu(Ref* r)
{
	auto tag = static_cast<Node*>(r)->getTag();

	switch (tag)
	{
		case QQ:
			MessageBox("world", "hello");
			break;
		case SINA:

			break;
		case SOUHU:

			break;
		case MY:

			break;
		default:

			break;
	}


	return;
}
