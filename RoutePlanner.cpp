#include "RoutePlanner.h"
#include "dijkstra.cpp"      // Função disjkstra para a rota principal
#include "dijkstra_alt.cpp"  // Função alternative_dijkstra para a rota alternativa
#include <algorithm>
#include <iostream>
#include <unordered_set>

//métodos para reconstruir e calcular rotas utilizando os algoritmos de Dijkstra.
RoutePlanner::RoutePlanner(Graph<int>* g) : graph(g) {}

void RoutePlanner::reconstructRoute(Vertex<int>* source, Vertex<int>* destination, std::vector<int>& route) {
    route.clear();
    Vertex<int>* current = destination;
    while (current != nullptr && current != source) {
        route.push_back(current->getInfo());
        current = current->getPath() ? current->getPath()->getOrig() : nullptr;
    }
    if (current == source)
        route.push_back(source->getInfo());
    std::reverse(route.begin(), route.end());
}

int RoutePlanner::calculateBestDrivingRoute(int sourceID, int destinationID, std::vector<int>& route) {
    // Apanhar os vértices de origem e destino
    Vertex<int>* sourceVertex = graph->findVertex(sourceID);
    Vertex<int>* destinationVertex = graph->findVertex(destinationID);

    if (!sourceVertex || !destinationVertex) {
        std::cerr << "Source or destination vertex not found.\n";
        return -1;
    }

    // Main Route
    int totalTime = dijkstra(graph, sourceVertex, destinationVertex);
    if (totalTime == -1)
        return -1;

    // Reconstruir a rota
    reconstructRoute(sourceVertex, destinationVertex, route);
    return totalTime;
}

int RoutePlanner::calculateAlternativeRoute(int sourceID, int destinationID, std::vector<int>& route) {
    Vertex<int>* sourceVertex = graph->findVertex(sourceID);
    Vertex<int>* destinationVertex = graph->findVertex(destinationID);

    if (!sourceVertex || !destinationVertex) {
        std::cerr << "Source or destination vertex not found.\n";
        return -1;
    }

    // Primeiro, calcular a rota principal para identificar os nós a excluir
    int primaryTime = dijkstra(graph, sourceVertex, destinationVertex);
    if (primaryTime == -1)
        return -1;

    // Reconstruir a rota principal
    std::vector<int> primaryRoute;
    reconstructRoute(sourceVertex, destinationVertex, primaryRoute);

    // Criar o set de nós a excluir (excluindo a origem e o destino)
    std::unordered_set<int> forbidden;
    for (size_t i = 1; i < primaryRoute.size() - 1; i++) {
        forbidden.insert(primaryRoute[i]);
    }

    // Calcular a rota alternativa ignorando os nós proibidos
    int alternativeTime = alternative_dijkstra(graph, sourceVertex, destinationVertex, forbidden, {});
    if (alternativeTime == -1)
        return -1;

    // Reconstruir a rota alternativa
    reconstructRoute(sourceVertex, destinationVertex, route);
    return alternativeTime;
}

// Calcula a rota excluindo nós específicos do grafo
int RoutePlanner::calculateRestrictedRoute(int sourceID, int destinationID, const std::unordered_set<int>& avoidNodes, const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments, int includeNode, std::vector<int>& route) {
    Vertex<int>* sourceVertex = graph->findVertex(sourceID);
    Vertex<int>* destinationVertex = graph->findVertex(destinationID);
    if (!sourceVertex || !destinationVertex) {
        std::cerr << "Source or destination vertex not found.\n";
        return -1;
    }
    //Se o includeNode for diferente de -1, fazer o Dijkstra alternativo até ao nó a incluir, e depois até ao destino
    if (includeNode != -1) {
        auto includeVertex = graph->findVertex(includeNode);
        if (includeVertex == nullptr) std::cerr << "Include node not found.\n";

        int time1 = alternative_dijkstra(graph, sourceVertex, includeVertex, avoidNodes, avoidSegments);
        if (time1 == -1) return -1;
        reconstructRoute(sourceVertex, includeVertex, route);

        std::vector<int> temp;
        int time2 = alternative_dijkstra(graph, includeVertex, destinationVertex, avoidNodes, avoidSegments);
        if (time2 == -1) return -1;
        reconstructRoute(includeVertex, destinationVertex, temp);
        route.insert(route.end(), temp.begin() + 1, temp.end());
        return time1 + time2;
    }

    // Usamos o nosso algoritmo de Dijkstra alternativo, mas com o avoidNodes
    int restrictedTime = alternative_dijkstra(graph, sourceVertex, destinationVertex, avoidNodes, avoidSegments);
    if (restrictedTime == -1)
        return -1;
    reconstructRoute(sourceVertex, destinationVertex, route);
    return restrictedTime;
}

std::pair<int,int> RoutePlanner::calculateDrivingAndWalkingRoute(int sourceID, int destinationID,
    std::unordered_set<int>& avoidNodes,
    const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments,
    std::vector<int>& drivingRoute,
    std::vector<int>& walkingRoute,
    int& parkingNode) {
    Vertex<int>* sourceVertex = graph->findVertex(sourceID);
    Vertex<int>* destinationVertex = graph->findVertex(destinationID);

    if (!sourceVertex || !destinationVertex) {
        std::cerr << "Source or destination vertex not found.\n";
        return std::make_pair(-1, 0);
    }

    // Finds the best parking until the dest
    parkingNode = -1;
    int minWalkingDistance = INT_MAX;

    for (auto vertex : graph->getVertexSet()) {
        int nodeId = vertex->getInfo();
        if (avoidNodes.find(nodeId) != avoidNodes.end()) continue;
        if (vertex-> getParking ()) {
            // Calculates the walking time from the parking to the destination
            int walkingTime = walking_alt_dijkstra(graph, vertex, destinationVertex, avoidNodes, avoidSegments);
            if (walkingTime != -1 && walkingTime < minWalkingDistance) {
                minWalkingDistance = walkingTime;
                parkingNode = nodeId;
            }
        }
    }

    if (parkingNode == -1) {
        std::cerr << "No suitable parking node found.\n";
        return std::make_pair(-1, 0);;
    }

    // Calculates the best driving route until the parking
    int drivingTime = alternative_dijkstra(graph, sourceVertex, graph->findVertex(parkingNode), avoidNodes, avoidSegments);
    if (drivingTime == -1) {
        std::cerr << "No driving route found.\n";
        return std::make_pair(-1, 0);;
    }
    reconstructRoute(sourceVertex, graph->findVertex(parkingNode), drivingRoute);

    // Calculates the best route of park and walk until the dest
    int walkingTime = walking_alt_dijkstra(graph, graph->findVertex(parkingNode), destinationVertex, avoidNodes, avoidSegments);
    if (walkingTime == -1) {
        std::cerr << "No walking route found.\n";
        return std::make_pair(-1, 0);
    }
    reconstructRoute(graph->findVertex(parkingNode), destinationVertex, walkingRoute);

    return std::make_pair(drivingTime, walkingTime);
}

