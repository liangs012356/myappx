#ifndef _MYMATHUTILS_H_
#define _MYMATHUTILS_H_

#include "cocos2d.h"


class MyMathUtils
{

public:

		// 1. 根据两点坐标获取方向向量
	cocos2d::Point getNormalizedPoint(cocos2d::Point & target, cocos2d::Point & src);
		// 2. 根据亮点坐标获取旋转角度
	float getDegree(cocos2d::Point& target, cocos2d::Point& src);
		// 3. 根据两点坐标获取弧度
	float getRadius(cocos2d::Point& target, cocos2d::Point& src);

	static std::string MyMathUtils::WStrToUTF8(const std::wstring& src);
};


#endif /*_MYMATHUTILS_H_*/