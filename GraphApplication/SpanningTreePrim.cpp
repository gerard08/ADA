#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================

struct comparator 
{
	bool operator()(CEdge* pE1, CEdge* pE2) { return pE1->m_Length > pE2->m_Length; }
};


CSpanningTree SpanningTreePrim(CGraph &graph)
{
	//CSpanningTree que retornarem com a resultat
	CSpanningTree resultat(&graph);

	if (graph.GetNEdges() != 0)
	{
		
		//lista ordenada de candidats
		priority_queue<CEdge*, std::vector<CEdge*>, comparator> llistaOrdenada;

		//minHeap llistaOrdenada;
		
		//variable per saber quants vertexs hem visitat
		int nVertexsVisitats = 0;
		//variable per saber els vertexs que hem de visitar
		int nVertexs = graph.GetNVertices();

		//vertex des del que començarem
		CVertex* vInicial = &(graph.m_Vertices.front());
		
		//posem una aresta a la llista de candidats per entrar al bucle
		llistaOrdenada.push(vInicial->m_Edges.front());

		//poso el vertex actual com a vertex visitat
		vInicial->visitat = true;
		//sumem el numero de vertexs visitats
		nVertexsVisitats++;


		while (llistaOrdenada.size() > 0 && nVertexsVisitats < nVertexs)
		{
			//esborrem la primera aresta de la llista
			llistaOrdenada.pop();


			for (list<CEdge*>::iterator eIter = vInicial->m_Edges.begin(); eIter != vInicial->m_Edges.end(); eIter++)
			{
				//si el vertex on apunta l'aresta no ha estat visitat, l'afegim a la llista de candidats
				if (!(*eIter)->m_pDestination->visitat)
				{
					llistaOrdenada.push(*eIter);
				}
			}

			//si hi ha algun candidat a la llista
			if (llistaOrdenada.size() > 0)
			{
				//si el primer candidat apunta a un node ja visitat el descartem
				while (!llistaOrdenada.empty() && llistaOrdenada.top()->m_pDestination->visitat)
				{
					llistaOrdenada.pop();
				}

				if (!llistaOrdenada.empty())
				{
					//marco com a resposta el vertex amb menys cost dels candidats
					resultat.m_Edges.push_back(llistaOrdenada.top());
					//marco com a nou vertex el que es el destí del vertex marcat com a resposta
					vInicial = (llistaOrdenada.top()->m_pDestination);
					//poso el vertex actual com a vertex visitat
					vInicial->visitat = true;
					nVertexsVisitats++;
				}
			}
		}
	}

	return resultat;	
}
