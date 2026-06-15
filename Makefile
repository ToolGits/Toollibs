CXX = g++
MINGW = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# ============================================================
# ARCHITECTURE DETECTION
# ============================================================

ARCH := $(shell uname -m)

BUILD_DIR = bin/$(ARCH)
BUILD_DIR_WIN = bin/windows_x86_64
BUILD_DIR_ANDROID = bin/android

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

FS_EMUCMD_SRC = \
    fs/fs.cpp \
    fs/fs_emucmd.cpp

FS_EMUCMD_SRC_WIN = \
    $(FS_EMUCMD_SRC) \
    $(REPLXX_SRC) \
    fs/replxx/windows.cxx

REPLXX_SRC = \
    fs/replxx/replxx.cxx \
    fs/replxx/replxx_impl.cxx \
    fs/replxx/history.cxx \
    fs/replxx/prompt.cxx \
    fs/replxx/terminal.cxx \
    fs/replxx/conversion.cxx \
    fs/replxx/escape.cxx \
    fs/replxx/util.cxx \
    fs/replxx/wcwidth.cpp \
    fs/replxx/ConvertUTF.cpp

# =========================
# AUDIO SOURCES
# =========================

AUDIO_SRC = audio/audio.cpp
AUDIO_PLAYER_SRC = audio/audio_player.cpp
AUDIO_LIBS := $(shell pkg-config --libs sndfile sdl2 SDL2_mixer)
AUDIO_CFLAGS := $(shell pkg-config --cflags sndfile sdl2 SDL2_mixer)

# =========================
# FONT PREVIEW
# =========================

FONT_PREVIEW_SRC = \
 graphics/font_renderer.cpp \
 graphics/font_preview.cpp

FONT_PREVIEW_TARGET = \
 $(BUILD_DIR)/font_preview

FONT_PREVIEW_LIBS = \
 -lfreetype
# ============================================================
# ANDROID NDK CONFIG
# ============================================================

ifneq ($(NDK_VERSION),)

NDK := $(NDK_BASE)/$(NDK_VERSION)

ANDROID_API = 24

CLANGXX = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$(ANDROID_API)-clang++

HAS_NDK = yes

else

HAS_NDK = no

endif

# ============================================================
# TARGETS (LINUX / ANDROID)
# ============================================================

MAIN_TARGET = $(BUILD_DIR)/mainlogger

FONT_PREVIVEW_TARGET = $(BUILD_DIR)/font_preview
FS_TARGET = $(BUILD_DIR)/fs_emucmd
CPU_TARGET = $(BUILD_DIR)/cpu_info
GPU_TARGET = $(BUILD_DIR)/gpu_info
BATTERY_TARGET = $(BUILD_DIR)/battery_info
AUDIO_PLAYER_LINUX_TARGET = $(BUILD_DIR)/audio_player
AUDIO_PLAYER_ANDROID_TARGET = $(BUILD_DIR_ANDROID)/android_audio_player

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
	@mkdir -p $(BUILD_DIR_ANDROID)
	@mkdir -p $(BUILD_DIR_WIN)

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

tools: cpu_info gpu_info battery_info audio_player android_audio_player

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
	$(CXX) $(CXXFLAGS) $(FS_EMUCMD_SRC) $(REPLXX_SRC) -o $(FS_TARGET)

# ============================================================
# AUDIO PLAYER
# ============================================================

audio_player: prepare $(AUDIO_SRC) $(AUDIO_PLAYER_SRC)
	@echo "Building Linux audio player..."
	$(CXX) $(CXXFLAGS) \
	$(AUDIO_CFLAGS) \
	$(AUDIO_SRC) \
	$(AUDIO_PLAYER_SRC) \
	$(AUDIO_LIBS) \
	-o $(AUDIO_PLAYER_LINUX_TARGET)

android_audio_player: prepare $(AUDIO_SRC) platform/android/audio_android.cpp
ifeq ($(HAS_NDK),yes)
@echo "Building Android audio player..."

$(CLANGXX) $(CXXFLAGS) \
$(AUDIO_SRC) \
platform/android/audio_android.cpp \
-o $(AUDIO_PLAYER_ANDROID_TARGET) \
-landroid -llog

else
@echo "Toollibs: Android NDK not found."
@echo "Skipping android_audio_player build."
endif

# ============================================================
# FONT PREVIEW BUILD
# ============================================================

font_preview: prepare
	$(CXX) $(CXXFLAGS) \
	$(FONT_PREVIEW_SRC) \
	$(FONT_PREVIEW_LIBS) \
	-o $(FONT_PREVIEW_TARGET)

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
	$(MINGW) $(CXXFLAGS) $(FS_EMUCMD_SRC_WIN) -o $(FS_TARGET_WIN)
endif

# ============================================================
# BUILD GROUPS
# ============================================================

linux: mainlogger cpu_info gpu_info pop fs_emucmd audio_player

android: battery_info android_audio_player

all: prepare mainlogger tools pop windows pop_windows fs_emucmd fs_emucmd_windows audio_player android_audio_player

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

run_audio_linux:
	@$(AUDIO_PLAYER_LINUX_TARGET)

run_audio_android:
	@echo "Android binary: $(AUDIO_PLAYER_ANDROID_TARGET)"

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
	@echo "Android Dir  : $(BUILD_DIR_ANDROID)"
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
	@echo "make audio_player"
	@echo "make run_audio_linux"
	@echo "make run_audio_android"
