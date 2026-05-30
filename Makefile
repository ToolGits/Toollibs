CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# =========================
# SOURCE FILES
# =========================
CORE_SRC = core/logger.cpp core/mainlogger.cpp platform/platform.cpp
MATH_SRC = math/math.cpp
GRAPHICS_SRC = graphics/graphics.cpp
PLUGIN_SRC = plugins/MathPlugin/plugin.cpp

SRC = $(CORE_SRC) $(MATH_SRC) $(GRAPHICS_SRC) $(PLUGIN_SRC) $(INPUT_SRC)

# =========================
# ARCH DETECTION
# =========================
ARCH := $(shell uname -m)

ifeq ($(ARCH),x86_64)
    PLATFORM = PC (x86_64)
else ifeq ($(ARCH),i386)
    PLATFORM = PC (x86)
else ifeq ($(ARCH),i686)
    PLATFORM = PC (x86)
else ifeq ($(ARCH),aarch64)
    PLATFORM = ARM64 (Android/Linux)
else ifeq ($(ARCH),armv7l)
    PLATFORM = ARM32 (Android/Linux)
else ifeq ($(ARCH),armv6l)
    PLATFORM = ARM32 (Android/Linux)
else
    PLATFORM = Unknown
endif

# =========================
# OUTPUT
# =========================
BUILD_DIR = bin/$(ARCH)
TARGET = mainlogger
OUT = $(BUILD_DIR)/$(TARGET)

# =========================
# DEFAULT BUILD
# =========================
all: prepare build

prepare:
	@mkdir -p $(BUILD_DIR)

build:
	@echo "=================================="
	@echo "Building Toollibs (ForgeLibs v2.0)"
	@echo "Platform: $(PLATFORM)"
	@echo "Arch: $(ARCH)"
	@echo "=================================="
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# =========================
# RUN
# =========================
run: all
	@echo "Running Toollibs..."
	@$(OUT)

# =========================
# CLEAN
# =========================
clean:
	rm -rf bin

re: clean all

# =========================
# DEBUG BUILD
# =========================
debug:
	$(CXX) $(CXXFLAGS) -g $(SRC) -o $(OUT)
