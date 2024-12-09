#include "../include/StatisticalAnalyzer.h"
#include <fstream>
#include <numeric>

double StatisticalAnalyzer::calculateMean() const {
    double sum = std::accumulate(runTimes.begin(), runTimes.end(), 0.0);
    return sum / runTimes.size();
}

double StatisticalAnalyzer::calculateStandardDeviation(double mean) const {
    double squareSum = 0.0;
    for (double time : runTimes) {
        squareSum += (time - mean) * (time - mean);
    }
    return std::sqrt(squareSum / (runTimes.size() - 1));
}

double StatisticalAnalyzer::calculateConfidenceInterval(double stdDev, size_t n) const {
    return Z_SCORE_90 * stdDev / std::sqrt(n);
}

bool StatisticalAnalyzer::isIntervalNarrow(double mean, double interval) const {
    return (interval / mean) < NARROW_INTERVAL_RATIO;
}

AnalysisResult StatisticalAnalyzer::analyze(IndependentSetSolver* heuristicSolver,
                                          IndependentSetSolver* bruteSolver,
                                          const Graph& graph,
                                          int numTrials) {
    runTimes.clear();
    solutionSizes.clear();

    // Get optimal solution
    auto optimalSolution = bruteSolver->findMaximumIndependentSet(graph);
    optimalSolutionSize = optimalSolution.size();

    int optimalMatches = 0;
    double totalHeuristicSize = 0;
    
    // Run heuristic multiple times
    for (int i = 0; i < numTrials; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto solution = heuristicSolver->findMaximumIndependentSet(graph);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        runTimes.push_back(duration.count());
        
        size_t heuristicSize = solution.size();
        totalHeuristicSize += heuristicSize;
        if (heuristicSize == optimalSolutionSize) {
            optimalMatches++;
        }
    }

    double meanHeuristicSize = totalHeuristicSize / numTrials;
    double mean = calculateMean();
    double stdDev = calculateStandardDeviation(mean);
    double confInterval = calculateConfidenceInterval(stdDev, numTrials);

    return {
        mean,
        stdDev,
        confInterval,
        isIntervalNarrow(mean, confInterval),
        optimalSolutionSize,
        meanHeuristicSize,
        meanHeuristicSize / optimalSolutionSize,
        static_cast<double>(optimalMatches) / numTrials
    };
}

void StatisticalAnalyzer::saveResultsToFile(
    const std::vector<AnalysisResult>& results,
    const std::vector<int>& graphSizes,
    const std::string& filename) {
    
    std::ofstream file(filename);
    file << "GraphSize,MeanTime,StdDev,ConfInterval,IsNarrowInterval,"
         << "OptimalSize,MeanHeuristicSize,ApproximationRatio,OptimalMatchRate\n";
    
    for (size_t i = 0; i < results.size(); i++) {
        file << graphSizes[i] << ","
             << results[i].meanTime << ","
             << results[i].standardDeviation << ","
             << results[i].confidenceInterval << ","
             << results[i].isConfidenceIntervalNarrow << ","
             << results[i].optimalSize << ","
             << results[i].meanHeuristicSize << ","
             << results[i].approximationRatio << ","
             << results[i].optimalMatchRate << "\n";
    }
}