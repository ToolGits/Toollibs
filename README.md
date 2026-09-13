<p align="center">
  <img
    src=".github/assets/Toollibs_newlogo.png"
    alt="Toollibs logo"
    width="250"
  />
</p>

<h1 align="center">Toollibs</h1>

<p align="center">
  <strong>Modular C++ systems for lightweight, portable and extensible software.</strong>
</p>

<p align="center">
  Build it. Verify it. Deploy it.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/version-v4.3-purple" alt="Version v4.3">
  <img src="https://img.shields.io/badge/codename-Androck%20Horizon-blueviolet" alt="Codename Androck Horizon">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="MIT License">
  <img src="https://img.shields.io/badge/status-stable-brightgreen" alt="Stable">
  <img src="https://img.shields.io/badge/Linux-supported-orange" alt="Linux supported">
  <img src="https://img.shields.io/badge/Windows-supported-orange" alt="Windows supported">
  <img src="https://img.shields.io/badge/Android-supported-orange" alt="Android supported">
</p>

<p align="center">
  <a href="https://toolgits.github.io/Toollibs/">Website</a> •
  <a href="https://toolgits.github.io/Toollibs/changelog.html">Changelog</a> •
  <a href="https://toolgits.github.io/Toollibs/downloads.html">Downloads</a> •
  <a href="https://github.com/ToolGits/Toollibs/issues">Issues</a>
</p>

> [!IMPORTANT]
> **Toollibs v4.3 — Androck Horizon is the current stable release.**
>
> The `main` branch contains the stable Toollibs line.
> The `nightly` branch contains experimental development and may introduce breaking changes.

---

## 📖 About

**Toollibs** is a modular C++ framework ecosystem designed for lightweight, portable and extensible software.

Instead of forcing every application into a single monolithic architecture, Toollibs is organized into focused systems that can be built, tested and used independently.

The project combines:

- Modular C++ components
- Cross-platform development
- System and platform tooling
- Plugin infrastructure
- Graphics and mathematics utilities
- Input handling
- Audio support
- Runtime verification
- Automated deployment
- Android development support

Toollibs is designed to serve both practical software and experimental projects.

---

## 🧩 Architecture

Toollibs is organized into focused modules and platform-specific systems.

~~~text
Toollibs
│
├── core
│   ├── logger
│   ├── mainlogger
│   └── timertrigger
│
├── math
│   └── mathematics and vector systems
│
├── graphics
│   ├── graphics
│   ├── font_renderer
│   └── font_preview
│
├── input
│   └── input systems
│
├── fs
│   ├── filesystem
│   ├── FS Emulated CMD
│   └── replxx integration
│
├── plugins
│   ├── MathPlugin
│   └── POP
│
├── audio
│   ├── audio
│   └── audio_player
│
└── platform
    ├── linux
    │   ├── cpu
    │   └── gpu
    │
    └── android
        ├── battery
        ├── audio
        └── android_device_diagnostic
~~~

Each area has a specific responsibility while remaining part of the same Toollibs ecosystem.

---

## ✨ Features

### ⚙️ Core Systems

The `core` module provides foundational runtime functionality, including:

- Logging
- MainLogger
- Timer-based triggers
- Platform integration

### 🧮 Mathematics

The `math` module provides reusable mathematical functionality for applications and other Toollibs components.

### 🎨 Graphics

The `graphics` module provides lightweight graphics-related systems, including font rendering and font preview functionality.

### 🎮 Input

The `input` module is intended for input-related systems such as keyboards, mice and controllers.

### 📁 FS Emulated CMD

Toollibs includes **FS Emulated CMD**, a terminal-emulator-style environment implemented inside the `fs` module.

The system uses the project's filesystem components together with `replxx` integration for interactive terminal functionality.

### 🔌 Plugins

Toollibs includes a plugin infrastructure with built-in components such as:

- **MathPlugin**
- **POP**

POP provides automation-oriented tooling for the Toollibs development workflow.

### 🎵 Audio

The `audio` module provides audio functionality and includes an audio player target.

Linux audio builds use:

- `libsndfile`
- `SDL2`
- `SDL2_mixer`

### 🖥️ Platform Tools

Toollibs provides platform-specific utilities for supported environments.

Linux tooling includes:

- `cpu_info`
- `gpu_info`

Android tooling includes:

- `battery_info`
- `android_audio_player`
- `android_device_diagnostic`

---

## 🌍 Platform Support

| Platform | Support | Architecture / Target |
| --- | --- | --- |
| 🐧 Linux | ✅ | Native host architecture |
| 🪟 Windows | ✅ | x86_64 / MinGW |
| 🤖 Android | ✅ | AArch64 / Android NDK |

The build system automatically detects the host architecture and organizes generated binaries under architecture-specific directories.

---

## 🔨 Build System

Toollibs uses a **Makefile-based C++17 build system**.

The build system automatically detects:

- Host architecture
- MinGW availability
- Android NDK availability

### Basic Build Layout

~~~text
bin/
├── <host-architecture>/
│   ├── mainlogger
│   ├── cpu_info
│   ├── gpu_info
│   ├── battery_info
│   ├── pop
│   ├── fs_emucmd
│   ├── audio_player
│   └── font_preview
│
├── windows_x86_64/
│   ├── mainlogger.exe
│   ├── pop.exe
│   └── fs_emucmd.exe
│
└── android/
    ├── android_audio_player
    └── libandroid_device_diagnostic.so
