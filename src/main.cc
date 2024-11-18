#include "TestFramework.h"
#include "BacktrackingSolver.h"

void runSpecificTests() {
    BacktrackingSolver solver;
    
    // Test 1: Triangle graph (maximum independent set size should be 1)
    Graph g1(3);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    auto result1 = solver.findMaximumIndependentSet(g1);
    assert(result1.size() == 1);
    assert(solver.validateSolution(g1, result1));
    
    // Test 2: Square graph (maximum independent set size should be 2)
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 0);
    auto result2 = solver.findMaximumIndependentSet(g2);
    assert(result2.size() == 2);
    assert(solver.validateSolution(g2, result2));
    
    // Test 3: Star graph (maximum independent set size should be n-1)
    int n = 6;
    Graph g3(n);
    for (int i = 1; i < n; i++) {
        g3.addEdge(0, i);
    }
    auto result3 = solver.findMaximumIndependentSet(g3);
    assert(result3.size() == static_cast<size_t>(n-1));
    assert(solver.validateSolution(g3, result3));
    
    // Test 4: Empty graph (maximum independent set size should be n)
    Graph g4(5);
    auto result4 = solver.findMaximumIndependentSet(g4);
    assert(result4.size() == 5);
    assert(solver.validateSolution(g4, result4));
    
    std::cout << "All specific tests passed successfully!\n";
}

int main() {
    TestFramework framework;
    BacktrackingSolver solver;
    
    try {
        framework.runTests(&solver);
    } catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}