#include "BigStageScene.h"
#include "MyAppMacros.h"
#include "MyMathUtils.h"

#include "EntryScene.h"

USING_NS_CC;

enum
{
	kTagStartMenuItem = 500,
	kTagSettingMenuItem,

};

bool EntryScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tankvstower.plist");

	init_ui();
	return true;
}

Scene* EntryScene::scene()
{
	auto scene = Scene::create();

	auto layer = EntryScene::create();

	scene->addChild(layer, 0, "entryscene");

	return scene;
}

void EntryScene::init_ui()
{
	auto winsize = gWinSize;
	auto logoSprite = Sprite::createWithSpriteFrameName("HelloWorld.png");
	addChild(logoSprite);
	logoSprite->setPosition(Point(winsize) / 2);
	
	auto startLabel = Label::createWithSystemFont(MyMathUtils::WStrToUTF8(L"开始游戏"), "fonts/arialuni.ttf", 40.0f);
	startLabel->setColor(Color3B::BLACK);
	
	auto start_game_item = MenuItemLabel::create(startLabel, CC_CALLBACK_1(EntryScene::click_event_handler, this));
	start_game_item->setPosition(Point(winsize.width / 2, winsize.height / 5));
	start_game_item->setTag(kTagStartMenuItem);

	auto setting_Menu_item = MenuItemLabel::create(Sprite::createWithSpriteFrameName("setting.png"), CC_CALLBACK_1(EntryScene::click_event_handler, this));
	setting_Menu_item->setPosition(Point(setting_Menu_item->getContentSize().width / 2, 
		winsize.height - setting_Menu_item->getContentSize().height / 2));
	setting_Menu_item->setTag(kTagSettingMenuItem);

	auto menu = Menu::create(start_game_item, setting_Menu_item, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);
}

void EntryScene::click_event_handler(Ref* ref)
{
	auto target = static_cast<MenuItemLabel*>(ref);
	auto tag = target->getTag();
	switch (tag)
	{
		case kTagStartMenuItem:
			gDirector->replaceScene(TransitionFade::create(0.1f,BigStageScene::scene()) );
			break;
		case kTagSettingMenuItem:
			cocos2d::MessageBox("settging", "setingMenu");
			break;
		default:
			break;
	}

}