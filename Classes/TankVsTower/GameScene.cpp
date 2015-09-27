#include "MyAppMacros.h"
#include "PauseLayer.h"
#include "Tower.h"
#include "Tank.h"
#include "GameScene.h"

USING_NS_CC;

enum{
	kTagMap = 1,
	kTagLayer,
};

Scene* GameScene::scene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		CCASSERT(false, "GameScene : LayerColor::initwithcolor() Faild!");
		return false;
	}

	this->setName("layer");

	initUI();
	initMapAndRoadPoint();



	return true;
}
void GameScene::onEnter()
{
	Layer::onEnter();

	generateNextTankWave();

}
void GameScene::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Layer::onExit();
}

void GameScene::initUI()
{
	auto winsize = Director::getInstance()->getWinSize();

	auto pause_bottom = MenuItemLabel::create(Sprite::createWithSpriteFrameName("pause.png"),
											  CC_CALLBACK_1(GameScene::pause_bottom_handler, this));

	pause_bottom->ignoreAnchorPointForPosition(false);
	pause_bottom->setAnchorPoint(Vec2(-0.2f, 1.2f));
	pause_bottom->setNormalizedPosition(Vec2(0.0f, 1.0f));
	pause_bottom->setScale(1.3f);

	auto game_menu = Menu::create(pause_bottom, nullptr);
	game_menu->ignoreAnchorPointForPosition(false);
	game_menu->setAnchorPoint(Vec2(0.5f, 0.5f));
	game_menu->setContentSize(winsize);
	game_menu->setNormalizedPosition(Vec2(0.5f, 0.5f));

	addChild(game_menu);

	
}
void GameScene::initMapAndRoadPoint()
{

}

bool GameScene::touchBegan(cocos2d::Touch* touch, cocos2d::Event* e)
{
	auto target = e->getCurrentTarget();
	log("target:%s", target->getName().c_str());

	auto position = touch->getLocation();
	log("position in gl: %f, %f", position.x, position.y);

	auto p = target->convertToNodeSpace(touch->getLocation());
	log("position in map: %f, %f", p.x, p.y);

	addTowerToMap(p);
	return true;
}
void GameScene::pause_bottom_handler(Ref* tar)
{
	auto pauselayer = PauseLayer::create();

	auto runingscene = Director::getInstance()->getRunningScene();

	runingscene->addChild(pauselayer);
}
void GameScene::addTowerToMap(Point& postionInMap)
{
	auto map = getChildByName("map");

	TowerInfo towerinfo(100, 50, 0.3f);

	auto tower = Tower::createWithInfo(std::string("tower.png"), towerinfo, Point(1.0f, 0.0f));

	tower->setPosition(postionInMap);

	map->addChild(tower);

	return;
}


