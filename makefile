# Compiler and linker settings
CXX      := g++

# Build type: Release or Debug (default is Release)
BUILD_TYPE ?= Release

ifeq ($(BUILD_TYPE), Debug)
    CXXFLAGS := -std=c++17 -g -O0 -Iinclude
    DEFINES  := -DDEBUG
else
    CXXFLAGS := -std=c++17 -O2 -DNDEBUG -Iinclude
    DEFINES  :=
endif

LDFLAGS  := -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

BUILD_DIR := bin
OBJ_DIR   := obj
SRC_DIR   := src
INC_DIR   := include

# Automatically find all .cpp files in the src directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Generate object files from source files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Extract program names from source files (without extensions)
PROGRAMS := $(patsubst $(SRC_DIR)/%.cpp, %, $(SRCS))

# Default target
.PHONY: all
all: $(PROGRAMS)

# Rule to build each program
$(PROGRAMS): %: $(BUILD_DIR)/%

# Link object files to create the binary
$(BUILD_DIR)/%: $(OBJ_DIR)/%.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEFINES) -o $@ $< $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o $@

# Create build and object directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: debug
debug:
	$(MAKE) BUILD_TYPE=Debug

.PHONY: release
release:
	$(MAKE) BUILD_TYPE=Release

.PHONY: ex
ex:
	@$(eval FILE := $(filter-out $@,$(MAKECMDGOALS)))
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make ex filename [BUILD_TYPE=Debug/Release]"; \
		exit 1; \
	fi
	@$(eval BASENAME := $(basename $(notdir $(FILE))))
	@echo "Compiling and executing '$(BASENAME)'..."
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEFINES) -o $(BUILD_DIR)/$(BASENAME) $(SRC_DIR)/$(BASENAME).cpp $(LDFLAGS)
	@echo "Running '$(BASENAME)':"
	@./$(BUILD_DIR)/$(BASENAME)

# Clean up generated files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)

# Run a specific program
.PHONY: run
run:
	@echo "Please specify the program to run, e.g., 'make run PROGRAM=program1 [BUILD_TYPE=Debug/Release]'"
	@false

.PHONY: run-%
run-%: $(BUILD_DIR)/%
	@echo "Running $*:"
	@./$(BUILD_DIR)/$*

# Rebuild the project from scratch
.PHONY: rebuild
rebuild: clean all
