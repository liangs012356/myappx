#include "EntryScene.h"
#include "GameDirector.h"
#include "LocalVariables.h"
#include "MyMathUtils.h"
#include "SmallStageScene.h"

#include "BigStageScene.h"

USING_NS_CC;

enum
{
	kTagBackBottom,
	kTagStoreBottom,
};
bool BigStageScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	init_ui();

	return true;
}

cocos2d::Scene* BigStageScene::scene()
{
	auto scene = Scene::create();

	auto layer = BigStageScene::create();

	scene->addChild(layer, 0, "BigStageScene");

	return scene;
}


void BigStageScene::init_ui()
{
	auto winsize = Director::getInstance()->getWinSize();

	auto stage = Label::createWithSystemFont(MyMathUtils::WStrToUTF8(L"关卡选择"), "fonts/arialuni.ttf", 40.0f);

	addChild(stage);
	stage->setColor(Color3B::BLACK);
	stage->setAnchorPoint(Vec2(0.5f, 1.0f));
	stage->setNormalizedPosition(Vec2(0.5f, 1.0f));

	auto back_bottom = MenuItemLabel::create(Sprite::createWithSpriteFrameName("backf.png"), CC_CALLBACK_1(BigStageScene::contrl_click_handler, this));
	back_bottom->setTag(kTagBackBottom);
	back_bottom->setAnchorPoint(Vec2(-0.1f, 1.1f));
	back_bottom->setNormalizedPosition(Vec2(0.0f, 1.0f));

	auto stroe_bottom = MenuItemLabel::create(Sprite::createWithSpriteFrameName("store.png"), CC_CALLBACK_1(BigStageScene::contrl_click_handler, this));
	stroe_bottom->setTag(kTagStoreBottom);
	stroe_bottom->setAnchorPoint(Vec2(1.1f, 1.1f));
	stroe_bottom->setNormalizedPosition(Vec2(1.0f, 1.0f));
	auto contrl_menu = Menu::create(back_bottom, stroe_bottom, nullptr);
	addChild(contrl_menu);
	contrl_menu->setPosition(Point::ZERO);

	auto checkpointmenu = Menu::create();
	for (int i = 1; i <= 3; ++i)
	{
		char buf[10] = {};
		sprintf(buf, "big%d.png", i);
		auto number = MenuItemLabel::create(Sprite::createWithSpriteFrameName(buf), CC_CALLBACK_1(BigStageScene::stage_click_handler,this));
		number->setTag(i);
		number->setScale(1.4f);
		number->setNormalizedPosition(Vec2(0.25*i, 0.5));
		checkpointmenu->addChild(number);
	}
	checkpointmenu->ignoreAnchorPointForPosition(false);
	checkpointmenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	checkpointmenu->setContentSize(Size(winsize.width, winsize.height / 2));
	checkpointmenu->setNormalizedPosition(Vec2(0.5f, 0.5f));

	addChild(checkpointmenu);

}

/*
	good
*/
void BigStageScene::contrl_click_handler(Ref* r)
{
	auto bottom = static_cast<MenuItemLabel*>(r);
	auto tag = bottom->getTag();
	switch (tag)
	{
		case kTagBackBottom:
			Director::getInstance()->replaceScene(TransitionFade::create(0.1f, EntryScene::scene()));
			break;
		case kTagStoreBottom:
			MessageBox("Not Ready", "NOTE");
			break;
		default:
			break;
	}
}

/*
	
*/
void BigStageScene::stage_click_handler(Ref* r)
{
	auto bottom = static_cast<MenuItemLabel*>(r);
	auto tag = bottom->getTag();

	std::string big_stage = "current_big_stage";
	GameDirector::getInstance()->getLocalVariables()->setInt(big_stage, tag);

	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SmallStageScene::scene()));

}