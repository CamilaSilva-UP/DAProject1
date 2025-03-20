#include <string>
#include <fstream>
#include <iostream>


//for testing purposes, make it print the values, DON'T CREATE A GRAPH UNTIL IT IS TESTED PROPERLY
//use files in csv examples for testing

//Parses Locations.csv and creates the vertices
void csvLocationParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    for (std::string line; std::getline(input,line);){
      std::cout << line <<std::endl;
      //divides the line in tokens separed by ','
      std::istringstream iss(line);
      for(std::string token; std::getline(iss,token, ',');){
        std::cout << token << ' | ';
      }
      std::cout << std::endl;
    }

}

//Parses Distances.csv and creates the edges
void csvDistancesParsing(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }
    for(std::string line; std::getline(input,line);){
      std::cout << line <<std::endl;
      std::istringstream iss(line);
      for(std::string token; std::getline(iss,token, ',');){
        std::cout << token << ' | ';
      }
      std::cout << std::endl;
    }

}

