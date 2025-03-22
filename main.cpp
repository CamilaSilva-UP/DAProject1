#include <iostream>
#include <vector>
#include <algorithm>
#include "csvParsing.h"   // Funções para ler os ficheiros CSV e a global instance "graph"
#include "Graph.h"        // Estrutura do grafo
#include "dijkstra.cpp"   // Algoritmo de Dijkstra

void showMainMenu() {
    std::cout << "\n==== Main Menu ====\n";
    std::cout << "1. Load CSV Files\n";
    std::cout << "2. Select Mode\n";
    std::cout << "3. Execute Functionality\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

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
    int selectedMode = 1; // Default mode: Driving

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
            if (selectedMode == 1) {
                int sourceID, destinationID;
                std::cout << "Driving mode selected.\n";
                std::cout << "Enter source ID: ";
                std::cin >> sourceID;
                std::cout << "Enter destination ID: ";
                std::cin >> destinationID;

                Vertex<int>* sourceVertex = graph.findVertex(sourceID);
                Vertex<int>* destinationVertex = graph.findVertex(destinationID);

                if (sourceVertex && destinationVertex) {
                    int totalTime = disjkstra(&graph, sourceVertex, destinationVertex);
                    if (totalTime == -1) {
                        std::cout << "No path exists between " << sourceID << " and " << destinationID << ".\n";
                    } else {
                        std::cout << "Shortest path (Driving) time: " << totalTime << " minutes.\n";
                        // Reconstruir a rota
                        std::vector<int> route;
                        Vertex<int>* current = destinationVertex;
                        while (current != nullptr && current != sourceVertex) {
                            route.push_back(current->getInfo());
                            current = current->getPath() ? current->getPath()->getOrig() : nullptr;
                        }
                        if (current == sourceVertex)
                            route.push_back(sourceVertex->getInfo());
                        std::reverse(route.begin(), route.end());
                        std::cout << "Route: ";
                        for (size_t i = 0; i < route.size(); i++) {
                            std::cout << route[i];
                            if (i < route.size() - 1)
                                std::cout << " -> ";
                        }
                        std::cout << "\n";
                    }
                } else {
                    std::cout << "Invalid source or destination.\n";
                }
            } else if (selectedMode == 2) {
                std::cout << "Driving + Walking mode selected. Functionality not yet implemented.\n";
            } else if (selectedMode == 3) {
                std::cout << "Restricted Routes mode selected. Functionality not yet implemented.\n";
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
