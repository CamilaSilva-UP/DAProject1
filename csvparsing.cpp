#include <string>
#include <fstream>
#include <iostream>
#include "Graph.h"
#include <sstream>
#include "csvparsing.h"
#include <vector>

#include <ranges>


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
    std::getline(input, line);  // first row is not needed
    while (std::getline(input, line)) {
        std::vector<std::string> values = split(line, ',');
        for (const auto& value : values) {
            std::cout << value << '|';
        }
        std::cout << std::endl;
    }
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
        std::vector<std::string> values = split(line, ',');
        for (const auto& value : values) {
            std::cout << value << '|';
        }
        std::cout << std::endl;
    }
}

