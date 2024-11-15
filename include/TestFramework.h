#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include "GraphGenerator.h"
#include "IndependentSetSolver.h"
#include <cassert>

class TestFramework {
private:
    GraphGenerator generator;

public:
    void runTests(IndependentSetSolver* solver);
};

#endif