#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================

class minHeap
{

public:

	minHeap();
	void insert(CEdge* value);
	CEdge* getFirst();
	void pop() { if (!values.empty())values.pop_front(); };
	int getNElements() { return int(values.size()); };
	void neteja(CVertex v);
	~minHeap() { /*if (!values.empty())values.~list();*/ };

private:

	list<CEdge*> values;
};


bool search(CVertex v, list<CVertex> lv)
{
	bool trobat = false;
	list<CVertex>::iterator it = lv.begin();

	while (!trobat && it != lv.end())
	{
		if ((*it).m_Name == v.m_Name)
			trobat = true;
		it++;
	}
	return trobat;
}


CSpanningTree SpanningTreePrim(CGraph &graph)
{
	CSpanningTree resultat(&graph);

	if (graph.GetNEdges() != 0)
	{
		minHeap llistaOrdenada;
		//list<CVertex> vertexsVisitats;
		int nVertexsVisitats = 0;
		int nVertexs = graph.GetNVertices();


		CVertex* vInicial = &(graph.m_Vertices.front());
		//resultat.m_Edges.push_back(&(graph.m_Edges.front()));

		llistaOrdenada.insert(vInicial->m_Edges.front());

		//poso el vertex actual com a vertex visitat
		//vertexsVisitats.push_back(vInicial);
		vInicial->visitat = true;
		nVertexsVisitats++;

		while (llistaOrdenada.getNElements() > 0 && nVertexsVisitats < nVertexs)
		{
			//esborrem la primera aresta de la llista
			llistaOrdenada.pop();
			//eliminem els nodes 
			llistaOrdenada.neteja(*vInicial);

			for (list<CEdge*>::iterator eIter = vInicial->m_Edges.begin(); eIter != vInicial->m_Edges.end(); eIter++)
			{
				//si el vertex on apunta l'aresta no ha estat visitat, l'afegim a la llista de candidats
				if (!(*eIter)->m_pDestination->visitat)
				{
					llistaOrdenada.insert(*eIter);
				}

			}
			//si hi ha algun candidat a la llista
			if (llistaOrdenada.getNElements() > 0)
			{
				//marco com a resposta el vertex amb menys cost dels candidats
				resultat.m_Edges.push_back(llistaOrdenada.getFirst());
				//marco com a nou vertex el que es el destí del vertex marcat com a resposta
				vInicial = (llistaOrdenada.getFirst()->m_pDestination);
				//poso el vertex actual com a vertex visitat
				vInicial->visitat = true;
				nVertexsVisitats++;
			}

		}
	}

	return resultat;	
}


minHeap::minHeap()
{
	while (!values.empty())
	{
		values.pop_back();
	}
}


void minHeap::insert(CEdge* value)
{
	list<CEdge*>::iterator it = values.begin();
	bool end = false;
	//si la llista es plena
	if (!values.empty())
	{
		//recorrem la llista fins que el valor de la nostra aresta sigui inferior al valor de la de la llista
		while (!end && *value >= *(*it))
		{
			it++;
			if (it == values.end())
			{
				end = true;
			}
		}

			
		//si no hem arribat al final de la llista
		if (!end)
			values.insert(it, value);
		//si hem arribat
		else
			values.push_back(value);
	}
	//si la llista es buida el posem directament
	else
		values.push_back(value);
}


CEdge* minHeap::getFirst()
{
	if (!values.empty())
	{
		return values.front();
	}
	else
	{
		cout << "sike!" << endl;
	}
}

void minHeap::neteja(CVertex v)
{
	list<CEdge*>::iterator it = values.begin();
	list<CEdge*>::iterator it2 = values.begin();
	
	if (values.size() > 1)
	{
		it2++;
		while (it2 != values.end())
		{
			if ((*it)->m_pDestination->m_Name == v.m_Name)
			{
				values.erase(it);
				it = it2;
				it2++;
			}
			else
			{
				it++;
				it2++;
			}
		}
	}
}


