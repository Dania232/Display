# Directories
SRC_DIR := .
BIN_DIR := ./bin

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Pattern rule: compile any .cpp in SRC_DIR into BIN_DIR
# $< = source file, $@ = target file
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	g++ $< -o $@

# Default target: build all cpp files
# Finds all .cpp files in SRC_DIR, creates corresponding targets in BIN_DIR
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SOURCES))

all: $(TARGETS)

# Optional: clean all binaries
clean:
	rm -f $(BIN_DIR)/*
