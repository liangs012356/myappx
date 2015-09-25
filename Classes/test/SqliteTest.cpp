#include "SqliteTest.h"
#include "sqlite3.h"
USING_NS_CC;

Scene * SqliteTest::createScene()
{
	auto scene = Scene::create();

	auto layer = SqliteTest::create();
	
	scene->addChild(layer);

	return scene;

}

bool SqliteTest::init()
{
	if ( !Layer::init() )
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...
	m_database = nullptr;
	
	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF(StringUtils::format("HelloWorld"), "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1, "sqliteopenstats");
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);



	return true;
}

bool SqliteTest::onTouchBegan(Touch *toch, Event * event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto blocksize = Size(visibleSize.width / 2, visibleSize.height * 5);

	auto label = static_cast<Label*>(getChildByName("sqliteopenstats"));

	m_data_path = FileUtils::getInstance()->getWritablePath() + "mydb.db";

	if (!sqlite3_open(m_data_path.c_str(), &m_database))
		label->setString("open failed");
	
	label->setString("open seccuse");

	auto label2 = Label::createWithSystemFont(m_data_path, "fonts/Marker Felt.ttf", 22,
											  Size(blocksize.width/2,blocksize.height/2), TextHAlignment::LEFT, TextVAlignment::TOP);
	label2->setMaxLineWidth(0);
	label2->setLineBreakWithoutSpace(blocksize.width);
	label2->setAnchorPoint(Vec2(0, 1));
	label2->setPosition(0, origin.y + visibleSize.height / 1.2);

	this->addChild(label2, 1, "data_path");
	return true;
}

void SqliteTest::onTouchEnded(Touch *toch, Event * event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto label = static_cast<Label*>(getChildByName("sqliteopenstats"));
	label->setString("open seccuse");

	m_data_path = FileUtils::getInstance()->getWritablePath() + "mydb.db";

	if (!sqlite3_close(m_database))
		label->setString("close failed");

	label->setString("close seccuse");

	this->removeChildByName("data_path");
	m_database = nullptr;
}