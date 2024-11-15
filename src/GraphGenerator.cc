#include "../include/GraphGenerator.h"

GraphGenerator::GraphGenerator() 
    : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

Graph GraphGenerator::generateRandomGraph(int n, double p) {
    Graph g(n);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist(rng) < p) {
                g.addEdge(i, j);
            }
        }
    }
    return g;
}

std::vector<Graph> GraphGenerator::generateTestCases() {
    std::vector<Graph> testCases;
    
    // Triangle graph (Graph 1)
    Graph triangle(3);
    triangle.addEdge(0, 1);
    triangle.addEdge(1, 2);
    triangle.addEdge(2, 0);
    testCases.push_back(triangle);

    // Star graph with 6 vertices (Graph 2)
    Graph star(6);
    for (int i = 1; i < 6; i++) {
        star.addEdge(0, i);
    }
    testCases.push_back(star);

    // Square graph (Graph 3)
    Graph square(4);
    square.addEdge(0, 1);
    square.addEdge(1, 2);
    square.addEdge(2, 3);
    square.addEdge(3, 0);
    testCases.push_back(square);

    return testCases;
}