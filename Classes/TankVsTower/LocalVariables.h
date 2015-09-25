#ifndef _LOCALVARRIABLES_H_
#define _LOCALVARRIABLES_H_

#include <map>
#include <string>
#include "cocos2d.h"
/* 
		缓存类的作用
			1. 将不需要数据持久化的一些数据，存储到内存，方便实用；
			2. 方便与数据持久化相关联；
			3. 减少 系统I/0 调用（系统I/0 非常耗时）；
		缓存类功能
			1. 可以读写int;
			2. 可以读写bool；
			3. 可以读写float;
			4. 可以读写string;
*/

class LocalVariables
{
public:
	void setInt(const std::string & key, int val);
	int getInt(std::string & key);
	void setBool(std::string & key, bool val);
	bool getBool(std::string & key);
	void setFloat(std::string & key, float val);
	float getFloat(std::string & key);
	void setString(std::string & key, std::string & val);
	std::string getString(std::string & key);
private:
	std::map<std::string, cocos2d::Value>m_cache_map;
};

#endif