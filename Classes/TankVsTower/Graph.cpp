#include <algorithm>
#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Graph.h"

/*************************************class Graph*****************************************/

Graph::Graph(type t)
	:m_vertex(), m_type(t)
{

}

Graph::~Graph()
{
	for (auto it = m_vertex.begin(); it != m_vertex.end();it++)
	{
		deleteVex(it->first);
	}
	m_vertex.clear();

}

Graph * Graph::create(type t)
{
	Graph* g = new(std::nothrow)Graph(t);
	assert(g);

	return g;
}

Vertex* Graph::insertVex(std::string name)
{
	auto it = m_vertex.find(name);
	if (it != m_vertex.end())
	{
		return nullptr;
	}

	auto v = new(std::nothrow)Vertex(nullptr, nullptr, name);

	if (!v)
	{
		return nullptr;
	}

	m_vertex.insert(std::make_pair(name, v));

	return v;
}

Arrow * Graph::insertArr(std::string tail, std::string head, int weight)
{
	auto it1 = m_vertex.find(tail);
	auto it2 = m_vertex.find(head);

	/* make sure both tail and head vertex is exist */
	if (it1 == m_vertex.end() || it2 == m_vertex.end())
		return nullptr;

	Vertex* pVTail = it1->second;
	Vertex* pVhead = it2->second;

	Arrow *arrow = findArr(pVTail, pVhead);
	if (arrow)
	{
		return arrow;
	}
	else
	{
		arrow = new(std::nothrow)Arrow;
		assert(arrow);

		arrow->set(pVTail, pVhead, pVhead->getFirstIn(), pVTail->getFirstOut(), weight);

		pVTail->setFirstOut(arrow);
		pVhead->setFirsIn(arrow);
	}

	if (m_type == Graph::type::UNDIGRAPH)
	{
		Arrow* arrow1 = new(std::nothrow)Arrow;
		assert(arrow1);

		arrow1->set(pVhead, pVTail, pVTail->getFirstIn(), pVhead->getFirstOut(), weight);

		pVhead->setFirstOut(arrow1);
		pVTail->setFirsIn(arrow1);
	}

	return arrow;

}

bool Graph::deleteVex(const std::string name)
{
	auto it = m_vertex.find(name);
	if (it == m_vertex.end()) {
		return false;
	}
	Vertex* v = it->second;

	Arrow* p = v->getFirstOut();
	Arrow* q = nullptr;
	while (p) {
		q = p->getNextArrowSameTail();
		freeFromSameHeadList(p);
		delete p;
		p = q;
	}

	p = v->getFirstIn();
	q = nullptr;
	while (p) {
		q = p->getNextArrowSameHead();
		freeFromSameTailList(p);
		delete p;
		p = q;
	}

	delete v;
	v = nullptr;
	m_vertex.erase(name);

	return true;
}

bool Graph::deleteArr(std::string tail, std::string head)
{
	auto it1 = m_vertex.find(tail);
	auto it2 = m_vertex.find(head);
	if (it1 == m_vertex.end() || it2 == m_vertex.end())
		return false;

	return deleteArr(it1->second, it2->second);
}

bool Graph::deleteArr(Arrow *arrow)
{
	return deleteArr(arrow->getTail(), arrow->getHead());
}

bool Graph::deleteArr(Vertex *vtail, Vertex *vhead)
{
	Arrow* arrow = findArr(vtail, vhead);
	if (!arrow)
	{
		return false;
	}

	freeFromSameHeadList(vhead, arrow);
	freeFromSameTailList(vtail, arrow);

	delete arrow;
	arrow = nullptr;

	if (m_type == DIGRAPH)
	{
		Arrow* arrow2 = findArr(vhead, vtail);
		if (!arrow2)
		{
			return false;
		}

		freeFromSameHeadList(vtail, arrow2);
		freeFromSameTailList(vhead, arrow2);

		delete arrow2;
		arrow2 = nullptr;
	}

	return true;
}

Vertex * Graph::findVer(std::string name)
{
	auto it = m_vertex.find(name);
	if (it != m_vertex.end())
	{
		return it->second;
	}
	return nullptr;
}

Arrow * Graph::findArr(std::string t, std::string h)
{
	Vertex* tail = findVer(t);
	Vertex* head = findVer(h);

	return findArr(tail, head);
}

