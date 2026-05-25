CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = core/logger.cpp platform/platform.cpp core/mainlogger.cpp
OUT = mainlogger

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

all:
	@echo "Building Toollibs for $(PLATFORM)"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run:
	@echo "Running Toollibs on $(PLATFORM)"
	./$(OUT)

clean:
	rm -f $(OUT)
