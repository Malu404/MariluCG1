# Makefile for SDL project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -O2 -march=native -I"E:/downloads ssd/SDL2/include" -D_REENTRANT

# Linker flags
LDFLAGS = -L"E:/downloads ssd/SDL2/lib" -lSDL2 -lSDL2_image

# Source files
SRCS = main.cpp engine/shapes/textura.cpp

# Output executable
TARGET = cg1

# Default target
all: $(TARGET)

run: $(TARGET)
    ./$(TARGET)

# Build the target
$(TARGET): $(SRCS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up build files
clean:
    rm -f $(TARGET)

# Phony targets
.PHONY: all clean