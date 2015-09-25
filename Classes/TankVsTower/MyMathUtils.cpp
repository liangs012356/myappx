#include "MyMathUtils.h"

USING_NS_CC;

// 1. �������������ȡ��������
Point MyMathUtils::getNormalizedPoint(Point & target, Point & src)
{
	auto subPos = target - src;
	return subPos.getNormalized();
}
// 2. �������������ȡ��ת�Ƕ�
float MyMathUtils::getDegree(Point& target, Point& src)
{
	float radius = getRadius(target, src);
	return CC_RADIANS_TO_DEGREES(radius);
}
// 3. �������������ȡ����
float MyMathUtils::getRadius(Point& target, Point& src)
{
	auto normalizedPos = getNormalizedPoint(target, src);
	return atan2f(normalizedPos.x, normalizedPos.y);
}

std::string MyMathUtils::WStrToUTF8(const std::wstring& src)

{

	std::string dest;

	dest.clear();

	for (size_t i = 0; i < src.size(); i++)

	{

		wchar_t w = src[i];

		if (w <= 0x7f)

		{

			dest.push_back((char)w);

		}

		else if(w <= 0x7ff)

		{

			dest.push_back(0xc0 | ((w >> 6) & 0x1f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else if(w <= 0xffff)

		{

			dest.push_back(0xe0 | ((w >> 12) & 0x0f));

			dest.push_back(0x80 | ((w >> 6) & 0x3f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else if(sizeof(wchar_t) > 2 && w <= 0x10ffff)

		{

			dest.push_back(0xf0 | ((w >> 18) & 0x07));

			dest.push_back(0x80 | ((w >> 12) & 0x3f));

			dest.push_back(0x80 | ((w >> 6) & 0x3f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else

			dest.push_back('?');

	}

	return dest;

}