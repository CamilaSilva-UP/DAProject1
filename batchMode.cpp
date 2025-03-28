#include <fstream>
#include <iostream>
#include "batchMode.h"

#include <sstream>
#include <vector>
#include <string>

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


        // 2ª linha - source
        std::getline(input, line);
        pos = line.find(':');
        source = std::stoi(line.substr(pos+1));


        // 3ª linha - dest
        std::getline(input, line);
        pos = line.find(':');
        destination = std::stoi(line.substr(pos+1));


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
        } else {
            std::getline(input, line);
            pos = line.find(':');
            maxWalkTime = std::stoi(line.substr(pos+1));
        }

        // 5ª linha - avoidSegments for driving, avoidNodes for driving-walking
        if (mode == "driving") {
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
        }

        //6ª linha - includeNode for driving, avoidSegments for driving-walking
        if (mode == "driving") {
            std::getline(input, line);
            pos = line.find(':');
            if (pos + 1 < line.size()) {
                includeNode = std::stoi(line.substr(pos+1));
            }
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
        }

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
            RoutePlanner planner(&graph);
            std::vector<int> restrictedRoute;
            int restrictedTime = planner.calculateRestrictedRoute(source, destination, avoidNodes, avoidSegments, includeNode, restrictedRoute);
            output << "Source:" << source << std::endl;
            output << "Destination:" << destination << std::endl;
            output << "RestrictedDrivingRoute:";
            if (restrictedTime == -1) output << "none";
            else {
                for (int i = 0; i < restrictedRoute.size(); i++) {
                    if (i == 0) output << restrictedRoute[i];
                    else output << "," << restrictedRoute[i];
                }
                output << '(' << restrictedTime << ')' << std::endl;
            }
        }
        else if (mode == "driving-walking") {
            RoutePlanner planner(&graph);
            std::vector<int> drivingRoute;
            std::vector<int> walkingRoute;
            int parkingNode = -1;

            std::pair<int,int> pairTime = planner.calculateDrivingAndWalkingRoute(source, destination,
                avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode, maxWalkTime);

            if (pairTime.first == -2) {
                output << "No route found with desired maximum walking time. Alternatives:\n";
                pairTime = planner.calculateDrivingAndWalkingRoute(source, destination,
                avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode, std::numeric_limits<int>::max());
                int totalTime = pairTime.first + pairTime.second;
                output << "Source:" << source << std::endl;
                output << "Destination:" << destination << std::endl;
                output << "DrivingRoute1:";
                for (int i = 0; i < drivingRoute.size(); i++) {
                    if (i == 0) output << drivingRoute[i];
                    else output << "," << drivingRoute[i];
                }
                output << '(' << pairTime.first << ')' << std::endl;
                output << "ParkingNode1:" << parkingNode << std::endl;
                output << "WalkingRoute1:";
                for (int i = 0; i < walkingRoute.size(); i++) {
                    if (i == 0) output << walkingRoute[i];
                    else output << "," << walkingRoute[i];
                }
                output << '(' << pairTime.second << ')' << std::endl;
                output << "TotalTime1: " << totalTime << std::endl;

                for (auto i = drivingRoute.begin() + 1; i != drivingRoute.end(); i++) {
                    avoidNodes.insert(*i);
                }
                for (auto i = walkingRoute.begin(); i != walkingRoute.end()-1; i++) {
                    avoidNodes.insert(*i);
                }
                pairTime = planner.calculateDrivingAndWalkingRoute(source, destination,
                avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode, std::numeric_limits<int>::max());

                totalTime = pairTime.first + pairTime.second;
                output << "DrivingRoute2:";
                for (int i = 0; i < drivingRoute.size(); i++) {
                    if (i == 0) output << drivingRoute[i];
                    else output << "," << drivingRoute[i];
                }
                output << '(' << pairTime.first << ')' << std::endl;
                output << "ParkingNode2:" << parkingNode << std::endl;
                output << "WalkingRoute2:";
                for (int i = 0; i < walkingRoute.size(); i++) {
                    if (i == 0) output << walkingRoute[i];
                    else output << "," << walkingRoute[i];
                }
                output << '(' << pairTime.second << ')' << std::endl;
                output << "TotalTime2: " << totalTime << std::endl;
            } else {
                pairTime = planner.calculateDrivingAndWalkingRoute(source, destination,
                avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode, std::numeric_limits<int>::max());
                int totalTime = pairTime.first + pairTime.second;
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
                output << "TotalTime: " << totalTime << std::endl;
            }
        }
    }
    output.close();
    std::cout << "Batch mode ran successfully, please check Batch_Mode_Files/output.txt for the output";
}
