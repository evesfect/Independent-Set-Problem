# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# Build type settings
ifeq ($(BUILD),debug)
    CXXFLAGS += -g -O0 -DDEBUG
else
    CXXFLAGS += -O2 -DNDEBUG
endif

# Directory structure
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = tests
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Main executable name
TARGET = $(BIN_DIR)/independent_set

# Test executable name
TEST_TARGET = $(BIN_DIR)/run_tests

# Header files
INCLUDES = -I$(INC_DIR)

# Output file for test results
OUTPUT_FILE ?= testresult.txt
OUTPUT_FLAG = $(if $(OUTPUT_TO_FILE),> $(OUTPUT_FILE),)

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $(OBJS) -o $@

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Run the program with default test cases
run: $(TARGET)
	@echo "Running program with default test cases..."
	@./$(TARGET) $(OUTPUT_FLAG)

# Run with small test cases
test-small: $(TARGET)
	@echo "Running small test cases..."
	@./$(TARGET) --test-size small $(OUTPUT_FLAG)

# Run with medium test cases
test-medium: $(TARGET)
	@echo "Running medium test cases..."
	@./$(TARGET) --test-size medium $(OUTPUT_FLAG)

# Run with large test cases
test-large: $(TARGET)
	@echo "Running large test cases..."
	@./$(TARGET) --test-size large $(OUTPUT_FLAG)

# Run all tests
test-all: test-small test-medium test-large

# Default number of trials for analysis
TRIALS ?= 100

# Analysis targets
.PHONY: analyze
analyze: $(TARGET)
	./$(TARGET) --analyze 100 5

analyze-custom: $(TARGET)
	./$(TARGET) --analyze $(TRIALS) $(GRAPH_COUNT)

# Save analysis results to file
analyze-to-file: $(TARGET)
	@echo "Running performance analysis and saving to file..."
	@.$(TARGET) --analyze $(TRIALS) OUTPUT_TO_FILE=1

# Build debug version
debug:
	@$(MAKE) BUILD=debug

# Build release version
release:
	@$(MAKE) BUILD=release

# Generate documentation using Doxygen
docs:
	@echo "Generating documentation..."
	@doxygen Doxyfile

# Install the program
install: $(TARGET)
	@echo "Installing program..."
	@install -d $(DESTDIR)/usr/local/bin
	@install $(TARGET) $(DESTDIR)/usr/local/bin

# Format source code using clang-format
format:
	@echo "Formatting source code..."
	@find $(SRC_DIR) $(INC_DIR) -iname *.hpp -o -iname *.cc | xargs clang-format -i

# Memory leak check using valgrind
memcheck: $(TARGET)
	@echo "Checking for memory leaks..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Performance profiling using gprof
profile: CXXFLAGS += -pg
profile: clean $(TARGET)
	@echo "Running program with profiling..."
	@./$(TARGET)
	@gprof $(TARGET) gmon.out > profile.txt

help:
	@echo "analyze        - Run analysis with default parameters (100 trials, 5 graphs per case)"
	@echo "analyze-custom - Run analysis with custom parameters using TRIALS=X GRAPH_COUNT=Y"
# Dependencies
-include $(OBJS:.o=.d)

# Generate dependency files
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cc
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT '$(BUILD_DIR)/$*.o' $< > $@

# Directory structure
.PHONY: all clean run test-small test-medium test-large test-all debug release docs install format analyze memcheck profile directories