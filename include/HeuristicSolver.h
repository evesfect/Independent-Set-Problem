#ifndef HEURISTIC_SOLVER_H
#define HEURISTIC_SOLVER_H

#include "IndependentSetSolver.h"
#include <map>

class HeuristicSolver : public IndependentSetSolver {
private:
    // Helper method to get vertex degrees
    std::map<int, int> getVertexDegrees(const Graph& g, const std::vector<bool>& removed) const;
    
    // Helper method to find vertex with minimum degree
    int findMinDegreeVertex(const std::map<int, int>& degrees) const;
    
    // Helper method to remove a vertex and its neighbors
    void removeVertexAndNeighbors(const Graph& g, int vertex, std::vector<bool>& removed);

public:
    std::vector<int> findMaximumIndependentSet(const Graph& g) override;
    bool hasIndependentSetOfSize(const Graph& g, int k) override;
};

#endif // HEURISTIC_SOLVER_H