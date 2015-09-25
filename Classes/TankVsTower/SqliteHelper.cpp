#include "SqliteHelper.h"
#include "storage\local-storage\LocalStorage.h"
USING_NS_CC;

void SqliteHelper::closeDB()
{
	localStorageFree();
}
void SqliteHelper::setItem(const std::string& key, const std::string& value)
{
	localStorageSetItem(key, value);
}
std::string SqliteHelper::getItem(const std::string&key)
{
	std::string outItem;
	if (!localStorageGetItem(key, &outItem))
	{
		log("no item found");
	}
	return outItem;
}
void SqliteHelper::removeItem(const std::string& key)
{
	localStorageRemoveItem(key);
}

void SqliteHelper::clear()
{
	localStorageClear();
}