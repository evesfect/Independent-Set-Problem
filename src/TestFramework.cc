#include "../include/TestFramework.h"
#include <chrono>
#include <fstream>
#include <iomanip>

void TestFramework::runTests(IndependentSetSolver* solver) {
    std::streambuf* old_cout = nullptr;
    std::ofstream file_out;
    
    // Check if output should be redirected to file
    if (getenv("OUTPUT_TO_FILE")) {
        file_out.open("testresult.txt");
        old_cout = std::cout.rdbuf(file_out.rdbuf());
    }

    std::cout << "Running tests...\n\n";

    // Test on predefined cases
    auto testCases = generator.generateTestCases();
    std::cout << "=== Running Predefined Test Cases ===\n";
    for (size_t i = 0; i < testCases.size(); i++) {
        std::cout << "Test case " << i + 1 << ":\n";
        testCases[i].print();
        
        auto start = std::chrono::high_resolution_clock::now();
        auto solution = solver->findMaximumIndependentSet(testCases[i]);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Maximum Independent Set size: " << solution.size() << "\n";
        std::cout << "Vertices in set: ";
        for (int vertex : solution) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        
        assert(solver->validateSolution(testCases[i], solution));
        std::cout << "Solution validated successfully\n";
        std::cout << "Runtime: " << duration.count() << " microseconds\n\n";
    }

    // Test on random instances
    std::cout << "=== Running Random Graph Test Cases ===\n";
    std::vector<std::pair<int, double>> configurations = {
        {5, 0.3}, {5, 0.5}, {5, 0.7},
        {10, 0.2}, {10, 0.4}, {10, 0.6},
        {15, 0.2}, {15, 0.4}, {15, 0.6},
        {20, 0.2}, {20, 0.3}, {20, 0.4},
        {25, 0.2}, {25, 0.3}, {25, 0.4}
    };

    double totalTime = 0.0;
    for (size_t i = 0; i < configurations.size(); i++) {
        int size = configurations[i].first;
        double probability = configurations[i].second;
        
        std::cout << "\nRandom Test " << i + 1 << ":\n";
        std::cout << "Size: " << size << ", Edge Probability: " << probability << "\n";
        
        Graph g = generator.generateRandomGraph(size, probability);
        g.print();
        
        auto start = std::chrono::high_resolution_clock::now();
        auto solution = solver->findMaximumIndependentSet(g);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        totalTime += duration.count();
        
        std::cout << "Maximum Independent Set size: " << solution.size() << "\n";
        std::cout << "Vertices in set: ";
        for (int vertex : solution) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        
        assert(solver->validateSolution(g, solution));
        std::cout << "Solution validated successfully\n";
        std::cout << "Runtime: " << duration.count() << " microseconds\n";
    }
    
    std::cout << "\n=== Test Summary ===\n";
    std::cout << "Total random tests runtime: " << totalTime << " microseconds\n";
    std::cout << "Average runtime per test: " << totalTime / configurations.size() << " microseconds\n";

    // Restore original cout if it was redirected
    if (old_cout) {
        std::cout.rdbuf(old_cout);
    }
}