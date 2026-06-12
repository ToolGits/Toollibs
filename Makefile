CXX = g++
MINGW = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# ============================================================
# ARCHITECTURE DETECTION
# ============================================================

ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)
BUILD_DIR_WIN = bin/windows_x86_64

# Detect MinGW automatically
HAS_MINGW := $(shell command -v $(MINGW) >/dev/null 2>&1 && echo yes)

# ============================================================
# CORE FRAMEWORK
# ============================================================

CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = \
	$(CORE_SRC) \
	$(MATH_SRC) \
	$(GRAPHICS_SRC) \
	$(PLUGIN_SRC)

# ============================================================
# LINUX TOOLS
# ============================================================

CPU_SRC = \
	platform/linux/cpu.cpp \
	platform/linux/cpu_info.cpp

GPU_SRC = \
	platform/linux/gpu.cpp \
	platform/linux/gpu_info.cpp

# ============================================================
# ANDROID TOOLS
# ============================================================

BATTERY_SRC = \
	platform/android/battery.cpp \
	platform/android/battery_info.cpp

# ============================================================
# POP PLUGIN
# ============================================================

POP_SRC = \
	plugins/POP/plugin.cpp \
	plugins/POP/pop_main.cpp

# ============================================================
# FS EMULATED CMD
# ============================================================

FS_SRC = fs/fs_emucmd.cpp

# ============================================================
# TARGETS (LINUX / ANDROID)
# ============================================================

MAIN_TARGET = $(BUILD_DIR)/mainlogger

FS_TARGET = $(BUILD_DIR)/fs_emucmd
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info
BATTERY_TARGET = $(BUILD_DIR)/battery_info

POP_TARGET = $(BUILD_DIR)/pop

# ============================================================
# TARGETS (WINDOWS)
# ============================================================

FS_TARGET_WIN = $(BUILD_DIR_WIN)/fs_emucmd.exe
MAIN_TARGET_WIN = $(BUILD_DIR_WIN)/mainlogger.exe
POP_TARGET_WIN = $(BUILD_DIR_WIN)/pop.exe

# ============================================================
# PREPARE
# ============================================================

prepare:
	@mkdir -p $(BUILD_DIR)

# ============================================================
# CORE BUILD
# ============================================================

mainlogger: prepare $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET)

# ============================================================
# PLATFORM TOOLS
# ============================================================

cpu_info: prepare
	$(CXX) $(CXXFLAGS) $(CPU_SRC) -o $(CPU_TARGET)

gpu_info: prepare
	$(CXX) $(CXXFLAGS) $(GPU_SRC) -o $(GPU_TARGET)

battery_info: prepare
	$(CXX) $(CXXFLAGS) $(BATTERY_SRC) -o $(BATTERY_TARGET)

tools: cpu_info gpu_info battery_info

# ============================================================
# POP
# ============================================================

pop: prepare
	@echo "Building POP..."
	$(CXX) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET)


# ============================================================
# FS EMULATED CMD Linux
# ============================================================

fs_emucmd: prepare
	$(CXX) $(CXXFLAGS) $(FS_SRC) -o $(FS_TARGET)

# ============================================================
# WINDOWS BUILD
# ============================================================

windows: prepare
ifeq ($(HAS_MINGW),yes)
	@mkdir -p $(BUILD_DIR_WIN)
	@echo "Building Windows binaries..."
	$(MINGW) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET_WIN)
else
	@echo "Toollibs: MinGW not found, skipping Windows build."
endif

# ============================================================
# WINDOWS POP
# ============================================================

pop_windows: prepare
ifeq ($(HAS_MINGW),yes)
	@mkdir -p $(BUILD_DIR_WIN)
	@echo "Building POP (Windows)..."
	$(MINGW) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET_WIN)
else
	@echo "Toollibs: MinGW not found, skipping Windows POP build."
endif


# ============================================================
# WINDOWS FS EMULATED CMD
# ============================================================

fs_emucmd_windows: prepare
ifeq ($(HAS_MINGW),yes)
	@mkdir -p $(BUILD_DIR_WIN)
	$(MINGW) $(CXXFLAGS) $(FS_SRC) -o $(FS_TARGET_WIN)
endif

# ============================================================
# BUILD GROUPS
# ============================================================

linux: mainlogger cpu_info gpu_info pop fs_emucmd

android: battery_info

all: prepare mainlogger tools pop windows pop_windows fs_emucmd fs_emucmd_windows

# ============================================================
# RUN
# ============================================================

run: mainlogger
	@$(MAIN_TARGET)

run_cpu:
	@$(CPU_TARGET)

run_gpu:
	@$(GPU_TARGET)

run_battery:
	@$(BATTERY_TARGET)

run_pop:
	@$(POP_TARGET)

run_fs_emucmd:
	@$(FS_TARGET)

# ============================================================
# INFORMATION
# ============================================================

info:
	@echo "===================================="
	@echo "Toollibs Build Information"
	@echo "===================================="
	@echo "Architecture : $(ARCH)"
	@echo "Build Dir    : $(BUILD_DIR)"
	@echo "Windows Dir  : $(BUILD_DIR_WIN)"
	@echo "MinGW Found  : $(HAS_MINGW)"
	@echo "===================================="

# ============================================================
# CLEAN
# ============================================================

clean:
	rm -rf bin

re: clean all

# ============================================================
# DEPLOY
# ============================================================

deploy: all
	@echo "=================================="
	@echo "Toollibs Deploy Starting..."
	@echo "=================================="
	@./.deploy.sh

# ============================================================
# HELP
# ============================================================

help:
	@echo "Toollibs Build Targets"
	@echo ""
	@echo "make mainlogger"
	@echo "make cpu_info"
	@echo "make gpu_info"
	@echo "make battery_info"
	@echo "make pop"
	@echo "make windows"
	@echo "make pop_windows"
	@echo "make linux"
	@echo "make android"
	@echo "make all"
	@echo "make deploy"
	@echo "make clean"
	@echo "make info"
	@echo "make fs_emucmd"
	@echo "make fs_emucmd_windows"
	@echo "make run_fs_emucmd"