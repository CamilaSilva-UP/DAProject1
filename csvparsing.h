//
// Created by Milla on 3/20/2025.
//

#ifndef CSVPARSING_H
#define CSVPARSING_H
#include <string>
#include "Graph.h"

///
///@file csvparsing.h
///@brief Header file containing the declaration of the functions required for parsing csv files
///


extern Graph<int> graph;

/// 
/// @param filepath the filepath to the Locations.csv file, relative to the project's root directory
///
/// @brief Parses the Locations.csv file
///
/// @details Parses the Location.csv file, creating the corresponding nodes in a global Graph
///
void csvLocationParsing(const std::string& filepath);

///
/// @param filepath the filepath to the Distances.csv file, relative to the project's root directory
///
/// @brief Parses the Distances.csv file
///
/// @details Parses the Distances.csv file, creating the corresponding edges in a global Graph
///
void csvDistancesParsing(const std::string& filepath);

#endif //CSVPARSING_H
