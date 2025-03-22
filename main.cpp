#include <iostream>
#include <ostream>
#include "Graph.h"
#include "dijkstra.cpp"
#include "csvParsing.h"

int main() {
    std::cout << "Testing Graph functionality" << std::endl;
    std::cout << std::endl;
    csvLocationParsing("csv_examples/Locations.csv");
    std::cout << std::endl;
    csvDistancesParsing("csv_examples/Distances.csv");
    return  0;
}
