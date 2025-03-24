#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <vector>
#include <unordered_set>
#include "Graph.h"
#include "pair_hash.h"

class RoutePlanner {
public:
    RoutePlanner(Graph<int>* g);
    int calculateBestDrivingRoute(int sourceID, int destinationID, std::vector<int>& route);
    int calculateAlternativeRoute(int sourceID, int destinationID, std::vector<int>& route);
    int calculateRestrictedRoute(int sourceID, int destinationID, const std::unordered_set<int>& avoidNodes, std::vector<int>& route);
    int calculateDrivingAndWalkingRoute(int sourceID, int destinationID, std::unordered_set<int>& avoidNodes, const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments, std::vector<int>& drivingRoute, std::vector<int>& walkingRoute, int& parkingNode);

private:
    Graph<int>* graph;

    // Método auxiliar para reconstruir a rota a partir do destino até a origem
    void reconstructRoute(Vertex<int>* source, Vertex<int>* destination, std::vector<int>& route);
};

#endif // ROUTE_PLANNER_H
