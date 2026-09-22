CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -O2
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/HotelManagementSystem

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

ifeq ($(OS),Windows_NT)
    TARGET := $(BUILD_DIR)/HotelManagementSystem.exe
    RM := del /Q
else
    RM := rm -f
endif

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(TARGET)

clean:
	$(RM) $(BUILD_DIR)/*.o $(TARGET)
