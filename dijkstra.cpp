#include <iostream>
#include "Graph.h"

template <class T>
void Disjkstra(Graph<T>* G, Vertex<T> *source){
    //Initialize
    for(auto v : G->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    source->setDist(0);

    //Priority queue
    MutablePriorityQueue<Vertex<T>> Q;
    for (auto v : G->getVertexSet()) {
        Q.insert(v);
    }

    //main loop
    while (!Q.empty()) {
        auto u = Q.extractMin();
        for (auto e : u->getAdj()) {
            auto v = e->getDest();
            //Relax Edge
            if (v->getDist() > u->getDist() + e->getWeight()) {
                v->setDist(u->getDist() + e->getWeight());
                v->setPath(e);
                Q.decreaseKey(v);
            }
        }
    }
}
