CXX = g++
	
MINGW = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# =========================
# ARCH DETECTION
# =========================
ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)
BUILD_DIR_WIN = bin/windows_$(ARCH)

# =========================
# SOURCES (CORE FRAMEWORK)
# =========================
CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = $(CORE_SRC) $(MATH_SRC) $(GRAPHICS_SRC) $(PLUGIN_SRC)

# =========================
# LINUX-ONLY TOOLS
# =========================
CPU_SRC = platform/linux/cpu.cpp platform/linux/cpu_info.cpp
GPU_SRC = platform/linux/gpu.cpp platform/linux/gpu_info.cpp

# =========================
# TARGETS (LINUX)
# =========================
MAIN_TARGET = $(BUILD_DIR)/mainlogger
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info

# =========================
# TARGETS (WINDOWS)
# =========================
MAIN_TARGET_WIN = $(BUILD_DIR_WIN)/mainlogger.exe

# =========================
# PREPARE
# =========================
prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR_WIN)

# =========================
# LINUX BUILD (CORE)
# =========================
mainlogger: prepare $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET)

# =========================
# LINUX TOOLS ONLY
# =========================
tools: prepare
	@echo "Building Linux-only tools (cpu_info, gpu_info)..."

	$(CXX) $(CXXFLAGS) $(CPU_SRC) -o $(CPU_TARGET)
	$(CXX) $(CXXFLAGS) $(GPU_SRC) -o $(GPU_TARGET)

# =========================
# WINDOWS BUILD (MAIN ONLY)
# =========================
windows: prepare
	@echo "Building Windows binaries ($(ARCH))..."

	$(MINGW) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET_WIN)

# =========================
# FULL BUILD
# =========================
all: prepare mainlogger tools windows

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

# =========================
# DEPLOY SYSTEM
# =========================
deploy: all
	@echo "=================================="
	@echo "Toollibs Deploy Starting..."
	@echo "=================================="
	@./.deploy.sh
