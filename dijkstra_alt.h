//
// Created by Milla on 3/27/2025.
//

#ifndef DIJKSTRA_ALT_H
#define DIJKSTRA_ALT_H
#include <unordered_set>
#include "Graph.h"
#include "pair_hash.h"
///
///@file dijkstra_alt.h
///@brief Header file containing the declaration of an altered version Dijkstra's algorithm that ignores specified nodes
///


///
/// @tparam T the variable type used by the Graph
/// @param G the Graph that the algorithm will be applied to
/// @param source the source node of the route
/// @param dest the destination of the route
/// @param forbidden the set of nodes that will be ignored by the algorithm
/// @param avoidSegments A set of edges, represented by a pair of node IDs, that will be avoided in the calculation of the route
/// @return the distance of the shortest path from source to dest, when driving
///
/// @brief Altered implementation of Dijkstra's algorithm that ignores specified nodes
///
/// @details Calculates the shortest driving path from a source node to a destination node, without passing by any of the nodes in the forbidden set.
template <class T>
int alternative_dijkstra(Graph<T>* G, Vertex<T>* source, Vertex<T>* dest, const std::unordered_set<T>& forbidden, const std::unordered_set<std::pair<int, int>, pair_hash<int, int>>& avoidSegments);

#endif //DIJKSTRA_ALT_H
