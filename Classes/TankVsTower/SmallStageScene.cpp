#include "BigStageScene.h"
#include "EntryScene.h"
#include "GameDirector.h"
#include "GameScene.h"
#include "LocalVariables.h"
#include "MyMathUtils.h"

#include "SmallStageScene.h"


USING_NS_CC;

enum
{
	kTagBackBottom,
	kTagStoreBottom,
};

Scene* SmallStageScene::scene()
{
	auto scene = Scene::create();
	auto layer = SmallStageScene::create();
	scene->addChild(layer);

	return scene;
}

bool SmallStageScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}


	init_ui();

	return true;
}
/*
	初始化小关选择界面
*/
void SmallStageScene::init_ui()
{
	auto winsize = Director::getInstance()->getWinSize();

	/* 关卡选择 */
	auto stage = Label::createWithSystemFont(MyMathUtils::WStrToUTF8(L"????"), "fonts/arialuni.ttf", 40.0f);
	addChild(stage);
	stage->setColor(Color3B::BLACK);
	stage->setAnchorPoint(Vec2(0.5f, 1.0f));
	stage->setNormalizedPosition(Vec2(0.5f, 1.0f));
	/* 后退按钮 */
	auto back_bottom = MenuItemLabel::create(Sprite::createWithSpriteFrameName("backf.png"), CC_CALLBACK_1(SmallStageScene::contrl_click_handler, this));
	back_bottom->setTag(kTagBackBottom);
	back_bottom->setAnchorPoint(Vec2(-0.1f, 1.1f));
	back_bottom->setNormalizedPosition(Vec2(0.0f, 1.0f));
	/* 商城 */
	auto stroe_bottom = MenuItemLabel::create(Sprite::createWithSpriteFrameName("store.png"), CC_CALLBACK_1(SmallStageScene::contrl_click_handler, this));
	stroe_bottom->setTag(kTagStoreBottom);
	stroe_bottom->setAnchorPoint(Vec2(1.1f, 1.1f));
	stroe_bottom->setNormalizedPosition(Vec2(1.0f, 1.0f));
	auto contrl_menu = Menu::create(back_bottom, stroe_bottom, nullptr);
	addChild(contrl_menu);
	contrl_menu->setPosition(Point::ZERO);
	/* 小关数字 */
	auto checkpointmenu = Menu::create();
	for (int i = 1; i <= 8; ++i)
	{
		char buf[10] = {};
		sprintf(buf, "%d.png", i);
		auto number = MenuItemLabel::create(Sprite::createWithSpriteFrameName(buf), CC_CALLBACK_1(SmallStageScene::stage_click_handler, this));
		number->setTag(i);
		number->setScale(0.6f);
		if (i<5)
		{
			number->setNormalizedPosition(Vec2(0.2*i, 0.7));
		}
		else
		{
			number->setNormalizedPosition(Vec2(0.2*(i-4), 0.3));

		}
		checkpointmenu->addChild(number);
	}
	checkpointmenu->ignoreAnchorPointForPosition(false);
	checkpointmenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	checkpointmenu->setContentSize(Size(winsize.width, winsize.height /1.5));
	checkpointmenu->setNormalizedPosition(Vec2(0.5f, 0.5f));

	addChild(checkpointmenu);

}

/* 
	返回控件回调
*/
void SmallStageScene::contrl_click_handler(Ref* r)
{
	auto bottom = static_cast<MenuItemLabel*>(r);
	auto tag = bottom->getTag();
	switch (tag)
	{
		case kTagBackBottom:
			Director::getInstance()->replaceScene(TransitionFade::create(0.1f, BigStageScene::scene()));
			break;
		case kTagStoreBottom:
			MessageBox("Not Ready", "NOTE");
			break;
		default:
			break;
	}
}

/* 
	小关图标选择回调 
*/
void SmallStageScene::stage_click_handler(Ref* r)
{
	auto bottom = static_cast<MenuItemLabel*>(r);
	auto tag = bottom->getTag();

	std::string big_stage = "current_small_stage";
	GameDirector::getInstance()->getLocalVariables()->setInt(big_stage, tag);
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, GameScene::scene()));
}