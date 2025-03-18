//this function should receive a .csv file, and parse it
//for testing purposes, make it print the values, DON'T CREATE A GRAPH UNTIL IT IS TESTED PROPERLY

#include <string>
#include <fstream>
#include <iostream>

void csvParsing(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Error opening file " << filepath << std::endl;
    }


}
