// BacktrackingSolver.h
#ifndef BACKTRACKING_SOLVER_H
#define BACKTRACKING_SOLVER_H

#include "IndependentSetSolver.h"
#include <set>

class BacktrackingSolver : public IndependentSetSolver {
private:
    std::vector<int> currentBest;  // Store the best solution found
    
    void findLargestSet(const Graph& g, 
                       std::vector<int>& currentSet, 
                       int start);
    
    // Helper method to check if vertex can be added to current set
    bool canAddVertex(const Graph& g, 
                     const std::vector<int>& currentSet, 
                     int vertex) const;

public:
    std::vector<int> findMaximumIndependentSet(const Graph& g) override;
    bool hasIndependentSetOfSize(const Graph& g, int k) override;
};

#endif // BACKTRACKING_SOLVER_H