# Independent Set Problem Solver

## Overview

This project implements algorithms for solving the Maximum Independent Set problem in graphs.

## Features

### Solvers

- Backtracking Solver: An implementation using recursive backtracking

### Test Framework

- Predefined test cases including:
  - Triangle graphs
  - Star graphs
  - Square graphs
- Random graph generation with configurable parameters
- Automated validation of solutions

### Build System Features

The project uses a comprehensive Makefile system with the following capabilities:

#### Basic Operations

- `make`: Build the project
- `make clean`: Remove all built files
- `make run`: Execute with default test cases

#### Testing

- `make test-small`: Run small test cases
- `make test-medium`: Run medium test cases
- `make test-large`: Run large test cases
- `make test-all`: Run all test sizes
- `make test-{size} OUTPUT_TO_FILE`: Save test results to a file

#### Analysis

- `make analyze`: Run analysis with default parameters (100 trials, 5 graphs per case)
- `make analyze-custom`: Run analysis with custom parameters using TRIALS=X GRAPH_COUNT=Y


#### Development Tools

- `make debug`: Build with debugging symbols
- `make release`: Build optimized release version
- `make docs`: Generate documentation using Doxygen
- `make format`: Format code using clang-format
- `make memcheck`: Check for memory leaks using valgrind
- `make profile`: Generate performance profile using gprof

#### Installation

- `make install`: Install the program to system

### Prerequisites

- C++17 compatible compiler
- Make build system
- Optional tools:
  - Doxygen (for documentation)
  - clang-format (for code formatting)
  - cppcheck (for static analysis)
  - valgrind (for memory checking)
  - gprof (for profiling)
