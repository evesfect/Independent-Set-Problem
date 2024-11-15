#ifndef INDEPENDENT_SET_SOLVER_H
#define INDEPENDENT_SET_SOLVER_H

#include "Graph.h"

class IndependentSetSolver {
public:
    virtual std::vector<int> findMaximumIndependentSet(const Graph& g) = 0;
    virtual bool hasIndependentSetOfSize(const Graph& g, int k) = 0;
    virtual ~IndependentSetSolver() = default;

    bool validateSolution(const Graph& g, const std::vector<int>& solution) {
        return g.isIndependentSet(solution);
    }
};

#endif