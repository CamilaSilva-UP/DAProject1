#include <iostream>
#include "Graph.h"

template <class T>
int disjkstra(Graph<T>* G, Vertex<T> *source, Vertex<T> *dest){
    //Initialize
    for(auto v : G->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    source->setDist(0);

    //Priority queue
    MutablePriorityQueue<Vertex<T>> Q;
    for (auto& v : G->getVertexSet()) {
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

    int dist = dest->getDist();
    if (dist == INF) return -1;
    return dist;
}
