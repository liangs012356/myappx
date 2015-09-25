#include "PauseLayer.h"
#include "MyMathUtils.h"
#include "EntryScene.h"

USING_NS_CC;


bool PauseLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	auto winsize = Director::getInstance()->getWinSize();

	/* ÔÝÍ£±êÇ© */
	auto pause_label = Label::createWithSystemFont(MyMathUtils::WStrToUTF8(L"ÔÝÍ£"), "fonts/arialuni.ttf", 50);
	pause_label->ignoreAnchorPointForPosition(false);
	pause_label->setAnchorPoint(Vec2(0.5f, 1.5f));
	pause_label->setNormalizedPosition(Vec2(0.5f, 1.0f));
	addChild(pause_label);

	/* ÍË³ö°´Å¥ */
	auto exit_menu_item = MenuItemLabel::create(Sprite::createWithSpriteFrameName("exit.png"),
												[](Ref* f){
		Director::getInstance()->replaceScene(TransitionFade::create(0.2f, EntryScene::scene()));
	});

	exit_menu_item->ignoreAnchorPointForPosition(false);
	exit_menu_item->setAnchorPoint(Vec2(0.5f, -0.5f));
	exit_menu_item->setNormalizedPosition(Vec2(0.5f, 0.0f));
	exit_menu_item->setScale(1.1f);
	/*  ¼ÌÐø°´Å¥ */
	auto resume_menu_item = MenuItemLabel::create(Sprite::createWithSpriteFrameName("resume.png"),
												  [this](Ref* f){
		this->removeFromParentAndCleanup(true);
	});

	resume_menu_item->ignoreAnchorPointForPosition(false);
	resume_menu_item->setAnchorPoint(Vec2(0.5f, 0.5f));
	resume_menu_item->setNormalizedPosition(Vec2(0.5f, 0.5f));
	resume_menu_item->setScale(1.1f);

	auto game_menu = Menu::create(exit_menu_item, resume_menu_item, nullptr);
	game_menu->ignoreAnchorPointForPosition(false);
	game_menu->setAnchorPoint(Vec2(0.5f, 0.5f));
	game_menu->setContentSize(winsize);
	game_menu->setNormalizedPosition(Vec2(0.5f, 0.5f));
	addChild(game_menu);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e)->bool{
		return true;
	};



	return true;
}

void PauseLayer::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	LayerColor::onExit();

}

