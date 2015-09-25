#include "Tank.h"

USING_NS_CC;



bool Tank::initWithInfo(std::string& filePath, TankInfo& towerinfo)
{
	if (!Sprite::initWithFile(filePath))
	{
		return false;
	}

	m_tank_info = towerinfo;

	return true;
}

Tank* Tank::createWithInfo(std::string& path, TankInfo& info)
{
	Tank* pRet = new(std::nothrow) Tank();
	if (pRet && pRet->initWithInfo(path, info))
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

void Tank::startWait()
{
	this->scheduleOnce(schedule_selector(Tank::waitSchedule), m_tank_info.getDuration());
}
void Tank::waitSchedule(float dt)
{
	schedule(schedule_selector(Tank::moveSchedule),0.05f);
}

void Tank::moveSchedule(float dt)
{
	setPosition(getPositionX() + m_tank_info.getSpeedX(), getPositionY() + m_tank_info.getSpeedY());
}




/* class TankInfo */
TankInfo::TankInfo()
	:m_waitDuration(0.0f)
	, m_speed_x(0.0f)
	, m_speed_y(0.0f)
{
}
TankInfo::TankInfo(const TankInfo& info)
{
	setDuration(info.getDuration());
	setSpeedX(info.getSpeedX());
	setSpeedy(info.getSpeedY());
}
TankInfo::TankInfo(const float duration, const float speedx, const float speedy)
	:m_waitDuration(duration), m_speed_x(speedx), m_speed_y(speedy)
{
}
TankInfo::~TankInfo()
{
	m_waitDuration = m_speed_x = m_speed_y = 0;
}
TankInfo& TankInfo::operator=(const TankInfo& info)
{
	setDuration(info.getDuration());
	setSpeedX(info.getSpeedX());
	setSpeedy(info.getSpeedY());
	return (*this);
}
const float TankInfo::getDuration()const
{
	return m_waitDuration;
}
const float TankInfo::getSpeedX()const
{
	return m_speed_x;
}
const float TankInfo::getSpeedY()const
{
	return m_speed_y;
}
void TankInfo::setDuration(const float duration)
{
	m_waitDuration = duration;
}
void TankInfo::setSpeedX(const float x)
{
	m_speed_x = x;
}
void TankInfo::setSpeedy(const float y)
{
	m_speed_y = y;
}