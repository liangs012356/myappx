#include "TetrisScene.h"

USING_NS_CC;
static cocos2d::Size customResolutionSize = cocos2d::Size(800, 500);

enum
{
	kTagLayerTetrisMap = 1000,
	kTagLayerTetrisDown,
	kTagSpriteBatchNode,
	kTagLayerTetrisContrl,
	kTagContrlup,
	kTagContrldown,
	kTagContrlleft,
	kTagContrlright
};
Scene* TetrisScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TetrisScene::create();	//地图层
	scene->addChild(layer,0, kTagLayerTetrisMap);

	auto livetetris = Layer::create();	//下落方块层
	scene->addChild(livetetris, 0, kTagLayerTetrisDown);
	auto layerui = Layer::create();	// 控制层
	scene->addChild(layerui, 1, kTagLayerTetrisContrl);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TetrisScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->setContentScaleFactor(1);
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(customResolutionSize.width, customResolutionSize.height, ResolutionPolicy::SHOW_ALL);

	// 地图初始化
	auto MapTetirsIsReady = MapTetris::GetInstance()->init();

	// 方块初始化
	for (int i = 0; i < 7; ++i)
	{
		tetriss[i].init(static_cast<Tetris::TYPES>(i));
	}
	// 设定初始方块
	resetTetris();

	// 开启键盘
	if (!isKeyboardEnabled())
	{
		setKeyboardEnabled(true);
	}
	/* 加载纹理 */
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("all.plist");
	SpriteBatchNode* batchnode = SpriteBatchNode::create("all.png", 20L);
	addChild(batchnode, 0, kTagSpriteBatchNode);

	/* 背景图片 */
	auto back = Sprite::create("back.jpg");
	back->setContentSize(Director::getInstance()->getWinSize());
	addChild(back, -1);

	m_freams_press = 0;		//帧计数初始化
	
	schedule(schedule_selector(TetrisScene::autodown), 0.5f, kRepeatForever, 0);	// 自动下落计划
	scheduleUpdate();	// 激活update()计划,每帧绘制前都会执行完update();
	
	return true;
}

void TetrisScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

/*update根据nowKeyCode做出不同反应*/
void TetrisScene::update(float delta)
{
	bool map_need_update = false;

	switch (nowKeyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (m_freams_press == 0 && (*tetris).isUpOK())
			(*tetris).up();
		updateFreamCount(0);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (m_freams_press == 0)
		{
			if ((*tetris).isDownOK())
			{
				(*tetris).down();
			}
			else
			{
				(*tetris).give();
				(*tetris).removeFullLine();
				resetTetris();
				map_need_update = true;
			}
		}
		updateFreamCount(5);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (m_freams_press == 0 && (*tetris).isLeftOK())
			(*tetris).left();
		updateFreamCount(2);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (m_freams_press == 0 && (*tetris).isRightOK())
			(*tetris).right();
		updateFreamCount(2);
		break;
	default:
		return;
		break;
	} // switch(nowkeycode)

	show(map_need_update);
}

void TetrisScene::addchildat(int id, int pos_x, int pos_y, int tag, Layer *who)
{
	auto winSize = Director::getInstance()->getWinSize();

	char buf[20];
	for (int i = 0; i < 20; ++i)
	{
		buf[i] = '\0';
	}
	sprintf(buf, "tetris_%d.png", id);

	auto sp = Sprite::createWithSpriteFrameName(buf);

	int x = pos_x * 16 + 16;
	int y = (MapTetris::GetInstance()->height()- pos_y) * 16;
	sp->setPosition(x, y);

	Node* spritebatchnode = nullptr;
	spritebatchnode = who->getChildByTag(kTagSpriteBatchNode);
	if (spritebatchnode != nullptr)
	{
		static_cast<SpriteBatchNode*>(spritebatchnode)->addChild(sp, 0, tag);
		return;
	}
	who->addChild(sp, 0, tag);
	return;
}

