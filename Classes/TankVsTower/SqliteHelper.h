#ifndef _SQLITEHELPER_H_
#define _SQLITEHELPER_H_

/*
	SqliteHelper 是一个单例
	A. 开启数据库的功能
	B. 关闭数据库的功能
	C. 可以根据SQL语句实现增、删、改、查

*/


#include "cocos2d.h"


class SqliteHelper
{
public:
	void closeDB();
	void setItem(const std::string& key, const std::string& value);
	std::string getItem(const std::string& key);
	void removeItem(const std::string& key);
	void clear();
};


#endif  // _SQLITEHELPER_H_
