#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <random>
#include <chrono>
#include "Graph.h"

class GraphGenerator {
private:
    std::mt19937 rng;

public:
    GraphGenerator();
    Graph generateRandomGraph(int n, double p);
    std::vector<Graph> generateTestCases();
};

#endif