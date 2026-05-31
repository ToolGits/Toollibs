#!/usr/bin/env bash

echo "=================================="
echo "Toollibs Deploy System (Multi-Arch)"
echo "=================================="

ARCH=$(uname -m)

BUILD_DIR="bin/$ARCH"
DOCS_DIR="docs/downloads"

echo "[1/4] Checking build output..."

if [ ! -d "$BUILD_DIR" ]; then
  echo "ERROR: build directory not found: $BUILD_DIR"
  exit 1
fi

echo "[2/4] Preparing docs/downloads..."
mkdir -p "$DOCS_DIR"

echo "[3/4] Cleaning old builds..."
rm -f "$DOCS_DIR"/*

echo "[4/4] Deploying executables..."

# mainlogger
if [ -f "$BUILD_DIR/mainlogger" ]; then
  cp "$BUILD_DIR/mainlogger" "$DOCS_DIR/mainlogger-$ARCH"
fi

# cpu_info
if [ -f "$BUILD_DIR/cpu_info" ]; then
  cp "$BUILD_DIR/cpu_info" "$DOCS_DIR/cpu_info-$ARCH"
fi

# gpu_info
if [ -f "$BUILD_DIR/gpu_info" ]; then
  cp "$BUILD_DIR/gpu_info" "$DOCS_DIR/gpu_info-$ARCH"
fi

echo "=================================="
echo "Deploy completed successfully!"
echo "Architecture: $ARCH"
echo "Output: $DOCS_DIR"
echo ""
echo "Powered by: Toollibs and toollibs-workstation"
echo "=================================="
