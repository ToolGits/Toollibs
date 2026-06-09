CXX = g++

MINGW = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# =========================
# ARCH DETECTION
# =========================
ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)
BUILD_DIR_WIN = bin/windows_x86_64

# =========================
# SOURCES (CORE FRAMEWORK)
# =========================
CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = $(CORE_SRC) $(MATH_SRC) $(GRAPHICS_SRC) $(PLUGIN_SRC)

# =========================
# TOOLS (LINUX)
# =========================
CPU_SRC = platform/linux/cpu.cpp platform/linux/cpu_info.cpp
GPU_SRC = platform/linux/gpu.cpp platform/linux/gpu_info.cpp

# =========================
# TOOLS (ANDROID)
# =========================
BATTERY_SRC = platform/android/battery.cpp platform/android/battery_info.cpp

# =========================
# POP PLUGIN TOOL
# =========================
POP_SRC = plugins/POP/plugin.cpp plugins/POP/pop_main.cpp

# =========================
# TARGETS (LINUX)
# =========================
MAIN_TARGET = $(BUILD_DIR)/mainlogger
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info
POP_TARGET = $(BUILD_DIR)/pop
BATTERY_TARGET = $(BUILD_DIR)/battery_info

# =========================
# TARGETS (WINDOWS)
# =========================
MAIN_TARGET_WIN = $(BUILD_DIR_WIN)/mainlogger.exe
POP_TARGET_WIN = $(BUILD_DIR_WIN)/pop.exe

# =========================
# PREPARE
# =========================
prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR_WIN)

# =========================
# LINUX BUILD CORE
# =========================
mainlogger: prepare $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET)

# =========================
# LINUX TOOLS
# =========================
tools: prepare
	@echo "Building Linux tools..."

	$(CXX) $(CXXFLAGS) $(CPU_SRC) -o $(CPU_TARGET)
	$(CXX) $(CXXFLAGS) $(GPU_SRC) -o $(GPU_TARGET)
	$(CXX) $(CXXFLAGS) $(BATTERY_SRC) -o $(BATTERY_TARGET)

# =========================
# POP (LINUX)
# =========================
pop: prepare
	@echo "Building POP (Linux)..."
	$(CXX) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET)

# =========================
# WINDOWS BUILD CORE
# =========================
windows: prepare
	@echo "Building Windows binaries..."

	$(MINGW) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET_WIN)

# =========================
# POP (WINDOWS)
# =========================
pop_windows: prepare
	@echo "Building POP (Windows)..."
	$(MINGW) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET_WIN)

# =========================
# FULL BUILD
# =========================
all: prepare mainlogger tools windows pop pop_windows

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
# DEPLOY
# =========================
deploy: all
	@echo "=================================="
	@echo "Toollibs Deploy Starting..."
	@echo "=================================="
	@./.deploy.sh