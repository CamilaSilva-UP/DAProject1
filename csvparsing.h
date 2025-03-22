//
// Created by Milla on 3/20/2025.
//

#ifndef CSVPARSING_H
#define CSVPARSING_H
#include <string>
#include "Graph.h"

extern Graph<int> graph;

void csvLocationParsing(const std::string& filepath);

void csvDistancesParsing(const std::string& filepath);

#endif //CSVPARSING_H
