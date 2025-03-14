#include <iostream>
#include <ostream>
#include "Graph.h"

int main() {
    std::cout << "Testing Graph functionality" << std::endl;
    auto G = new Graph<int>();
    G->addVertex(1); G->addVertex(2); G->addVertex(3);
    for (auto v : G->getVertexSet()) {
        std::cout << v->getInfo() << " ";
    }
    return  0;
}
