#include <string>
#include <fstream>
#include <iostream>


//for testing purposes, make it print the values, DON'T CREATE A GRAPH UNTIL IT IS TESTED PROPERLY

//Parses Locations.csv and creates the vertices
void csvLocationParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
    }

}

//Parses Distances.csv and creates the edges
void csvDistancesParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
    }

}
