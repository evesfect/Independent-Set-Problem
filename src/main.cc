#include "TestFramework.h"
#include "BacktrackingSolver.h"
#include "HeuristicSolver.h"
#include "StatisticalAnalyzer.h"
#include <string>

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

void runAnalysis(int numTrials) {
    GraphGenerator generator;
    StatisticalAnalyzer analyzer;
    BacktrackingSolver bruteSolver;
    HeuristicSolver heuristicSolver;
    
    std::vector<int> graphSizes = {10, 15, 20, 25, 30};
    std::vector<double> probabilities = {0.2, 0.4, 0.6};
    std::vector<AnalysisResult> results;
    
    for (int size : graphSizes) {
        for (double prob : probabilities) {
            std::cout << "Analyzing graph of size " << size 
                     << " with edge probability " << prob << "\n";
            
            Graph g = generator.generateRandomGraph(size, prob);
            auto result = analyzer.analyze(&heuristicSolver, &bruteSolver, g, numTrials);
            results.push_back(result);
            
            std::cout << "Performance Metrics:\n"
                      << "  Mean time: " << result.meanTime << " microseconds\n"
                      << "  Confidence interval: [" << result.meanTime - result.confidenceInterval
                      << ", " << result.meanTime + result.confidenceInterval << "]\n"
                      << "  Interval is " << (result.isConfidenceIntervalNarrow ? "narrow" : "too wide") << "\n"
                      << "Quality Metrics:\n"
                      << "  Optimal solution size: " << result.optimalSize << "\n"
                      << "  Mean heuristic size: " << result.meanHeuristicSize << "\n"
                      << "  Approximation ratio: " << result.approximationRatio << "\n"
                      << "  Optimal match rate: " << result.optimalMatchRate << "%\n\n";
        }
    }
    
    analyzer.saveResultsToFile(results, graphSizes, "analysis_results.csv");
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--analyze") {
        int numTrials = (argc > 2) ? std::stoi(argv[2]) : 100;
        runAnalysis(numTrials);
    } else {
        TestFramework framework;
        BacktrackingSolver BruteSolver;
        HeuristicSolver HeurSolver;
        
        try {
            framework.runTests(&BruteSolver);
        } catch (const std::exception& e) {
            std::cerr << "Error during testing: " << e.what() << std::endl;
            return 1;
        }

    }
    return 0;
}