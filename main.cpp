#include <iostream>
#include <ostream>
#include "Graph.h"
#include "dijkstra.cpp"
#include "csvParsing.h"

int main() {
    std::cout << "Testing Graph functionality" << std::endl;
    std::cout << std::endl;
    csvLocationParsing("csv_examples/Locations.csv");


    Graph<int> graph;

    // (Location)
    int id1 = 1;
    int id2 = 2;
    std::string locationName1 = "Location1";
    std::string locationName2 = "Location2";
    bool hasParking1 = true;
    bool hasParking2 = false;

    // Convert ids to std::string
    std::string strId1 = std::to_string(id1);
    std::string strId2 = std::to_string(id2);

    // Add vertex to the graff with location info
    graph.addVertex(id1, strId1, locationName1, hasParking1);
    graph.addVertex(id2, strId2, locationName2, hasParking2);

    // Test each edge
    Vertex<int> *v1 = graph.findVertex(id1);  // Find the vertex with id1
    Vertex<int> *v2 = graph.findVertex(id2);  // Find the vertex with id2

    // Now we can acess data in variables
    if (v1 != nullptr && v2 != nullptr) {
        int idFromV1 = v1->getInfo(); // Id v1
        int idFromV2 = v2->getInfo(); // Id v2

        std::string codeFromV1 = v1->getCode(); // Code v1
        std::string codeFromV2 = v2->getCode(); // Code v2

        std::string nameFromV1 = v1->getName(); // Name v1
        std::string nameFromV2 = v2->getName(); // Name v2

        bool parkingFromV1 = v1->getParking(); // Check if it has parking in v1
        bool parkingFromV2 = v2->getParking(); // Check if it has parking in v2

        // Cout the values of the variables
        std::cout << "Location 1 Info: " << idFromV1 << ", " << codeFromV1 << ", " << nameFromV1 << ", Parking: " << (parkingFromV1 ? "Yes" : "No") << std::endl;
        std::cout << "Location 2 Info: " << idFromV2 << ", " << codeFromV2 << ", " << nameFromV2 << ", Parking: " << (parkingFromV2 ? "Yes" : "No") << std::endl;
    }

    return 0;
}

