#include <iostream>
#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <unordered_set>


// Implementação do algoritmo de Dijkstra alternativo que evita nós proibidos para calcular a rota secundária.

// Raciocínio:
/*
1. Executar o Dijkstra “normal” para encontrar a melhor rota.

2. Reconstruir essa rota e obter um conjunto (por exemplo, um std::unordered_set) dos nós do meio a excluir.

3. Executar um segundo Dijkstra, mas com um “filtro” que ignora qualquer relaxamento
para um vértice cujo ID esteja no conjunto de nós proibidos (com exceção da origin e destination).

4. Se a rota alternativa existir, mostrar ambos os caminhos com os seus tempos;
caso contrário, imprimir “AlternativeDrivingRoute:none” (e same para a rota principal, se não existir).
 */


// Dijkstra, mas que ignora os vértices do meio
template <class T>
int alternative_dijkstra(Graph<T>* G, Vertex<T>* source, Vertex<T>* dest, const std::unordered_set<T>& forbidden) {
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
            // Se v for um nó proibido (mas se for o destino, permitimos)
            if (v != dest && forbidden.find(v->getInfo()) != forbidden.end())
                continue;
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
