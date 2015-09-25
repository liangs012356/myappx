#ifndef _LOCALVARRIABLES_H_
#define _LOCALVARRIABLES_H_

#include <map>
#include <string>
#include "cocos2d.h"
/* 
		�����������
			1. ������Ҫ���ݳ־û���һЩ���ݣ��洢���ڴ棬����ʵ�ã�
			2. ���������ݳ־û��������
			3. ���� ϵͳI/0 ���ã�ϵͳI/0 �ǳ���ʱ����
		�����๦��
			1. ���Զ�дint;
			2. ���Զ�дbool��
			3. ���Զ�дfloat;
			4. ���Զ�дstring;
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