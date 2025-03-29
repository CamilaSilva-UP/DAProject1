//
// Created by Milla on 3/27/2025.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Graph.h"

///
///@file dijkstra.h
///@brief Header file containing the declaration of the base Dijkstra's algorithm, used for finding the shortest driving path
///

///
/// @tparam T the variable type used by the Graph
/// @param G the Graph that the algorithm will be applied to
/// @param source the source node of the route
/// @param dest the destination of the route
/// @return the distance of the shortest path from source to dest, when driving
///
///@brief Implementation of Dijkstra's algorithm
///
///@details Calculates the shortest driving path from a source node to a destination node
///
///@note Time Complexity: O((V + E) log V)
template <class T>
int dijkstra(Graph<T>* G, Vertex<T>* source, Vertex<T>* dest);

#endif //DIJKSTRA_H
