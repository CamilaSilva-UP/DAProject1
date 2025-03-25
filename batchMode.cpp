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
        std::cerr << "Error opening input file " << std::endl;
    }

    std::ofstream output("Batch_Mode_Files/output.txt");

    //parse csvfiles
    csvLocationParsing("csv_examples/Locations.csv");
    csvDistancesParsing("csv_examples/Distances.csv");
    std::cout << "CSV data loaded successfully!\n";

    //ler a tag
    std::string tagLine;
    while (std::getline(input, tagLine) && tagLine[0] == '#') {
        output << tagLine << std::endl;
        //Inicializar valores a ler
        std::string mode;
        int source;
        int destination;
        std::unordered_set<int> avoidNodes;
        std::unordered_set<std::pair<int, int>, pair_hash<int, int>> avoidSegments;
        int includeNode;
        int maxWalkTime;

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

        // 4ª linha - avoidNodes for driving, maxWalkTime for driving-walking
        if (mode == "driving") {
            std:getline(input, line);
            pos = line.find(':');
            std::string values = line.substr(pos+1);
            // remover virgulas
            for (auto& c : values) {if (c == ',') c = ' ';}
            // ler nodes para o vector
            int node;
            std::istringstream iss(values);
            while ((iss >> node)) {
                avoidNodes.insert(node);
            }
            std::cout << "Avoiding Nodes:";
            for (auto n : avoidNodes) {std::cout << n << " ";}
            std::cout << std::endl;
        } else {
            std::getline(input, line);
            pos = line.find(':');
            maxWalkTime = stoi(line.substr(pos+1));
            std::cout << "MaxWalkTime:" << maxWalkTime << std::endl;
        }

        // 5ª linha - avoidSegments for driving, avoidNodes for driving-walking
        if (mode == "driving") {
            //avoidSegments not yet implemented
            std::getline(input, line);
        } else {
            std::getline(input, line);
            pos = line.find(':');
            std::string values = line.substr(pos+1);
            // remover virgulas
            for (auto& c : values) {if (c == ',') c = ' ';}
            // ler nodes para o vector
            int node;
            std::istringstream iss(values);
            while ((iss >> node)) {
                avoidNodes.insert(node);
            }
            std::cout << "Avoiding Nodes:";
            for (auto n : avoidNodes) {std::cout << n << " ";}
            std::cout << std::endl;
        }

        //6ª linha - includeNode for driving, avoidSegments for driving-walking
        if (mode == "driving") {
            //includeNode not yet implemented
            std::getline(input, line);
        } else {
            std::getline(input, line);
            pos = line.find(':');
            std::string values = line.substr(pos+1);
            // remover virgulas
            for (auto& c : values) {if (c == ',' || c == '(' || c == ')' || c == '-') c = ' ';}
            // ler nodes para o set
            int node1, node2;
            std::istringstream iss(values);
            while ((iss >> node1) && iss >> node2) {
                avoidSegments.insert({node1, node2});
            }
            std::cout << "Avoiding Segments:";
            for (auto n : avoidSegments) {std::cout << n.first << ',' << n.second << " ";}
            std::cout << std::endl;
        }

        std::string modeToUse;
        //modo a usar
        if (mode == "driving") {
            if (!avoidNodes.empty()) {
                modeToUse = "RestrictedDriving";
            } else modeToUse = "Driving";
        } else modeToUse = "DrivingWalking";

        //execute
        if (mode == "driving" && avoidNodes.empty()) {
            RoutePlanner planner(&graph);
            std::vector<int> bestRoute;
            int bestTime = planner.calculateBestDrivingRoute(source, destination, bestRoute);
            std::vector<int> alternativeRoute;
            int altTime = planner.calculateAlternativeRoute(source, destination, alternativeRoute);
            output << "Source:" << source << std::endl;
            output << "Destination:" << destination << std::endl;
            output << "BestDrivingRoute:";
            for (int i = 0; i < bestRoute.size(); i++) {
                if (i == 0) output << bestRoute[i];
                else output << "," << bestRoute[i];
            }
            output << '(' << bestTime << ')' << std::endl;
            output << "AlternativeDrivingRoute:";
            for (int i = 0; i < alternativeRoute.size(); i++) {
                if (i == 0) output << alternativeRoute[i];
                else output << "," << alternativeRoute[i];
            }
            output << '(' << altTime << ')' << std::endl;
        }
        else if (mode == "driving" && !avoidNodes.empty()) {
            //TODO (Restricted)
        }
        else if (mode == "driving-walking") {
            std::vector<int> drivingRoute;
            std::vector<int> walkingRoute;
            int parkingNode = -1;
            RoutePlanner planner(&graph);
            std::pair<int,int> pairTime = planner.calculateDrivingAndWalkingRoute(source, destination,
                        avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode);

            output << "Source:" << source << std::endl;
            output << "Destination:" << destination << std::endl;
            output << "DrivingRoute:";
            for (int i = 0; i < drivingRoute.size(); i++) {
                if (i == 0) output << drivingRoute[i];
                else output << "," << drivingRoute[i];
            }
            output << '(' << pairTime.first << ')' << std::endl;
            output << "ParkingNode:" << parkingNode << std::endl;
            output << "WalkingRoute:";
            for (int i = 0; i < walkingRoute.size(); i++) {
                if (i == 0) output << walkingRoute[i];
                else output << "," << walkingRoute[i];
            }
            output << '(' << pairTime.second << ')' << std::endl;
            output << "TotalTime:" << pairTime.first + pairTime.second << std::endl;
        }
    }
    output.close();
    std::cout << "Batch mode ran successfully, please check Batch_Mode_Files/output.txt for the output";
}
