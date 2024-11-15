# Compiler
CXX = g++

# Debug flag (default is off, set DEBUG=1 to enable debugging)
DEBUG ?= 0

# Compiler flags
CXXFLAGS = -Wall -Werror -Wextra -Wshadow -Wsign-conversion -Ih -std=c++17
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g -O0  # Add debugging symbols and disable optimizations
endif

# Directories
SRC_DIR 		= src
BIN_DIR 		= bin
GTEST_DIR 		= googletest/lib

# Find all .cpp files in the src/ directory
SRCS            = $(filter-out %_test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_SRCS       = $(wildcard $(SRC_DIR)/*_test.cpp)

# Generate .o filenames in obj/ directory for each .cpp
OBJS            = $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(SRCS))
TEST_OBJS       = $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(TEST_SRCS))

# Executable names
EXECUTABLE      = $(BIN_DIR)/gdsii_parser
TEST_EXECUTABLE = $(BIN_DIR)/gdsii_parser_unit_tests

# GoogleTest library paths and flags
GTEST_LIB       = $(GTEST_DIR)

# Default target (build both and run tests)
all: $(EXECUTABLE) $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Build the main executable
$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build the test executable
$(TEST_EXECUTABLE): $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(GTEST_LIB) -lgtest -lgtest_main -pthread

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o

# Trigger CMake configuration and build
build:
	cmake -S . -B build
	cmake --build build

.PHONY: all clean build