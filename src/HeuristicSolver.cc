#include "../include/HeuristicSolver.h"
#include <limits>

std::map<int, int> HeuristicSolver::getVertexDegrees(const Graph& g, const std::vector<bool>& removed) const {
    std::map<int, int> degrees;
    int n = g.getNumVertices();
    
    // Calculate degrees only for non-removed vertices
    for (int i = 0; i < n; i++) {
        if (!removed[i]) {
            int degree = 0;
            for (int j = 0; j < n; j++) {
                if (!removed[j] && g.hasEdge(i, j)) {
                    degree++;
                }
            }
            degrees[i] = degree;
        }
    }
    return degrees;
}

int HeuristicSolver::findMinDegreeVertex(const std::map<int, int>& degrees) const {
    int minVertex = -1;
    int minDegree = std::numeric_limits<int>::max();
    
    for (const auto& pair : degrees) {
        if (pair.second < minDegree) {
            minDegree = pair.second;
            minVertex = pair.first;
        }
    }
    return minVertex;
}

void HeuristicSolver::removeVertexAndNeighbors(const Graph& g, int vertex, std::vector<bool>& removed) {
    removed[vertex] = true;
    for (int i = 0; i < g.getNumVertices(); i++) {
        if (g.hasEdge(vertex, i)) {
            removed[i] = true;
        }
    }
}

std::vector<int> HeuristicSolver::findMaximumIndependentSet(const Graph& g) {
    std::vector<int> solution;
    std::vector<bool> removed(g.getNumVertices(), false);
    
    while (true) {
        // Get current degrees of remaining vertices
        auto degrees = getVertexDegrees(g, removed);
        
        // If no vertices left, break
        if (degrees.empty()) {
            break;
        }
        
        // Find vertex with minimum degree
        int vertex = findMinDegreeVertex(degrees);
        
        // Add to solution
        solution.push_back(vertex);
        
        // Remove vertex and its neighbors
        removeVertexAndNeighbors(g, vertex, removed);
    }
    
    return solution;
}

bool HeuristicSolver::hasIndependentSetOfSize(const Graph& g, int k) {
    // Find a solution using the heuristic
    std::vector<int> solution = findMaximumIndependentSet(g);
    
    // Check if solution size is at least k
    return solution.size() >= static_cast<size_t>(k);
}