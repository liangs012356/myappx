#include "GameDirector.h"

#include "LocalVariables.h"
#include "SqliteHelper.h"
#include "MyMathUtils.h"

GameDirector* GameDirector::m_i = nullptr;

GameDirector::GameDirector() :
m_LocalVariables(nullptr),
m_SqliteHelper(nullptr),
m_MathUtils(nullptr)
{

}

GameDirector::~GameDirector()
{
	if (m_LocalVariables)
		delete m_LocalVariables;
	if (m_SqliteHelper)
		delete m_SqliteHelper;
	if (m_MathUtils)
		delete m_MathUtils;
}

GameDirector* GameDirector::getInstance()
{
	if (m_i == nullptr)
	{
		m_i = new GameDirector;
	}
	return m_i;
}
LocalVariables* GameDirector::getLocalVariables()
{
	if (m_LocalVariables == nullptr)
	{
		m_LocalVariables = new LocalVariables;
	}
	return m_LocalVariables;
}
SqliteHelper* GameDirector::getSqliteHelper()
{
	if (m_SqliteHelper == nullptr)
	{
		m_SqliteHelper = new SqliteHelper;
	}
	return m_SqliteHelper;
}
MyMathUtils* GameDirector::getMathUtils()
{
	if (m_MathUtils == nullptr)
	{
		m_MathUtils = new MyMathUtils;
	}
	return m_MathUtils;

}
