#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph {
private:
    std::vector<std::vector<bool>> adjacencyMatrix;
    int numVertices;

public:
    Graph(int n);
    void addEdge(int v1, int v2);
    bool hasEdge(int v1, int v2) const;
    int getNumVertices() const;
    bool isIndependentSet(const std::vector<int>& vertices) const;
    void print() const;
};

#endif