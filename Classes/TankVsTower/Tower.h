/*
	Tower.h: include the 
	time:	2015-9-11
	auther:	liangs012356
	main:	define of Tower in the game of tankvstower,

*/


#ifndef _TANKVSTOWER_TOWER_H_
#define _TANKVSTOWER_TOWER_H_

#include "cocos2d.h"


class TowerInfo
{
public:
	TowerInfo();
	TowerInfo(const TowerInfo& info);
	TowerInfo(const int attackRange, const int damageValue, const float attackDuration);
	virtual ~TowerInfo();

	TowerInfo& operator=(const TowerInfo& towerinfo);
protected:
	const int getAttackRange()const;
	const int getDamageValue()const;
	const float getAttackDuration()const;
	inline void setAttackRange(const int range);
	inline void setDamageValue(const int val);
	inline void setAttackDuration(const float duration);
private:
	int m_attackRange;
	int m_damageValue;
	float m_attackDuration;
};

class Tower : public cocos2d::Sprite
{
public:
	virtual bool initWithInfo(std::string& filePath, TowerInfo& towerinfo, cocos2d::Point& point);

	static Tower* createWithInfo(std::string& filePath,TowerInfo& towerinfo, cocos2d::Point& point);
		
private:
	TowerInfo m_towerInfo;
	cocos2d::Point m_Normalied;
};





#endif /* define(_TANKVSTOWER_TOWER_H_) */