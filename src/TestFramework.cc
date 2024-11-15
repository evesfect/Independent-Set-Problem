#include "../include/TestFramework.h"

void TestFramework::runTests(IndependentSetSolver* solver) {
    std::cout << "Running tests...\n\n";

    // Test on predefined cases
    auto testCases = generator.generateTestCases();
    for (size_t i = 0; i < testCases.size(); i++) {
        std::cout << "Test case " << i + 1 << ":\n";
        testCases[i].print();
        
        auto solution = solver->findMaximumIndependentSet(testCases[i]);
        std::cout << "Maximum Independent Set size: " << solution.size() << "\n";
        std::cout << "Vertices in set: ";
        for (int vertex : solution) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        
        assert(solver->validateSolution(testCases[i], solution));
        std::cout << "Solution validated successfully\n\n";
    }

    // Test on random instances
    for (int size : {5, 10, 15}) {
        std::cout << "Testing random graph of size " << size << ":\n";
        Graph g = generator.generateRandomGraph(size, 0.3);
        g.print();
        
        auto solution = solver->findMaximumIndependentSet(g);
        std::cout << "Maximum Independent Set size: " << solution.size() << "\n";
        std::cout << "Vertices in set: ";
        for (int vertex : solution) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        
        assert(solver->validateSolution(g, solution));
        std::cout << "Solution validated successfully\n\n";
    }
}