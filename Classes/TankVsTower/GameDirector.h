/*
	GameDirector.h
	ÖÐ½éÄ£Ê½
	2015-9-5
*/

#ifndef _GAMEDIRCTOR_H_
#define _GAMEDIRCTOR_H_


class LocalVariables;
class SqliteHelper;
class MyMathUtils;

class GameDirector
{
public:
	GameDirector();
	virtual ~GameDirector();
public:
	static GameDirector* getInstance();
	LocalVariables* getLocalVariables();
	SqliteHelper* getSqliteHelper();
	MyMathUtils* getMathUtils();
private:
	static GameDirector* m_i;
	LocalVariables* m_LocalVariables;
	SqliteHelper* m_SqliteHelper;
	MyMathUtils* m_MathUtils;
};


#endif /*_GAMEDIRCTOR_H_*/