#pragma once
#ifndef _Graph_h_
#define _Graph_h_

#include <string>
#include <unordered_map>

class Vertex;
class Arrow;

class Graph
{
public:
	enum type{DIGRAPH,UNDIGRAPH};
public:
	Graph(type t);
	~Graph();

	static Graph * create(type t = DIGRAPH);

	Vertex * insertVex(std::string name);

	Arrow * insertArr(std::string tail, std::string head, int weight = 1);

	bool deleteVex(const std::string name);
	bool deleteArr(std::string tail, std::string head);
	bool deleteArr(Arrow * arrow);
	bool deleteArr(Vertex * vtail, Vertex * vhead);

	Vertex * findVer(std::string name);
	Arrow * findArr(std::string t, std::string h);
	Arrow * findArr(Vertex * tail, Vertex * head);
	Vertex * findFirstAdjVex(Vertex * v);
	Vertex * findNextAdjVex(Vertex * v, Vertex * w);

	bool visited(Vertex * v);
	void visit(Vertex * vertex);

	void DFS(Vertex * v);
	void DFSTraverse();

	void BFSTraverse();

	void minitree_prim(Vertex* root);
	void minitree_Kruskal(Vertex **root);

	Vertex* minipath_Dijkstra(Vertex* src, Vertex* dest);
protected:
	void freeFromSameTailList(Arrow * arrow);

	void freeFromSameTailList(Vertex * vTail, Arrow * arrow);

	void freeFromSameHeadList(Arrow * arrow);

	void freeFromSameHeadList(Vertex * vHead, Arrow * arrow);

private:
	std::unordered_multimap<std::string, Vertex*>m_vertex;

	type m_type;
};


class Vertex
{
public:
	Vertex(Arrow * firstin, Arrow * firstout, std::string name);
	~Vertex();

	void set(Arrow * firstin, Arrow * firstout, std::string & name);

	Arrow * getFirstIn() const;
	void setFirsIn(Arrow * firstin);

	Arrow * getFirstOut() const;
	void setFirstOut(Arrow * firstout);

	std::string & getName();
	void setName(const std::string & name);
private:
	Arrow* m_firstin;
	Arrow* m_firstout;
	std::string m_name;
};

class Arrow
{
public:
	Arrow();
	~Arrow();
	void set(Vertex * tail, Vertex * head, Arrow * nextSameH, Arrow * nextSameT, int weight);
	Vertex * getTail()const;
	Vertex * getHead()const;
	Arrow * getNextArrowSameHead()const;
	void setNextArrowSameHead(Arrow * a);
	Arrow * getNextArrowSameTail()const;
	void setNextArrowSameTail(Arrow * a);
	int getWeight()const;
	void setWeight(int weight);

private:
	Vertex* m_head;
	Vertex* m_tail;
	Arrow*  m_next_sameH;
	Arrow*	m_next_sameT;
	int	m_weight;
};



#endif /* define(_Graph_h_) */