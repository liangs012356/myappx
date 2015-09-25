#ifndef _SQLITETEST_H_
#define _SQLITETEST_H_

#include "cocos2d.h"
#include "sqlite3.h"
USING_NS_CC;


class SqliteTest : public Layer
{
public:
	static Scene * createScene();

	virtual bool init();
	virtual bool onTouchBegan(Touch *toch, Event * eevent);
	virtual void onTouchEnded(Touch *toch, Event * eevent);
	CREATE_FUNC(SqliteTest);
private:
	sqlite3 *m_database;
	std::string m_data_path;
};

#endif //_SQLITETEST_H_