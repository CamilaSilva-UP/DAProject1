#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <vector>
#include <unordered_set>
#include "Graph.h"

class RoutePlanner {
public:
    RoutePlanner(Graph<int>* g);
    int calculateBestDrivingRoute(int sourceID, int destinationID, std::vector<int>& route);
    int calculateAlternativeRoute(int sourceID, int destinationID, std::vector<int>& route);

private:
    Graph<int>* graph;

    // Método auxiliar para reconstruir a rota a partir do destino até a origem
    void reconstructRoute(Vertex<int>* source, Vertex<int>* destination, std::vector<int>& route);
};

#endif // ROUTE_PLANNER_H
