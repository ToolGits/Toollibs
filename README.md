# Toollibs

Toollibs is a modular collection of reusable C++ libraries designed to provide simple, lightweight, and structured tools for software development.

It can be used as a base for games, emulators, system tools, and general-purpose applications.

---

## 🔧 Modules

- core: logging, basic utilities, and system helpers
- graphics: simple rendering and pixel manipulation
- input: keyboard, mouse, and controller handling
- audio: basic sound and audio system
- fs: file system utilities
- math: mathematical helpers and structures
- plugins: modular extension system

---

## 🎯 Goal

To build a clean, reusable, and modular C++ toolkit that can serve as a foundation for different types of projects.

---

## 🌍 Community Project

Toollibs is an open project built for the community.

Everyone is welcome to:
- contribute ideas
- improve code
- create new modules
- build bases and tools
- experiment freely
- help expand the project in any direction

This project is meant to be a space for creativity, collaboration, and learning.

## 📦 Build

### 🐧 Linux

```bash
git clone https://github.com/enzobobdevvideos04-ctrl/Toollibs.git
cd Toollibs

g++ core/mainlogger.cpp platform/platform.cpp input/input_simulation.cpp -o mainlogger

./mainlogger

### 🪟 Windows (MinGW)

Bash
git clone https://github.com/enzobobdevvideos04-ctrl/Toollibs.git
cd Toollibs

g++ core\mainlogger.cpp platform\platform.cpp input\input_simulation.cpp -o mainlogger.exe

mainlogger.exe

---

# 🤝 Contributing

```md id="contrib_clean"
## 🤝 Contributing

We welcome contributions to Toollibs!

1. Fork the repository  
2. Clone your fork  
   ```bash
   git clone https://github.com/YOUR_USERNAME/Toollibs.git
Create a new branch
Bash
git checkout -b my-feature
Make your changes
Commit
Bash
git commit -m "Add my feature"
Push
Bash
git push origin my-feature
Open a Pull Request