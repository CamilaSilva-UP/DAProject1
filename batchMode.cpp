#include <fstream>
#include <iostream>
#include "batchMode.h"

#include <sstream>
#include <vector>

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


}
