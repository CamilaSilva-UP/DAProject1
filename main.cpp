// main.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include "csvParsing.h"     // Funções para ler os ficheiros CSV e carregar a instância global "graph"
#include "Graph.h"          // Estrutura do grafo
#include "RoutePlanner.h"   // Classe que encapsula a lógica de cálculo de rotas
#include <limits>
#include "batchMode.h" // Função para correr o programa em BatchMode


// Função para exibir o menu principal
void showMainMenu() {
    std::cout << "\n==== Main Menu ====\n";
    std::cout << "1. Load CSV Files\n";
    std::cout << "2. Select Mode\n";
    std::cout << "3. Execute Functionality\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";

}

// Função para exibir o menu de seleção de modo
void showModeMenu() {
    std::cout << "\n==== Select Mode ====\n";
    std::cout << "1. Driving\n";
    std::cout << "2. Driving + Walking\n";
    std::cout << "3. Restricted Routes\n";
    std::cout << "Enter your mode choice: ";
}

// Função para exibir o menu de seleção de modo batch
void showInitialMenu() {
    std::cout << "\n==== Select Mode ====\n";
    std::cout << "1. Menu Mode\n";
    std::cout << "2. Batch Mode\n";
    std::cout << "Enter your mode choice: ";
}

int main() {

    int batch;
    showInitialMenu();
    std::cin >> batch;

    while (batch < 1 || batch > 2 || !std::cin >> batch) {
        std::cout << "Invalid Input\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        showInitialMenu();
        std::cin >> batch;
    }

    if (batch == 1) {
        int option;
        bool dataLoaded = false;
        int selectedMode = 1; // Modo padrão: Driving

        while (true) {
            showMainMenu();
            std::cin >> option;

            while (option < 1 || option > 4 || !std::cin >> option) {
                std::cout << "Invalid Input\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                showMainMenu();
                std::cin >> option;
            }

            if (option == 1) {
                csvLocationParsing("csv_examples/Locations.csv");
                csvDistancesParsing("csv_examples/Distances.csv");
                std::cout << "CSV data loaded successfully!\n";
                dataLoaded = true;
            } else if (option == 2) {
                showModeMenu();
                int mode;
                std::cin >> mode;

                if (mode < 1 || mode > 3 || !std::cin >> mode) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid mode. Defaulting to Driving.\n";
                    selectedMode = 1;
                } else {
                    selectedMode = mode;
                }
                std::cout << "Selected mode: ";
                if (selectedMode == 1)
                    std::cout << "Driving\n";
                else if (selectedMode == 2) {
                    std::cout << "Driving + Walking mode selected.\n";
                }
                else if (selectedMode == 3)
                    std::cout << "Restricted Routes\n";
            } else if (option == 3) {
                if (!dataLoaded) {
                    std::cout << "Please load CSV data first (Option 1).\n";
                    continue;
                }
                RoutePlanner planner(&graph);
                if (selectedMode == 1) {
                    int sourceID, destinationID;
                    std::cout << "Driving mode selected.\n";
                    std::cout << "Enter source ID: ";
                    std::cin >> sourceID;
                    std::cout << "Enter destination ID: ";
                    std::cin >> destinationID;

                    //Principal route
                    std::vector<int> bestRoute;
                    int bestTime = planner.calculateBestDrivingRoute(sourceID, destinationID, bestRoute);
                    if (bestTime == -1) {
                        std::cout << "No path exists between " << sourceID << " and " << destinationID << ".\n";
                    } else {
                        std::cout << "BestDrivingRoute time: " << bestTime << " minutes.\n";
                        std::cout << "BestDrivingRoute: ";
                        for (size_t i = 0; i < bestRoute.size(); i++) {
                            std::cout << bestRoute[i];
                            if (i < bestRoute.size() - 1)
                                std::cout << " -> ";
                        }
                        std::cout << "\n";

                        //Alternative route
                        std::vector<int> alternativeRoute;
                        int altTime = planner.calculateAlternativeRoute(sourceID, destinationID, alternativeRoute);
                        if (altTime == -1) {
                            std::cout << "AlternativeDrivingRoute:none\n";
                        } else {
                            std::cout << "AlternativeDrivingRoute time: " << altTime << " minutes.\n";
                            std::cout << "AlternativeDrivingRoute: ";
                            for (size_t i = 0; i < alternativeRoute.size(); i++) {
                                std::cout << alternativeRoute[i];
                                if (i < alternativeRoute.size() - 1)
                                    std::cout << " -> ";
                            }
                            std::cout << "\n";
                        }
                    }
                } else if (selectedMode == 2) {
                    std::cout << "Driving + Walking mode selected.\n";
                    int sourceID, destinationID;
                    std::unordered_set<int> avoidNodes;
                    std::unordered_set<std::pair<int, int>, pair_hash<int, int>> avoidSegments;
                    // Enter the source ID and the destination ID
                    std::cout << "Enter source <ID>: ";
                    std::cin >> sourceID;
                    std::cout << "Enter destination <ID>: ";
                    std::cin >> destinationID;

                    // Nodes to avoid
                    std::string avoidNodesInput;
                    std::cout << "Enter AvoidNodes (separated by commas): ";
                    std::cin.ignore();
                    std::getline(std::cin, avoidNodesInput);

                    std::stringstream ss(avoidNodesInput);
                    std::string token;
                    while (std::getline(ss, token, ',')) {
                        if (token.empty()) continue;
                        try {
                            avoidNodes.insert(std::stoi(token));
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Invalid value in AvoidNodes: " << token << "\n";
                        }
                    }

                    // Edges to avoid
                    std::string avoidSegmentsInput;
                    std::cout << "Enter AvoidSegments (format: 1-2, separated by commas): ";
                    std::getline(std::cin, avoidSegmentsInput);

                    std::stringstream ssSegments(avoidSegmentsInput);
                    while (std::getline(ssSegments, token, ',')) {
                        if (token.empty()) continue;
                        try {
                            size_t pos = token.find('-');
                            if (pos != std::string::npos) {
                                int node1 = std::stoi(token.substr(0, pos));
                                int node2 = std::stoi(token.substr(pos + 1));
                                avoidSegments.insert({node1, node2});
                            }
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Invalid segment in AvoidSegments: " << token << "\n";
                        }
                    }

                    // Define the variables for the driving and walking routes
                    std::vector<int> drivingRoute;
                    std::vector<int> walkingRoute;
                    int parkingNode = -1;  // Este valor será alterado pela função se necessário

                    // Calculates the driving + walking routes

                    std::pair<int,int> pairTime = planner.calculateDrivingAndWalkingRoute(sourceID, destinationID,
                        avoidNodes, avoidSegments, drivingRoute, walkingRoute, parkingNode);
                    int totalTime = pairTime.first + pairTime.second;
                    if (totalTime == -1) {
                        std::cout << "No valid combined route found.\n";
                    } else {
                        std::cout << "Driving + Walking combined route time: " << totalTime << " minutes.\n";
                        std::cout << "Driving route: ";
                        for (size_t i = 0; i < drivingRoute.size(); i++) {
                            std::cout << drivingRoute[i];
                            if (i < drivingRoute.size() - 1)
                                std::cout << " -> ";
                        }
                        std::cout << "\n";

                        std::cout << "Parking: " << parkingNode << '\n';

                        std::cout << "Walking route: ";
                        for (size_t i = 0; i < walkingRoute.size(); i++) {
                            std::cout << walkingRoute[i];
                            if (i < walkingRoute.size() - 1)
                                std::cout << " -> ";
                        }
                        std::cout << "\n";
                    }
                } else if (selectedMode == 3) {
                    // Restricted Routes
                    int sourceID, destinationID;
                    std::string avoidNodesInput, avoidSegmentsInput;
                    std::cout << "Restricted Routes mode selected.\n";
                    std::cout << "Enter source ID: ";
                    std::cin >> sourceID;
                    std::cout << "Enter destination ID: ";
                    std::cin >> destinationID;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa tudo até ao '\n'

                    std::cout << "Enter Nodes to Avoid (separated with a comma): ";
                    std::getline(std::cin, avoidNodesInput);

                    //Nodes to avoid
                    std::unordered_set<int> avoidNodes;
                    std::stringstream ss(avoidNodesInput);
                    std::string token;
                    while (std::getline(ss, token, ',')) {
                        if (token.empty()) continue;
                        try {
                            avoidNodes.insert(std::stoi(token));
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Invalid value in AvoidNodes: " << token << "\n";
                        }
                    }

                    // Edges to avoid
                    std::unordered_set<std::pair<int, int>, pair_hash<int, int>> avoidSegments;
                    std::cout << "Enter AvoidSegments (format: 1-2, separated by commas): ";
                    std::getline(std::cin, avoidSegmentsInput);

                    std::stringstream ssSegments(avoidSegmentsInput);
                    while (std::getline(ssSegments, token, ',')) {
                        if (token.empty()) continue;
                        try {
                            size_t pos = token.find('-');
                            if (pos != std::string::npos) {
                                int node1 = std::stoi(token.substr(0, pos));
                                int node2 = std::stoi(token.substr(pos + 1));
                                avoidSegments.insert({node1, node2});
                            }
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Invalid segment in AvoidSegments: " << token << "\n";
                        }
                    }

                    // Node to include
                    int includeNode = -1;
                    std::cout << "Enter IncludeNode (leave empty for none): ";
                    std::cin >> includeNode;

                    std::cout << "Nodes to Avoid: ";
                    for (auto node : avoidNodes) {
                        std::cout << node << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Edges to Avoid: ";
                    for (auto edge : avoidSegments) {
                        std::cout << edge.first << "->" << edge.second << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Node to Include: ";
                    if (includeNode != -1) std::cout << includeNode;
                    std::cout << "\n";


                    // Calcular a rota restrita
                    std::vector<int> restrictedRoute;
                    int restrictedTime = planner.calculateRestrictedRoute(sourceID, destinationID, avoidNodes, avoidSegments, includeNode, restrictedRoute);
                    if (restrictedTime == -1) {
                        std::cout << "RestrictedDrivingRoute:none\n";
                    } else {
                        std::cout << "RestrictedDrivingRoute time: " << restrictedTime << " minutes.\n";
                        std::cout << "RestrictedDrivingRoute: ";
                        for (size_t i = 0; i < restrictedRoute.size(); i++) {
                            std::cout << restrictedRoute[i];
                            if (i < restrictedRoute.size() - 1)
                                std::cout << " -> ";
                        }
                        std::cout << "\n";
                    }
                }
            } else if (option == 4) {
                std::cout << "Exiting...\n";
                break;
            } else {
                std::cout << "Invalid option. Please try again.\n";
            }
        }
    } else if (batch == 2) {
        runBatchMode();
    }
    return 0;
}
