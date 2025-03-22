#include <string>
#include <fstream>
#include <iostream>
#include "Graph.h"
#include <sstream>
#include "csvparsing.h"
#include <vector>
#include <ranges>
#include <algorithm>
#include <cctype>

// Função para remover espaços em branco do início e do fim de uma string.
std::string trim(const std::string &s) {
    const std::string whitespace = " \t\n\r";
    size_t start = s.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return ""; // A string só contém espaços em branco.
    size_t end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}

Graph<int> graph;

std::vector<std::string> split(std::string &s, const char &delimiter) {
    std::vector<std::string> values;
    size_t pos = 0;
    std::string value;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        value = s.substr(0, pos);
        // Aplica trim ao valor extraído
        values.push_back(trim(value));
        s.erase(0, pos + 1);
    }
    values.push_back(trim(s));
    return values;
}

void csvLocationParsing(const std::string &filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }
    std::string line;
    // Ignora o header
    std::getline(input, line);
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 2) {
            std::cerr << "Invalid line: " << line << std::endl;
            continue;
        }
        std::string location = tokens[0];
        int id = std::stoi(tokens[1]);
        std::string code = (tokens.size() > 2) ? tokens[2] : "";
        bool parking = (tokens.size() > 3) && (tokens[3] == "1");
        std::cout << "Location: " << location << ", Id: " << id
                  << ", Code: " << code << ", Parking: " << parking << std::endl;
        // troquei a ordem para que 'code' was passed antes de 'location'**
        graph.addVertex(id, code, location, parking);
    }
}

void csvDistancesParsing(const std::string &filepath) {
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }
    std::string line;
    // Lê o cabeçalho
    std::getline(input, line);
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3) {
            std::cerr << "Invalid line: " << line << std::endl;
            continue;
        }
        std::string code1 = tokens[0];
        std::string code2 = tokens[1];
        double driving, walking;
        try {
            if (tokens[2] == "X")
                driving = INF;
            else
                driving = std::stod(tokens[2]);
            if (tokens.size() > 3) {
                if (tokens[3] == "X")
                    walking = INF;
                else
                    walking = std::stod(tokens[3]);
            } else {
                walking = driving;
            }
        } catch (const std::exception &e) {
            std::cerr << "Error converting numbers in line: " << line << std::endl;
            continue;
        }
        std::cout << "Code1: " << code1 << ", Code2: " << code2
                  << ", Driving: " << driving << ", Walking: " << walking << std::endl;
        graph.addEdge(code1, code2, driving, walking);
    }
}