Arrow * Graph::findArr(Vertex *tail, Vertex *head)
{
	if (tail && head)
	{

		Arrow *p = tail->getFirstOut();
		while (p)
		{
			if (p->getHead() == head)
				return p;
			p = p->getNextArrowSameTail();
		}

	}

	return nullptr;
}

Vertex * Graph::findFirstAdjVex(Vertex *v)
{
	assert(v);
	Arrow* a = v->getFirstOut();

	if (a)
		return a->getHead();

	return nullptr;
}

Vertex * Graph::findNextAdjVex(Vertex *v, Vertex *w)
{
	assert(v && w);
	Arrow* a = findArr(v, w);
	assert(a);
	a = a->getNextArrowSameTail();
	if (a)
	{
		return a->getHead();
	}

	return nullptr;
}

static std::unordered_multimap<Vertex*, bool>isvisite;
bool Graph::visited(Vertex * v)
{
	auto it = isvisite.find(v);
	if (it == isvisite.end())
	{
		isvisite.insert(std::make_pair(v, false));
		return false;
	}
	else
	{
		return it->second;
	}
}

void Graph::visit(Vertex * vertex)
{

#ifdef _DEBUG
	std::cout << vertex->getName() << "\t";
#endif
	auto it = isvisite.find(vertex);
	assert(it != isvisite.end());

	it->second = true;
}

void Graph::DFS(Vertex * v)
{
	if (!visited(v)) {
		visit(v);

#ifdef _DEBUG
		std::cout << v << std::endl;
#endif

	}
	for (Vertex* w = findFirstAdjVex(v); w; w = findNextAdjVex(v, w))
	{
		if (!visited(w)) {
			DFS(w);
		}
	}
}

void Graph::DFSTraverse()
{
	isvisite.clear();

	for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	{
		if (visited(it->second) == false) {

#ifdef _DEBUG
			std::cout << "\nnew visit root Vertex\n";
#endif

			DFS(it->second);
		}
	}

#ifdef _DEBUG
	std::cout << "\n" << std::endl;
#endif

}

void Graph::BFSTraverse()
{
	isvisite.clear();
	for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	{
		visited(it->second);
	}

	std::queue<Vertex*> qvisit;
	for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	{
		if (visited(it->second) == false) {

#ifdef _DEBUG
			std::cout << "\nnew visit Vertex\n";
#endif
			visit(it->second);
			qvisit.push(it->second);
			while (!qvisit.empty())
			{
				Vertex* root = qvisit.front();
				assert(root);
				qvisit.pop();
				for (Vertex* w = findFirstAdjVex(root); w; w = findNextAdjVex(root, w))
				{
					if (!visited(w))
					{
						visit(w);
						isvisite.find(w)->second = true;
						qvisit.push(w);
					}
				}
			}
		}
	}

#ifdef _DEBUG
	std::cout << "\n" << std::endl;
#endif
	for (auto it = m_vertex.begin(); it != m_vertex.end(); it++)
	{
		isvisite.find(it->second)->second = false;
	}
}

