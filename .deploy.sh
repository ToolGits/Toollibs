#!/usr/bin/env bash

echo "=================================="
echo "Toollibs Deploy System (Multi-Arch)"
echo "=================================="

ARCH=$(uname -m)

BUILD_DIR="bin/$ARCH"
BUILD_DIR_WIN="bin/windows_$ARCH"

DOCS_DIR="docs/downloads"

echo "[1/6] Checking build outputs..."

if [ ! -d "$BUILD_DIR" ]; then
  echo "ERROR: Linux build directory not found: $BUILD_DIR"
  exit 1
fi

echo "[2/6] Preparing docs/downloads..."
mkdir -p "$DOCS_DIR"

echo "[3/6] Cleaning old builds..."
rm -f "$DOCS_DIR"/*-"$ARCH"
rm -f "$DOCS_DIR"/*.exe

echo "[4/6] Deploying Linux executables..."

for bin in mainlogger cpu_info gpu_info pop; do
  if [ -f "$BUILD_DIR/$bin" ]; then
    cp "$BUILD_DIR/$bin" "$DOCS_DIR/$bin-$ARCH"
  fi
done

echo "[5/6] Deploying Windows binaries (if available)..."

if [ -d "$BUILD_DIR_WIN" ]; then
  for bin in mainlogger.exe pop.exe; do
    if [ -f "$BUILD_DIR_WIN/$bin" ]; then
      cp "$BUILD_DIR_WIN/$bin" "$DOCS_DIR/${bin%.exe}-$ARCH.exe"
    fi
  done
fi

echo "[6/6] Generating index.json..."

INDEX_FILE="$DOCS_DIR/index.json"

echo "[" > "$INDEX_FILE"

first=true

for file in "$DOCS_DIR"/*; do
  name=$(basename "$file")

  if [[ "$name" == "index.json" ]]; then
    continue
  fi

  if [ "$first" = true ]; then
    first=false
  else
    echo "," >> "$INDEX_FILE"
  fi

  echo -n "  \"$name\"" >> "$INDEX_FILE"
done

echo "" >> "$INDEX_FILE"
echo "]" >> "$INDEX_FILE"

echo "==========================================="
echo "Deploy completed successfully!"
echo "Architecture: $ARCH"
echo "Linux build: $BUILD_DIR"
echo "Windows build: $BUILD_DIR_WIN"
echo "Output: $DOCS_DIR"
echo ""
echo "Powered by Toollibs & Toollibs-workstation"
echo "==========================================="