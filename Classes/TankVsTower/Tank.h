#ifndef _TANKVSTOWER_TANK_H_
#define _TANKVSTOWER_TANK_H_

#include "cocos2d.h"



class TankInfo
{
public:
	TankInfo();
	TankInfo(const TankInfo& info);
	TankInfo(const float duration, const float speedx, const float speedy);
	virtual ~TankInfo();

	TankInfo& operator=(const TankInfo& info);
public:
	const float getDuration()const;
	const float getSpeedX()const;
	const float getSpeedY()const;
	inline void setDuration(const float duration);
	inline void setSpeedX(const float x);
	inline void setSpeedy(const float y);
private:
	float m_waitDuration;
	float m_speed_x;
	float m_speed_y;
};

class TankTurret;

class Tank : public cocos2d::Sprite
{
public:
	bool initWithInfo(std::string& filePath, TankInfo& info);
	static Tank* createWithInfo(std::string& filePath, TankInfo& info);
	void startWait();
	void waitSchedule(float dt);
	void moveSchedule(float dt);
private:
	TankInfo m_tank_info;
};

class TankTurret :public cocos2d::Sprite
{

};


#endif /* define(_TANKVSTOWER_TANK_H_) */