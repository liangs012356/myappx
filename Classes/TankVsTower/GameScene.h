#ifndef _TANKVSTOWER_GAMESCENE_H_
#define _TANKVSTOWER_GAMESCENE_H_

#include "cocos2d.h"
#include <vector>

class Tank;
class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* scene();
	/*
		初始化:  1.用户界面UI :init();
				2.初始化地图路径点 :initRoadPoint();
	*/
	virtual bool init()override;

	CREATE_FUNC(GameScene);
	virtual void onEnter() override;
	virtual void onExit() override;

private:
	/*
		设置UI
	*/
	void initUI();
	/*
		初始化地图以及路径点
	*/
	void initMapAndRoadPoint();
	/*
		暂停按钮回调
	*/
	void pause_bottom_handler(cocos2d::Ref* target);
	/*
		触摸时间:测试防御塔加入功能
	*/
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedevent);
	/*
		加入防御塔到地图指定位置
	*/
	void addTowerToMap(cocos2d::Point& positionInMap);
	/*
		生成敌军坦克群
	*/
	void generateNextTankWave();

private:
	std::vector<cocos2d::Vec2>m_road_point;
	std::vector<Tank*>m_tank_wave;
};



#endif /*_TANKVSTOWER_GAMESCENE_H_*/