~~~

### Main Targets

~~~text
make mainlogger
make cpu_info
make gpu_info
make battery_info
make tools
make pop
make fs_emucmd
make audio_player
make android_audio_player
make android_device_diagnostic
~~~

The `tools` target builds the primary platform tools and audio components.

---

## 🤖 Android Development

Android support is integrated directly into the Makefile through the Android NDK.

The project uses an Android NDK toolchain and currently targets:

~~~text
Android API: 24
NDK: 25.2.9519653
Toolchain: aarch64-linux-android
~~~

Android targets include:

- Android audio player
- Battery information
- Android device diagnostic shared library

If the configured Android NDK is unavailable, Android-specific targets are skipped instead of stopping the regular build process.

---

## 🧪 Runtime Verification

Toollibs includes **MainLogger** as part of its runtime-oriented verification and logging infrastructure.

The build system can produce a main runtime executable alongside the platform utilities and other Toollibs components.

This allows generated builds to be tested independently before deployment.

---

## 📦 Automated Deployment

Toollibs includes an automated multi-architecture deployment script:

~~~text
.deploy.sh
~~~

The deployment pipeline:

1. Checks the current Linux build output.
2. Creates the download directory.
3. Removes previous generated binaries.
4. Deploys Linux executables.
5. Deploys Windows x86_64 binaries.
6. Deploys Android binaries.
7. Generates `index.json`.

Deployment output is placed under:

~~~text
docs/
└── downloads/
    ├── mainlogger-<arch>
    ├── cpu_info-<arch>
    ├── gpu_info-<arch>
    ├── battery_info-<arch>
    ├── pop-<arch>
    ├── fs_emucmd-<arch>
    ├── audio_player-<arch>
    ├── font_preview-<arch>
    ├── *.exe
    ├── android_audio_player-android
    └── index.json
~~~

The generated `index.json` provides a machine-readable list of the deployed downloads.

---

## 🌙 Nightly Development

Toollibs maintains a dedicated **`nightly`** branch for experimental development.

~~~text
main
  │
  └── Stable Toollibs
       │
       └── v4.3 — Androck Horizon


nightly
  │
  ├── New features
  ├── Experimental APIs
  ├── Internal redesigns
  ├── New platform support
  └── Future releases
~~~

The `nightly` branch is:

- Experimental
- Unstable
- Under active development
- Subject to breaking changes
- Not recommended for production use

Features developed in Nightly may eventually reach `main`, but they are not guaranteed to do so.

---

## 🧭 Project Direction

Toollibs is designed to remain a flexible foundation for lightweight software.

Possible applications include:

- System utilities
- Game development
- Lightweight engines
- Plugin-based applications
- Development tools
- Experimental software
- Platform utilities

The project focuses on:

**Modularity • Portability • Verification • Automation**

---

## 🕰️ From ServerHub to Toollibs

Toollibs began after the discontinuation of **ServerHub**, initially serving as its replacement.

However, the project soon took a different direction.

Instead of continuing to focus entirely on server software, Toollibs evolved into a **C++ library and modular development project**. The original idea of replacing ServerHub gradually became something much larger.

As development continued, Toollibs grew in both scope and ambition:

- It evolved from a simple replacement project into a standalone library.
- Its architecture became larger and more modular.
- Its documentation and `README.md` went through major revisions and improvements.
- The project's description and identity were continuously refined.
- The Toollibs website was created.
- The project expanded with new systems, modules and tools.
- **ToollibsServer** was introduced as the **backend/API system for the Toollibs website**, providing the server-side infrastructure behind the project's web presence.
- **Toollibs-workstation** was created as another branch of the project's evolution. It was later discontinued as an independent project and evolved into **ToolGits-workstation**.
- Android support was introduced, expanding Toollibs beyond traditional desktop environments.
- The project continued growing in functionality, infrastructure and scope.

The development of Toollibs was therefore not a straight continuation of ServerHub. It was a process of transformation.

What started as a replacement for a discontinued server project became a **large, independent C++ framework ecosystem** with its own architecture, website, documentation, tooling, platform support and identity.

Today, Toollibs is no longer defined by ServerHub or by its original purpose.

**ServerHub was the starting point. Toollibs became its own project.**

From a replacement, to a library, to a growing ecosystem — Toollibs evolved into what it is today.

---

## 🌱 Contributing

Toollibs is open to experimentation and contributions.

You can:

- Contribute code
- Create new modules
- Improve existing systems
- Propose features
- Experiment with the architecture
- Report bugs
- Fork the project

For bugs and feature requests, use the repository's **Issues** section.

---

## 🏢 Maintained by ToolGits

Toollibs is an official project of the **ToolGits** organization.

- **Organization:** https://github.com/ToolGits
- **Creator:** https://github.com/enzobobdevvideos04-ctrl

Toollibs maintains its own identity within the ToolGits project family, including its own logo and modular C++ architecture.

---

## 📄 License

Toollibs is released under the **MIT License**.

**Copyright © 2026 ToolGits.**

---

<p align="center">
  <strong>Toollibs — Modular systems. Verified runtime. Automated deployment.</strong>
</p>