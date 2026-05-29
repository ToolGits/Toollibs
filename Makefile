CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

SRC = core/logger.cpp platform/platform.cpp core/mainlogger.cpp math/math.cpp graphics/graphics.cpp

ARCH := $(shell uname -m)

ifeq ($(ARCH),x86_64)
    PLATFORM = PC (x86_64)
else ifeq ($(ARCH),i386)
    PLATFORM = PC (x86)
else ifeq ($(ARCH),i686)
    PLATFORM = PC (x86)
else ifeq ($(ARCH),aarch64)
    PLATFORM = ARM64 (Android)
else ifeq ($(ARCH),armv7l)
    PLATFORM = ARM32 (Android)
else ifeq ($(ARCH),armv6l)
    PLATFORM = ARM32 (Android)
else
    PLATFORM = Unknown
endif

OUT = bin/$(ARCH)/mainlogger

all:
	@mkdir -p bin/$(ARCH)
	@echo "Building Toollibs for $(PLATFORM)"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run:
	@echo "Running Toollibs on $(PLATFORM)"
	./$(OUT)

clean:
	rm -rf bin
