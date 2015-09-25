#include "LabelTest.h"

USING_NS_CC;

Scene * LabelTest::createScene()
{
	auto scene = Scene::create();

	auto layer = LabelTest::create();

	scene->addChild(layer);

	return scene;
}

bool LabelTest::init()
{
	if (!Layer::init())
		return false;

	auto visiable = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto string = StringUtils::format("time to play");


	auto label_sys = Label::createWithSystemFont(string, "arial", 23);
	label_sys->setPosition(origin.x + visiable.width / 2, origin.y + visiable.height - label_sys->getContentSize().height);
		
	auto label_ttf = Label::createWithTTF(
		TTFConfig("fonts/Marker Felt.ttf", 23, GlyphCollection::CUSTOM, "UTF-8", false, 1),
		string,
		TextHAlignment::LEFT,
		Director::getInstance()->getWinSize().width
		);
	label_ttf->setPosition(origin.x + visiable.width / 2, origin.y + visiable.height / 2);

	//auto label_fnt = Label::createWithTexture()



	addChild(label_sys, 1);
	addChild(label_ttf, 1);
	

	return true;
}