void Graph::minitree_prim(Vertex* root)
{
	/* an vertex set that all vertex could be add to tree when the cost is low,
	 it increase when you walk on the graph and find an new vertex,  decrease when
	 the way to him is most low*/
	std::unordered_multimap<Vertex*, Arrow*>F;

	/* It is the "road" in the tree and you find them on the graph */
	std::vector<Arrow*>R;

	/* All vertex fond will be hear when you find a minicost way to it */
	std::unordered_set<Vertex*>U;
	
	/*
		u: Vertex in F;
		v: Vertex new fond;
		uv: u->v / Arrow that to F;
	*/
	Vertex* u = root;
	U.insert(u);
	do
	{
		// #1:	update the way to vertex_fond infomation
		Arrow* uv = u->getFirstOut();
		Vertex* v = nullptr;
		while(uv)
		{
			v = uv->getHead();
			auto atv = F.find(v);
			auto atu = U.find(v);

			if (atv != F.end()) {
				assert(atu == U.end());
				auto uvold = atv->second;
				
				if (!(uvold && (uvold->getWeight() < uv->getWeight()))) {
					F.erase(v);
					F.insert(std::make_pair(v, uv));
				}
			}
			else if (atu == U.end())
			{
				F.insert(std::make_pair(v, uv));
			}
			else
			{
				assert(true);
			}
			uv = uv->getNextArrowSameTail();			
		}
		// #2:	find the mini cost way 
		Arrow* uvmini = nullptr;
		for (auto it = F.begin(); it != F.end(); it++)
		{
			if (!it->second)
				continue;

			Arrow* uvfind = it->second;
			if (!uvmini)
				uvmini = uvfind;
			if (uvmini->getWeight() > uvfind->getWeight())
				uvmini = uvfind;
		}
		
		// #3:	Save the way and move the vertex from F to U.		
		R.push_back(uvmini);
		u = uvmini->getHead();
		F.erase(F.find(u));
		U.insert(u);
	} while (!F.empty());

#ifdef _DEBUG
	for (auto i : R)
	{
		std::cout << i->getTail()->getName().c_str()
			<< i->getHead()->getName().c_str()
			<< i->getNextArrowSameTail()
			<< i->getNextArrowSameHead()
			<< i->getWeight()
			<< std::endl;
	}
#endif
	
	F.clear();
	U.clear();
}

void Graph::minitree_Kruskal( Vertex **root)
{
	std::unordered_set<Vertex*>U;
	std::vector<const Arrow*>R;
	std::vector<const Arrow*>VR;

	for (auto& it : m_vertex)
	{
		Arrow* r = it.second->getFirstOut();
		while (r)
		{
			VR.push_back(r);
			r = r->getNextArrowSameTail();
		}
	}

#ifdef _DEBUG
	printf("before sort\n");
		for (auto it : VR)
		{
			printf("%d", it->getWeight());
		}
	putchar(10);
#endif
	// sort VR : prepare for kruskal select the arrow
	std::sort(VR.begin(), VR.end(), [=](const Arrow *f, const Arrow *s)->bool {
		return f->getWeight() < s->getWeight();
	});

#ifdef _DEBUG
	printf("after sort\n");
	for (auto it : VR)
	{
		printf("%d", it->getWeight());
	}
	putchar(10);
#endif

	Vertex* rooot= VR.at(0)->getTail();
	for (auto it = VR.begin(); it != VR.end(); it++)
	{
		Vertex* u = (*it)->getHead();
		Vertex* v = (*it)->getTail();
		if (U.find(rooot) != U.end())
			rooot = v;
		
		if (U.find(u) == U.end())
		{
			U.insert(u);
			R.push_back(*it);
		}
	}
	*root = rooot;
#ifdef _DEBUG
	for (auto i : R)
	{
		std::cout << i->getTail()->getName().c_str() 
			<<	i->getHead()->getName().c_str()
			<< i->getNextArrowSameTail() 
			<< i->getNextArrowSameHead() 
			<< i->getWeight() 
			<< std::endl;
	}
#endif

	U.clear();
	VR.clear();
}

Vertex* Graph::minipath_Dijkstra(Vertex * src, Vertex * dst)
{
	std::unordered_multimap<Vertex*, Vertex*>U;
	std::unordered_multimap<Vertex*, std::pair<Vertex*, int>>F;

	U.insert(std::make_pair(src, nullptr));
	Vertex* u = src;
	int c = 0;

	// update imfomation in vertex fond set by the mini value
	do
	{
		Arrow* uv = u->getFirstOut();
		// insert an Vertex when it is not fond both in U set and F set
		// change an Vertex when there is another vertex cost more less.
		while (uv)
		{
			Vertex* v = uv->getHead();
			auto it = F.find(v);

			if (it == F.end())
			{
				if (U.find(v) == U.end())
				{
					F.insert(std::make_pair(v, std::make_pair(u, c + uv->getWeight())));
				}
			}
			else
			{
				assert(U.find(v) == U.end());
				int ct = c + uv->getWeight();
				if (ct < it->second.second)
				{
					F.erase(v);
					F.insert(std::make_pair(v, std::make_pair(u, c + uv->getWeight())));
				}
			}

			uv = uv->getNextArrowSameTail();
		} // while(uv)

		u = F.begin()->first;
		c = F.begin()->second.second;
		for (auto it = F.begin(); it != F.end(); it++)
		{
			if (c > it->second.second)
			{
				u = it->first;
				c = it->second.second;
			}
		}
		
		U.insert(std::make_pair(u, F.find(u)->second.first));
		F.erase(u);

	} while (U.find(dst) == U.end() && !F.empty());

#ifdef _DEBUG
	auto it = U.find(dst);
	while (it->second)
	{
		std::cout << it->first->getName() << "<--";
		it = U.find(it->second);
	}
	std::cout << it->first->getName() << std::endl;
#endif

	auto It = U.find(dst);
	while (It->second != src)
	{
		It = U.find(It->second);
	}
	u = It->first;

	U.clear();
	F.clear();
	return u;
}

