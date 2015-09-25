#include "testScene.h"

Scene *TestScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	auto layer = TestScene::create();
	
	scene->addChild(layer);

	return scene;
}
bool TestScene::init()
{
	if (!Layer::init()) 
	{
		return false;
	}

	auto vsize = Director::getInstance()->getVisibleSize();

	auto worldBody = PhysicsBody::createEdgeBox(vsize,PHYSICSBODY_MATERIAL_DEFAULT,3.0f);
	auto node = Node::create();
	node->setPosition(Vec2(vsize.width, vsize.height)/2);
	node->setPhysicsBody(worldBody);

	addChild(node);

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

bool TestScene::onTouchBegan(Touch *touch, Event * eevent)
{
	addSpriteAtPosition(touch->getLocation());
	return true;
}
void TestScene::addSpriteAtPosition(Vec2 p)
{
	auto sprite = Sprite::create("CloseNormal.png");
	
	auto body = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(10.0f,0.1f,0.1f));
	body->setDynamic(true);
	
	sprite->setPhysicsBody(body);
	
	sprite->setPosition(p);
	
	addChild(sprite);
}