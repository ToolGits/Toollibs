CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# =========================
# ARCH DETECTION
# =========================
ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)

# =========================
# SOURCES
# =========================
CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = $(CORE_SRC) $(MATH_SRC) $(GRAPHICS_SRC) $(PLUGIN_SRC)

CPU_SRC = platform/linux/cpu.cpp platform/linux/cpu_info.cpp
GPU_SRC = platform/linux/gpu.cpp platform/linux/gpu_info.cpp

# =========================
# TARGETS
# =========================
MAIN_TARGET = $(BUILD_DIR)/mainlogger
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info

# =========================
# PREPARE
# =========================
prepare:
	@mkdir -p $(BUILD_DIR)

# =========================
# MAIN BUILD
# =========================
mainlogger: prepare
	$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET)

# =========================
# TOOLS BUILD
# =========================
tools: prepare
	@echo "Building CPU & GPU tools..."
	$(CXX) $(CXXFLAGS) $(CPU_SRC) -o $(CPU_TARGET)
	$(CXX) $(CXXFLAGS) $(GPU_SRC) -o $(GPU_TARGET)

# =========================
# FULL BUILD
# =========================
all: mainlogger tools

# =========================
# RUN
# =========================
run: mainlogger
	@$(MAIN_TARGET)

# =========================
# CLEAN
# =========================
clean:
	rm -rf bin

re: clean all
