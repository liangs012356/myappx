#ifndef _SQLITEHELPER_H_
#define _SQLITEHELPER_H_

/*
	SqliteHelper ��һ������
	A. �������ݿ�Ĺ���
	B. �ر����ݿ�Ĺ���
	C. ���Ը���SQL���ʵ������ɾ���ġ���

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
