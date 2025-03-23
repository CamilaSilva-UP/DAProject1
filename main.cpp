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

int main() {
    int option;
    bool dataLoaded = false;
    int selectedMode = 1; // Modo padrão: Driving

    while (true) {
        showMainMenu();
        std::cin >> option;

        if (option == 1) {
            csvLocationParsing("csv_examples/Locations.csv");
            csvDistancesParsing("csv_examples/Distances.csv");
            std::cout << "CSV data loaded successfully!\n";
            dataLoaded = true;
        } else if (option == 2) {
            showModeMenu();
            int mode;
            std::cin >> mode;
            if (mode < 1 || mode > 3) {
                std::cout << "Invalid mode. Defaulting to Driving.\n";
                selectedMode = 1;
            } else {
                selectedMode = mode;
            }
            std::cout << "Selected mode: ";
            if (selectedMode == 1)
                std::cout << "Driving\n";
            else if (selectedMode == 2)
                std::cout << "Driving + Walking\n";
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

                // Calcular a melhor rota (rota principal)
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

                    // Calcular a rota alternativa
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
                std::cout << "Driving + Walking mode selected. Functionality not yet implemented.\n";
            } else if (selectedMode == 3) {
                // Restricted Routes
                int sourceID, destinationID;
                std::string avoidNodesInput;
                std::cout << "Restricted Routes mode selected.\n";
                std::cout << "Enter source ID: ";
                std::cin >> sourceID;
                std::cout << "Enter destination ID: ";
                std::cin >> destinationID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa tudo até ao '\n'

                std::cout << "Enter Nodes to Avoid (separated with a comma): ";
                std::getline(std::cin, avoidNodesInput);

                // Processar a entrada dos nós a evitar
                std::unordered_set<int> avoidNodes;
                std::stringstream ss(avoidNodesInput);
                std::string token;
                while (std::getline(ss, token, ',')) {
                    if (token.empty()) continue; // Ignorar se estiver vazio
                    try {
                        avoidNodes.insert(std::stoi(token));
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid value in AvoidNodes: " << token << "\n";
                    }
                }

                std::cout << "Nodes to Avoid: ";
                for (auto node : avoidNodes) {
                    std::cout << node << " ";
                }
                std::cout << "\n";

                // Calcular a rota restrita
                std::vector<int> restrictedRoute;
                int restrictedTime = planner.calculateRestrictedRoute(sourceID, destinationID, avoidNodes, restrictedRoute);
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
    return 0;
}
