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
	auto winsize = Director::getInstance()->getWinSize();
	auto map = TMXTiledMap::create("tankvstower.tmx");
	map->setName("map");

	addChild(map, -1, kTagMap);


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::touchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map);
	
	TMXLayer* road = map->getLayer("road");

	
	auto mapsize = map->getContentSize();
	auto mapsize2 = map->getMapSize();
	auto size = road->getLayerSize();
	auto layersize = road->getContentSize();
	auto tilesize = road->getMapTileSize();
	auto tilesize2 = map->getTileSize();

	map->setScale(winsize.width / mapsize.width, winsize.height / mapsize.height);
	map->setContentSize(winsize);

	log("win: %f, %f", winsize.width, winsize.height);
	log("map: %f, %f", mapsize.width, mapsize.height);
	log("map2: %f, %f", mapsize2.width, mapsize2.height);

	log("layer: %f, %f", layersize.width, layersize.height);
	log("layer2: %f, %f", size.width, size.height);
	log("tilesize: %f, %f", tilesize.width, tilesize.height);
	log("tilesize2: %f, %f", tilesize2.width, tilesize2.height);



	auto begin = road->getTileAt(Vec2(0, 2));
	auto second = road->getTileAt(Vec2(6, 2));
	auto third = road->getTileAt(Vec2(6, 4));
	auto fivth = road->getTileAt(Vec2(1, 4));
	auto sixth = road->getTileAt(Vec2(1, 6));
	auto seventh = road->getTileAt(Vec2(6, 6));
	auto end = road->getTileAt(Vec2(6, 7));
	
	
	
	// 地图锚点(0,0),新加入精灵(锚点(0.5,0.5)都要加入偏差值
	auto diff = Vec2(tilesize.width / 2, tilesize.height);

	m_road_point.push_back(begin->getPosition() + diff);
	m_road_point.push_back(second->getPosition() + diff);
	m_road_point.push_back(third->getPosition() + diff);
	m_road_point.push_back(fivth->getPosition() + diff);
	m_road_point.push_back(sixth->getPosition() + diff);
	m_road_point.push_back(seventh->getPosition() + diff);
	m_road_point.push_back(end->getPosition() + diff);
	log("p1: x: %f, y : %f", begin->getPosition().x, begin->getPosition().y);
	log("p2: x: %f, y: %f", second->getPosition().x, second->getPosition().y);
	log("p3: x: %f, y: %f", third->getPosition().x, third->getPosition().y);
	log("p4: x: %f, y: %f", fivth->getPosition().x, fivth->getPosition().y);
	log("p5: x: %f, y: %f", sixth->getPosition().x, sixth->getPosition().y);
	log("p6: x: %f, y: %f", seventh->getPosition().x, seventh->getPosition().y);
	log("p7: x: %f, y: %f", end->getPosition().x, end->getPosition().y);

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

void GameScene::generateNextTankWave()
{
	float speed = 1.0f;
	for (int i = 0; i < 10; ++i)
	{
		auto tank = Sprite::create("tank.png");
		/*tank->setAnchorPoint(Vec2(0, 0));*/
		getChildByName("map")->addChild(tank);
		tank->setTag(i);
		tank->setPosition(m_road_point[0]);
		auto wait = DelayTime::create(3.0*i);
		auto m1 = MoveTo::create(speed * 6.0f, m_road_point[1]);
		auto m2 = MoveTo::create(speed * 2.0f, m_road_point[2]);
		auto m3 = MoveTo::create(speed * 5.0f, m_road_point[3]);
		auto m4 = MoveTo::create(speed * 2.0f, m_road_point[4]);
		auto m5 = MoveTo::create(speed * 5.0f, m_road_point[5]);
		auto m6 = MoveTo::create(speed * 1.0f, m_road_point[6]);
		auto end = CallFuncN::create([](Ref* r){
			static_cast<Sprite*>(r)->removeFromParentAndCleanup(true);
		});
		auto seq = Sequence::create(wait,m1, m2, m3, m4, m5, m6, end, nullptr);
		tank->runAction(seq);
	}
}

