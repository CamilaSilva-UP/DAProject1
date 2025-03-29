#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <vector>
#include <unordered_set>
#include "Graph.h"
#include "pair_hash.h"

///
///@file RoutePlanner.h
///@brief RoutePlanner class. These methods are used to reconstruct and calculate routes using Dijkstra's algorithm
///


class RoutePlanner {
public:
    ///
    /// @param g The graph that the planner will be constructed for
    RoutePlanner(Graph<int>* g);

    ///
    /// @param sourceID The id of the source node
    /// @param destinationID The id of the destination node
    /// @param route A reference to a vector where the route will be stored
    /// @return The distance of the route calculated
    ///
    /// @brief Planner for the best driving route
    /// @details Calculates and saves the best driving route from a source node to a destination node
    ///
    /// @note Time Complexity: O((V + E) log V)
    int calculateBestDrivingRoute(int sourceID, int destinationID, std::vector<int>& route);

    ///
    /// @param sourceID The id of the source node
    /// @param destinationID The id of the destination node
    /// @param route A reference to a vector where the route will be stored
    /// @return The distance of the route calculated
    ///
    /// @brief Planner for the alternate driving route
    /// @details Calculates the best driving route from a source node to a destination node, and then finds an alternative route where none of the intermediate nodes are the same
    ///
    /// @note Time Complexity: O((V + E) log V)
    int calculateAlternativeRoute(int sourceID, int destinationID, std::vector<int>& route);

    ///
    /// @param sourceID The id of the source node
    /// @param destinationID The id of the destination node
    /// @param avoidNodes A set of node IDs that will be avoided in the calculation of the route
    /// @param avoidSegments A set of edges, represented by a pair of node IDs, that will be avoided in the calculation of the route
    /// @param includeNode Node to be included in the path
    /// @param route A reference to a vector where the route will be stored
    /// @return The distance of the route calculated
    ///
    /// @brief Planner for the best driving route, avoiding a specified set of nodes
    /// @details Calculates and saves the best driving route from a source node to a destination node, without passing by any of the nodes with an ID in the avoidNodes set
    ///
    /// @note Time Complexity: O((V + E) log V)
    int calculateRestrictedRoute(int sourceID, int destinationID, const std::unordered_set<int>& avoidNodes, const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments, int includeNode, std::vector<int>& route);

    ///
    /// @param sourceID The id of the source node
    /// @param destinationID The id of the destination node
    /// @param avoidNodes A set of node IDs that will be avoided in the calculation of the route
    /// @param avoidSegments A set of edges, represented by a pair of node IDs, that will be avoided in the calculation of the route
    /// @param drivingRoute A reference to a vector where the driving section of the route will be stored
    /// @param walkingRoute A reference to a vector where the walking section of the route will be stored
    /// @param parkingNode A reference to a variable where the ID of the parking node will be stored
    /// @param maxWalkTime The maximum walk time desired for the route
    /// @return A pair containing the distance of the driving route (first) and the distance of the walking route (second). Returns {-1, 0} if no route is found, and {-2, 0} if the route found exceeds the maximum walking time desired
    ///
    /// @brief Planner for the best driving and walking route
    /// @details Calculates and saves the best route combining a driving segment and a waling segment, without passing by any of the nodes with an ID in the avoidNodes set or any of the edges in the avoidSegments set
    ///
    /// @note Time Complexity: O((V + E) log V)
    std::pair<int,int> calculateDrivingAndWalkingRoute(int sourceID, int destinationID, std::unordered_set<int>& avoidNodes, const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments,
        std::vector<int>& drivingRoute, std::vector<int>& walkingRoute, int& parkingNode, int maxWalkTime);

private:
    Graph<int>* graph;

    ///
    /// @param source The id of the source node
    /// @param destination The id of the destination node
    /// @param route A reference to a vector where the route will be stored
    ///
    /// @brief Helper method to reconstruct a route
    /// @details Creates and saves the route from the source node to the destination node by checking the node's predecessors
    ///
    /// @note Time Complexity: O(V)
    void reconstructRoute(Vertex<int>* source, Vertex<int>* destination, std::vector<int>& route);
};

#endif // ROUTE_PLANNER_H
