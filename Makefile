CXX = g++

MINGW = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

=========================

ARCH DETECTION

=========================

ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)
BUILD_DIR_WIN = bin/windows_x86_64

=========================

TOOLCHAIN DETECTION

=========================

HAS_MINGW := $(shell command -v $(MINGW) >/dev/null 2>&1 && echo yes)

=========================

SOURCES (CORE FRAMEWORK)

=========================

CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = $(CORE_SRC) $(MATH_SRC) $(GRAPHICS_SRC) $(PLUGIN_SRC)

=========================

TOOLS (LINUX)

=========================

CPU_SRC = platform/linux/cpu.cpp platform/linux/cpu_info.cpp
GPU_SRC = platform/linux/gpu.cpp platform/linux/gpu_info.cpp

=========================

TOOLS (ANDROID)

=========================

BATTERY_SRC = platform/android/battery.cpp platform/android/battery_info.cpp

=========================

POP PLUGIN TOOL

=========================

POP_SRC = plugins/POP/plugin.cpp plugins/POP/pop_main.cpp

=========================

TARGETS (LINUX / ANDROID)

=========================

MAIN_TARGET = $(BUILD_DIR)/mainlogger
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info
BATTERY_TARGET = $(BUILD_DIR)/battery_info
POP_TARGET = $(BUILD_DIR)/pop

=========================

TARGETS (WINDOWS)

=========================

MAIN_TARGET_WIN = $(BUILD_DIR_WIN)/mainlogger.exe
POP_TARGET_WIN = $(BUILD_DIR_WIN)/pop.exe

=========================

PREPARE

=========================

prepare:
@mkdir -p $(BUILD_DIR)

ifeq ($(HAS_MINGW),yes)
@mkdir -p $(BUILD_DIR_WIN)
endif

=========================

LINUX BUILD CORE

=========================

mainlogger: prepare $(SRC)
$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET)

=========================

PLATFORM TOOLS

=========================

tools: prepare
@echo "Building platform tools..."

$(CXX) $(CXXFLAGS) $(CPU_SRC) -o $(CPU_TARGET)
$(CXX) $(CXXFLAGS) $(GPU_SRC) -o $(GPU_TARGET)
$(CXX) $(CXXFLAGS) $(BATTERY_SRC) -o $(BATTERY_TARGET)

=========================

POP (LINUX)

=========================

pop: prepare
@echo "Building POP (Linux)..."
$(CXX) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET)

=========================

WINDOWS BUILD CORE

=========================

windows: prepare
ifeq ($(HAS_MINGW),yes)
@echo "Building Windows binaries..."
$(MINGW) $(CXXFLAGS) $(SRC) -o $(MAIN_TARGET_WIN)
else
@echo "MinGW not found. Skipping Windows build."
endif

=========================

POP (WINDOWS)

=========================

pop_windows: prepare
ifeq ($(HAS_MINGW),yes)
@echo "Building POP (Windows)..."
$(MINGW) $(CXXFLAGS) $(POP_SRC) -o $(POP_TARGET_WIN)
else
@echo "MinGW not found. Skipping Windows POP build."
endif

=========================

FULL BUILD

=========================

all: prepare mainlogger tools pop

ifeq ($(HAS_MINGW),yes)
all: windows pop_windows
else
$(info Toollibs: MinGW not found, Windows builds disabled)
endif

=========================

RUN

=========================

run: mainlogger
@$(MAIN_TARGET)

=========================

CLEAN

=========================

clean:
rm -rf bin

re: clean all

=========================

DEPLOY

=========================

deploy: all
@echo "=================================="
@echo "Toollibs Deploy Starting..."
@echo "=================================="
@./.deploy.sh