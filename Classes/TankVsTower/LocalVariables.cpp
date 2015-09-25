#include "LocalVariables.h"

USING_NS_CC;


/*
	根据key设置整形数 
*/
void LocalVariables::setInt(const std::string & key, int val)
{
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		m_cache_map.insert(std::make_pair(key, Value(val)));
		return;
	}
	valIt->second = Value(val);
	return;
}


/*
根据key获取整形数
*/
int LocalVariables::getInt(std::string & key)
{
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		std::string error = StringUtils::format("no value is found in key: %s", key.c_str());
		CCASSERT(false, error.c_str());
		return 0;
	}
	return valIt->second.asInt();
}
void LocalVariables::setBool(std::string & key, bool val){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		m_cache_map.insert(std::make_pair(key, Value(val)));
		return;
	}
	valIt->second = Value(val);
	return;
}
bool LocalVariables::getBool(std::string & key){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		std::string error = StringUtils::format("no value is found in key: %s", key.c_str());
		CCASSERT(false, error.c_str());
		return false;
	}
	return valIt->second.asBool();
}
void LocalVariables::setFloat(std::string & key, float val){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		m_cache_map.insert(std::make_pair(key, Value(val)));
		return;
	}
	valIt->second = Value(val);
	return;
}
float LocalVariables::getFloat(std::string & key){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		std::string error = StringUtils::format("no value is found in key: %s", key.c_str());
		CCASSERT(false, error.c_str());
		return 0;
	}
	return valIt->second.asFloat();
}
void LocalVariables::setString(std::string & key,std::string & val){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		m_cache_map.insert(std::make_pair(key, Value(val)));
		return;
	}
	valIt->second = Value(val);
	return;
}
std::string LocalVariables::getString(std::string & key){
	auto valIt = m_cache_map.find(key);
	if (valIt == m_cache_map.end())
	{
		std::string error = StringUtils::format("no value is found in key: %s", key.c_str());
		CCASSERT(false, error.c_str());
		return "";
	}
	return valIt->second.asString();
}
