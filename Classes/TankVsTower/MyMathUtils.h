#ifndef _MYMATHUTILS_H_
#define _MYMATHUTILS_H_

#include "cocos2d.h"


class MyMathUtils
{

public:

		// 1. �������������ȡ��������
	cocos2d::Point getNormalizedPoint(cocos2d::Point & target, cocos2d::Point & src);
		// 2. �������������ȡ��ת�Ƕ�
	float getDegree(cocos2d::Point& target, cocos2d::Point& src);
		// 3. �������������ȡ����
	float getRadius(cocos2d::Point& target, cocos2d::Point& src);

	static std::string MyMathUtils::WStrToUTF8(const std::wstring& src);
};


#endif /*_MYMATHUTILS_H_*/