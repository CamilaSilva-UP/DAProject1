#include <fstream>
#include <iostream>
#include "batchMode.h"

#include <sstream>
#include <vector>

#include "csvParsing.h"
#include "RoutePlanner.h"

void runBatchMode() {
    //read the input
    std::ifstream input("Batch_Mode_Files/input.txt");
    if (!input) {
        std::cerr << "Error opening file " << std::endl;
    }
    //Inicializar valores a ler
    std::string mode;
    int source;
    int destination;
    std::vector<int> avoidNodes;
    std::vector<int> avoidSegments;
    int includeNode;

    std::string line;

    // 1ª linha - mode
    std::getline(input, line);
    size_t pos = line.find(':');
    mode = line.substr(pos+1);
    std::cout << "Mode:" << mode << std::endl;

    // 2ª linha - source
    std::getline(input, line);
    pos = line.find(':');
    source = stoi(line.substr(pos+1));
    std::cout << "Source:" << source << std::endl;

    // 3ª linha - dest
    std::getline(input, line);
    pos = line.find(':');
    destination = stoi(line.substr(pos+1));
    std::cout << "Destination:" << destination << std::endl;

    // 3ª linha - avoidNodes (can be empty)
    std:getline(input, line);
    pos = line.find(':');
    std::string values = line.substr(pos+1);
    // remover virgulas
    for (auto& c : values) {if (c == ',') c = ' ';}
    // ler nodes para o vector
    int node;
    std::istringstream iss(values);
    while ((iss >> node)) {
        avoidNodes.push_back(node);
    }
    std::cout << "Avoiding Nodes:";
    for (auto n : avoidNodes) {std::cout << n << " ";}
    std::cout << std::endl;

    // 4ª linha - avoidsegments (não implementado)

    //5ª linha - includeNode (não implementado)


    //parse csvfiles
    csvLocationParsing("csv_examples/Locations.csv");
    csvDistancesParsing("csv_examples/Distances.csv");
    std::cout << "CSV data loaded successfully!\n";

    std::string modeToUse;
    //modo a usar
    if (mode == "driving") {
        if (!avoidNodes.empty()) {
            modeToUse = "RestrictedDriving";
        } else modeToUse = "Driving";
    }
    if (mode == "driving-walking") {
        if (!avoidNodes.empty()) {
            modeToUse = "RestrictedDrivingWalking";
        } else modeToUse = "DrivingWalking";
    }

    //execute
    if (modeToUse == "Driving") {
        RoutePlanner planner(&graph);
        std::vector<int> bestRoute;
        int bestTime = planner.calculateBestDrivingRoute(source, destination, bestRoute);
        std::vector<int> alternativeRoute;
        int altTime = planner.calculateAlternativeRoute(source, destination, alternativeRoute);
        std::ofstream output("Batch_Mode_Files/output.txt");
        output << "Source:" << source << std::endl;
        output << "Destination:" << destination << std::endl;
        output << "BestDrivingRoute:";

        output.close();
    }
}
