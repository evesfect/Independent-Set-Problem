#ifndef STATISTICAL_ANALYZER_H
#define STATISTICAL_ANALYZER_H

#include "Graph.h"
#include "IndependentSetSolver.h"
#include <vector>
#include <chrono>
#include <cmath>

struct AnalysisResult {
    double meanTime;
    double standardDeviation;
    double confidenceInterval;
    bool isConfidenceIntervalNarrow;
    
    size_t optimalSize;
    double meanHeuristicSize;
    double approximationRatio;
    double optimalMatchRate;
};

class StatisticalAnalyzer {
private:
    static constexpr double Z_SCORE_90 = 1.96;
    static constexpr double NARROW_INTERVAL_RATIO = 0.1;
    
    std::vector<double> runTimes;
    std::vector<size_t> solutionSizes;
    size_t optimalSolutionSize;

    double calculateMean() const;
    double calculateStandardDeviation(double mean) const;
    double calculateConfidenceInterval(double stdDev, size_t n) const;
    bool isIntervalNarrow(double mean, double interval) const;

public:
    AnalysisResult analyze(IndependentSetSolver* heuristicSolver,
                          IndependentSetSolver* bruteSolver,
                          const Graph& graph,
                          int numTrials);

    static void saveResultsToFile(const std::vector<AnalysisResult>& results,
                                const std::vector<int>& graphSizes,
                                const std::string& filename);
};

#endif