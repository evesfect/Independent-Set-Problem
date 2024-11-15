#include "../include/Graph.h"

Graph::Graph(int n) : numVertices(n) {
    adjacencyMatrix.resize(n, std::vector<bool>(n, false));
}

void Graph::addEdge(int v1, int v2) {
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        adjacencyMatrix[v1][v2] = true;
        adjacencyMatrix[v2][v1] = true;
    }
}

bool Graph::hasEdge(int v1, int v2) const {
    return adjacencyMatrix[v1][v2];
}

int Graph::getNumVertices() const {
    return numVertices;
}

bool Graph::isIndependentSet(const std::vector<int>& vertices) const {
    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t j = i + 1; j < vertices.size(); j++) {
            if (hasEdge(vertices[i], vertices[j])) {
                return false;
            }
        }
    }
    return true;
}

void Graph::print() const {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            std::cout << (adjacencyMatrix[i][j] ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
}