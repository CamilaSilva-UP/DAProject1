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
std:: vector<std::string> split(const std::string& line, char delim) {
    std:: vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delim)) {
        token.erase(0, token.find_first_not_of(delim));
        token.erase(token.find_last_not_of(delim) + 1);
        tokens.push_back(token);
    }
    return tokens;
}
//Parses Locations.csv and creates the vertices
void csvLocationParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }

    //for (std::string line; std::getline(input,line);){
      //std::cout << line <<std::endl;
      //divides the line in tokens separed by ','
      //std::istringstream iss(line);
      //for(std::string token; std::getline(iss,token, ',');){
        //std::cout << token << ' | ';
      //}
      //std::cout << std::endl;
    //}
    std::string line;
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        for (const auto& token : tokens) {
            std::cout << token << '|';
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
    //for(std::string line; std::getline(input,line);){
     // std::cout << line <<std::endl;
      //std::istringstream iss(line);
      //for(std::string token; std::getline(iss,token, ',');){
      //  std::cout << token << ' | ';
      //}
      //std::cout << std::endl;
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        for (const auto& token : tokens) {
            std::cout << token << '|';
        }
        std::cout << std::endl;
    }
}