void Graph::freeFromSameTailList(Arrow * arrow)
{
	Vertex* vTail = arrow->getTail();
	freeFromSameTailList(vTail, arrow);
}

void Graph::freeFromSameTailList(Vertex * vTail, Arrow * arrow)
{
	Arrow* p = vTail->getFirstOut();
	if (p == arrow)
	{
		vTail->setFirstOut(p->getNextArrowSameTail());
	}
	else
	{
		while (p->getNextArrowSameTail() != arrow)
			p = p->getNextArrowSameTail();
		p->setNextArrowSameTail(arrow->getNextArrowSameTail());
	}
}

void Graph::freeFromSameHeadList(Arrow * arrow)
{
	Vertex* vHead = arrow->getHead();
	freeFromSameHeadList(vHead, arrow);
}

void Graph::freeFromSameHeadList(Vertex * vHead, Arrow * arrow)
{
	Arrow* p = vHead->getFirstIn();
	if (p == arrow)
	{
		vHead->setFirsIn(p->getNextArrowSameHead());
	}
	else
	{
		while (p->getNextArrowSameHead() != arrow)
			p = p->getNextArrowSameHead();
		p->setNextArrowSameHead(arrow->getNextArrowSameHead());
	}
}

/****************************************class Vertex********************************************/

Vertex::Vertex(Arrow* firstin, Arrow* firstout, std::string name)
	:m_firstin(firstin), m_firstout(firstout), m_name(name)
{
}

Vertex::~Vertex()
{
	m_firstin = nullptr;
	m_firstin = nullptr;
}

void Vertex::set(Arrow* firstin, Arrow* firstout, std::string &name)
{
	m_firstin = firstin;
	m_firstout = firstout;
	m_name = name;
}

Arrow * Vertex::getFirstIn() const
{
	return m_firstin;
}

void Vertex::setFirsIn(Arrow * firstin)
{
	m_firstin = firstin;
}

Arrow * Vertex::getFirstOut() const
{
	return m_firstout;
}

void Vertex::setFirstOut(Arrow * firstout)
{
	m_firstout = firstout;
}

std::string & Vertex::getName()
{
	return m_name;
}

void Vertex::setName(const std::string & name)
{
	m_name = name;
}



/*******************************************class Arrow***************************************/

Arrow::Arrow()
	:m_head(nullptr), m_tail(nullptr), m_next_sameH(nullptr), m_next_sameT(nullptr), m_weight(1)
{
}

Arrow::~Arrow()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_next_sameH = nullptr;
	m_next_sameT = nullptr;
	m_weight = 0;
}

void Arrow::set(Vertex * tail, Vertex * head, Arrow * nextSameH, Arrow * nextSameT, int weight)
{
	m_tail = tail, m_head = head;
	m_next_sameH = nextSameH, m_next_sameT = nextSameT;
	m_weight = weight;
}

Vertex * Arrow::getTail()const
{
	return m_tail;
}

Vertex * Arrow::getHead()const
{
	return m_head;
}

Arrow * Arrow::getNextArrowSameHead()const
{
	return m_next_sameH;
}

void Arrow::setNextArrowSameHead(Arrow  *a)
{
	m_next_sameH = a;
}

Arrow * Arrow::getNextArrowSameTail()const
{
	return m_next_sameT;
}

void Arrow::setNextArrowSameTail(Arrow *a)
{
	m_next_sameT = a;
}

int Arrow::getWeight() const
{
	return m_weight;
}

void Arrow::setWeight(int weight)
{
	m_weight = weight;
}


/******************************************************************************************/
