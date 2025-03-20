#include <iostream>
#include <ostream>
#include "Graph.h"
#include "dijkstra.cpp"
#include "csvParsing.h"

int main() {
    std::cout << "Testing Graph functionality" << std::endl;
    csvLocationParsing("csv_examples/Locations.csv");
    return  0;
}
