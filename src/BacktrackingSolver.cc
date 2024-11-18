// BacktrackingSolver.cpp
#include "../include/BacktrackingSolver.h"

bool BacktrackingSolver::canAddVertex(const Graph& g, 
                                    const std::vector<int>& currentSet, 
                                    int vertex) const {
    // Check if vertex is adjacent to any vertex in current set
    for (int v : currentSet) {
        if (g.hasEdge(vertex, v)) {
            return false;
        }
    }
    return true;
}

void BacktrackingSolver::findLargestSet(const Graph& g, 
                                      std::vector<int>& currentSet, 
                                      int start) {
    // Update best solution if current set is larger
    if (currentSet.size() > currentBest.size()) {
        currentBest = currentSet;
    }
    
    // Try adding each remaining vertex
    for (int i = start; i < g.getNumVertices(); i++) {
        // Check if vertex i can be added to current set
        if (canAddVertex(g, currentSet, i)) {
            // Add vertex
            currentSet.push_back(i);
            
            // Recurse
            findLargestSet(g, currentSet, i + 1);
            
            // Backtrack
            currentSet.pop_back();
        }
    }
}

std::vector<int> BacktrackingSolver::findMaximumIndependentSet(const Graph& g) {
    // Initialize empty sets
    std::vector<int> currentSet;
    currentBest.clear();
    
    // Start backtracking
    findLargestSet(g, currentSet, 0);
    
    return currentBest;
}

bool BacktrackingSolver::hasIndependentSetOfSize(const Graph& g, int k) {
    // Find maximum independent set
    std::vector<int> maxSet = findMaximumIndependentSet(g);
    
    // Check if its size is at least k
    return maxSet.size() >= static_cast<size_t>(k);
}