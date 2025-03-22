#include <string>
#include <fstream>
#include <iostream>
#include "Graph.h"
#include <sstream>
#include "csvparsing.h"
#include <vector>

#include <ranges>

Graph<int> graph; //Graph is a template class so needs a type to be used


//for testing purposes, make it print the values, DON'T CREATE A GRAPH UNTIL IT IS TESTED PROPERLY
//use files in csv_examples for testing


std::vector<std::string> split(std::string& s, const char& delimiter) {
    std::vector<std::string> values;
    size_t pos = 0;
    std::string value;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        value = s.substr(0, pos);
        values.push_back(value);
        s.erase(0, pos + 1);
    }
    values.push_back(s);

    return values;
}

//Parses Locations.csv and creates the vertices
void csvLocationParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 2) {
            std::cerr << "Invalid line: " << line << std::endl;
            continue;
        }
        std::string location = tokens[0]; //location name
        int id = std::stoi(tokens[1]);
        std::string code = (tokens.size() > 2) ? tokens[2] : "";
        bool parking = (tokens.size() > 3) && tokens[3] == "1";

        std::cout << "Location: " << location << ",Id: " << id << ", Code: " << code << ", Parking: " << parking << std::endl;
        graph.addVertex(id, location, code, parking);
    }

        //for (const auto& token : tokens) {
          //  std::cout << token << '|';
        //}
        //std::cout << std::endl;
}

//Parses Distances.csv and creates the edges
void csvDistancesParsing(const std::string& filepath){
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line);

    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3) {
            std::cerr << "Invalid line: " << line << std::endl;
            continue;

        }
        int id1 = std::stoi(tokens[0]);
        int id2 = std::stoi(tokens[1]);
        double distance = std::stod(tokens[2]);

        std::cout << "Id1: " << id1 << ", Id2: " << id2 << ", Distance: " << distance << std::endl;

        std::string strId1 = std::to_string(id1);
        std::string strId2 = std::to_string(id2);
        graph.addEdge(strId1, strId2, distance, distance);

    }
}


