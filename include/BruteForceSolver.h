#ifndef BRUTE_FORCE_SOLVER_H
#define BRUTE_FORCE_SOLVER_H

#include "IndependentSetSolver.h"

class BruteForceSolver : public IndependentSetSolver {
public:
    std::vector<int> findMaximumIndependentSet(const Graph& g) override;
    bool hasIndependentSetOfSize(const Graph& g, int k) override;
};

#endif // BRUTE_FORCE_SOLVER_H