//
// Created by matildeoliveirasilvafeup on 14/03/2025.
//
#include "Graph.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

template <class T>
Vertex <T>::Vertex(T in) : info(in), visited(false), processign(false), low(-1), num(-1), indegree(0), dist(INF), path(nullptr) {}

template <class T>
bool Vertex<T>::operator<(const Vertex<T> &vertex) const {
  return this ->dist < vertex.dist; //returns if the distance from the actual vertex is < then the other vertex
}

//info associated to the vertex
template <class T>
T Vertex<T>::getInfo() const {
  return this->info;
}
//get the value of low
template <class T>
int Vertex<T>::getLow() const {
  return this->low;
}
//define the value of low
template <class T>
void Vertex<T>::setLow(int value) {
  this->low = value;
}

//DFS Algorithm to obtain the number of order of the vertex
template <class T>
void Vertex<T>::setNum(int value) {
  this->num = value;
}

//get adjacent edges to the vertex
template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
  return this->adj;
}

//checks if the vertex was visited or not
template <class T>
bool Vertex<T>::isVisited() const {
  return this->visited;
}
template <class T>
bool Vertex<T>::isProcessing() const {
  return this->processing;
}
//degree of the vertex
template <class T>
usigned int Vertex<T>::getIndegree() const { //cannot be negative the degree of a vertex
  return this->indegree;
}

//distance associated to the vertex
template <class T>
double Vertex<T>::getDist() const {
  return this->dist;
}

//get the edge that leads to the vertex Dijkstra Algorithm
template <class T>
Edge<T> *Vertex<T>::getPath() const {
  return this->path;
}

//get the edges
template <class T>
vector<Edge<T>* > Vertex<T>::getIncoming() const {
  return this->incoming;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
  this->visited = visited;
}
template <class T>
void Vertex<T>::setInfo(T in) {
  this->info = in;
}
template <class T>
void Vertex<T>::setProcessing(bool processing) {
  this->processing = processing;
}
template <class T>
void Vertex<T>::setIndegree(int value) {
  this->indegree = indegree;
}
template <class T>
void Vertex<T>::setDist(double dist) {
  this->dist = dist;
}
template <class T>
void Vertex<T>::setPath(vector<Edge<T>* > path) {
  this->path = path;
}

//adds an edge into 'this' to the destiny edge with weight 'w' and the edge goes to the list of adjacency's
template <class T>
Edge<T>* Vertex<T>::addEdge(Vertex<T>* d, double w) {
  auto newEdge = new Edge<T>(this,d,w);
  adj.push_back(newEdge);
  d-> incoming.push_back(newEdge);
  return newEdge;

}