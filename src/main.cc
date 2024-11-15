#include "TestFramework.h"
#include "BruteForceSolver.h"

int main() {
    TestFramework framework;
    BruteForceSolver solver;
    
    try {
        framework.runTests(&solver);
    } catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}