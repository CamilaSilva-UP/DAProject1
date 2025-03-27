//
// Created by Milla on 3/27/2025.
//

#ifndef DIJKSTRA_ALT_H
#define DIJKSTRA_ALT_H
#include <unordered_set>
#include "Graph.h"

///
///@file dijkstra_alt.h
///@brief Header file containing the declaration of an altered version Dijkstra's algorithm that ignores certain nodes
///



template <class T>
int alternative_dijkstra(Graph<T>* G, Vertex<T>* source, Vertex<T>* dest, const std::unordered_set<T>& forbidden);

#endif //DIJKSTRA_ALT_H
