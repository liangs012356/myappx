#include "Tower.h"

USING_NS_CC;

/* 
	TowerInfo 
*/
TowerInfo::TowerInfo()
	:m_attackRange(0)
	,m_damageValue(0)
	,m_attackDuration(0)
{
}
TowerInfo::TowerInfo(const TowerInfo& info)
{
	this->setAttackRange(info.getAttackRange());
	this->setAttackDuration(info.getAttackDuration());
	this->setDamageValue(info.getDamageValue());
}
TowerInfo::TowerInfo(const int attackRange, const int damageValue, const float attackDuration)
	:m_attackRange(attackRange)
	, m_damageValue(damageValue)
	, m_attackDuration(attackDuration)
{
}
TowerInfo::~TowerInfo()
{
	setAttackRange(0);
	setDamageValue(0);
	setAttackDuration(0);
}
const int TowerInfo::getAttackRange()const
{ 
	return m_attackRange; 
}
const int TowerInfo::getDamageValue()const
{
	return m_damageValue;
}
const float TowerInfo::getAttackDuration()const
{
	return m_attackDuration;
}
void TowerInfo::setAttackRange(const int range)
{
	m_attackRange = range;
}
void TowerInfo::setDamageValue(const int val)
{
	m_attackRange = val;
}
void TowerInfo::setAttackDuration(const float duration)
{ 
	m_attackDuration = duration; 
}
TowerInfo& TowerInfo::operator=(const TowerInfo& towerinfo)
{
	setAttackRange(towerinfo.getAttackRange());
	setAttackDuration(towerinfo.getAttackDuration());
	setDamageValue(towerinfo.getDamageValue());

	return (*this);
}


/* 
	Tower
*/

bool Tower::initWithInfo(std::string& filePath, TowerInfo& towerinfo, cocos2d::Point& point)
{
	if (!Sprite::initWithFile(filePath))
	{
		return false;
	}

	m_towerInfo = towerinfo;

	m_Normalied = point;

	return true;
}

Tower* Tower::createWithInfo(std::string& path, TowerInfo& info, cocos2d::Point& point)
{
	Tower* pRet = new(std::nothrow) Tower();
	if (pRet && pRet->initWithInfo(path, info, point))
		{ 
			pRet->autorelease();
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
}