/*
	绘制地图层和下落方块层 由update函数调用
*/
void TetrisScene::show(bool map_need_update)
{
	// 绘制地图层
	if (map_need_update)
	{
		static_cast<SpriteBatchNode*>(getChildByTag(kTagSpriteBatchNode))->removeAllChildrenWithCleanup(true);
		log("map_update");
		MapTetris *map = MapTetris::GetInstance();
		for (int y = Tetris::BEGIN; y < (*map).height(); y++)
			for (int x = 0; x < (*map).width(); ++x)
			{
				int id =map->get(x, y);
				if (id){
					addchildat(id, x, y, x*y, this);
				}
			}
		map_need_update = false;
	}

	// 绘制下落方块层
	auto livetetris = getScene()->getChildByTag(kTagLayerTetrisDown);
	livetetris->removeAllChildrenWithCleanup(false);

	int points = (*tetris).points();
	for (int i = 0; i < points; ++i)
	{
		int y = (*tetris).posYInMap(i);
		if (y < Tetris::BEGIN)
			continue;
		int id = (*tetris).id();
		int x = (*tetris).posXInMap(i);
		addchildat(id, x, y, i,static_cast<Layer *>(livetetris));
	}
	// 控制层 在onEnter()里创建,不需要更新
}

/*
	自动下落实现,大部分复制update()函数里的 下降 部分 代码即可
*/
void TetrisScene::autodown(float time)
{
	bool map_need_update = false;

	if (!(nowKeyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW && m_freams_press > 30))
	{
		if ((*tetris).isDownOK())
		{
			(*tetris).down();
		}
		else
		{
			(*tetris).give();
			(*tetris).removeFullLine();
			resetTetris();
			map_need_update = true;
		}
		show(map_need_update);
	}
}

/*
	记录并更新按下一个键所经历的帧数,用于移动速度, 由update()和autodown()调用
*/
void TetrisScene::updateFreamCount(int freams_count_to_add_once)
{
	static cocos2d::EventKeyboard::KeyCode lastKeyCode;
	static int speed;
	if (nowKeyCode == lastKeyCode)
	{
		speed += freams_count_to_add_once;
		if (speed > 60)
			speed = 60;
	}
	else
	{
		speed = 1;
	}

	m_freams_press += speed;
	if (m_freams_press > 59)
		m_freams_press = 0;

	lastKeyCode = nowKeyCode;
}

/* 
	重置下落方块:类型/位置状态等 
*/
void TetrisScene::resetTetris()
{
	srand((unsigned)time(nullptr));
	tetris = (tetriss + rand() % 7);
	(*tetris).reset();
}

/* 
	创建4个按钮 上/下/左/右 和键盘按下上下左右一样的作用
*/
void TetrisScene::onEnter()
{
	Layer::onEnter();	// 先调用父系onEnter

	auto layer = getParent()->getChildByTag(kTagLayerTetrisContrl);
	
	auto up = Sprite::createWithSpriteFrameName("up.png");
	auto down = Sprite::createWithSpriteFrameName("down.png");
	auto left = Sprite::createWithSpriteFrameName("left.png");
	auto right = Sprite::createWithSpriteFrameName("right.png");
	
	up->setPosition(500.0f, 300.0f);
	down->setPosition(500.0f, 100.0f);
	left->setPosition(400.0f, 200.0f);
	right->setPosition(600.0f, 200.0f);

	layer->addChild(up, 5, kTagContrlup);
	layer->addChild(down, 5, kTagContrldown);
	layer->addChild(left, 5, kTagContrlleft);
	layer->addChild(right, 5, kTagContrlright);

	auto listener_up = EventListenerTouchOneByOne::create();
	listener_up->setSwallowTouches(true);
	listener_up->onTouchBegan = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			target->setOpacity(180);
			switch (target->getTag())
			{
				case kTagContrlup:
					nowKeyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
					break;
				case kTagContrldown:
					nowKeyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
					break;
				case kTagContrlleft:
					nowKeyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
					break;
				case kTagContrlright:
					nowKeyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
					break;
				default:
					break;
			}
			return true;
		}
		return false;
	};
	listener_up->onTouchEnded = [=](Touch* touch, Event* event){
		m_freams_press = 0;
		static_cast<Sprite*>(event->getCurrentTarget())->setOpacity(255);
		nowKeyCode = EventKeyboard::KeyCode::KEY_NONE; 
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_up, up);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_up->clone(), down);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_up->clone(), left);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_up->clone(), right);

}