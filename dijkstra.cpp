#include <iostream>
#include "Graph.h"
//Implementação do algoritmo padrão de Dijkstra para calcular a rota mais rápida (driving) no grafo.
template <class T>
int disjkstra(Graph<T>* G, Vertex<T>* source, Vertex<T>* dest) {
    for (auto v : G->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    source->setDist(0);

    MutablePriorityQueue<Vertex<T>> Q;
    for (auto& v : G->getVertexSet()) {
        Q.insert(v);
    }

    while (!Q.empty()) {
        auto u = Q.extractMin();
        for (auto e : u->getAdj()) {
            auto v = e->getDest();
            if (v->getDist() > u->getDist() + e->getDrivingWeight()) {
                v->setDist(u->getDist() + e->getDrivingWeight());
                v->setPath(e);
                Q.decreaseKey(v);
            }
        }
    }

    double d = dest->getDist();
    if (d == INF)
        return -1;
    return static_cast<int>(d);
}
