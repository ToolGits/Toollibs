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
  <img src="https://img.shields.io/badge/version-v4.4-purple" alt="Version v4.4">
  <img src="https://img.shields.io/badge/codename-RebirthCatalyst-blueviolet" alt="Codename RebirthCatalyst">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="MIT License">
  <img src="https://img.shields.io/badge/status-stable-brightgreen" alt="Stable">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Linux-supported-6b7280" alt="Linux supported">
  <img src="https://img.shields.io/badge/Windows-supported-0078D4" alt="Windows supported">
  <img src="https://img.shields.io/badge/Android-supported-3DDC84" alt="Android supported">
</p>

<p align="center">
  <a href="https://toolgits.github.io/Toollibs/">Website</a> •
  <a href="https://toolgits.github.io/Toollibs/changelog.html">Changelog</a> •
  <a href="https://toolgits.github.io/Toollibs/downloads.html">Downloads</a> •
  <a href="https://toolgits.github.io/Toollibs/devices.html">Devices</a> •
  <a href="https://github.com/ToolGits/Toollibs/issues">Issues</a>
</p>

> [!IMPORTANT]
> **Toollibs v4.4 — RebirthCatalyst** is the current stable release.
>
> The [`main`](https://github.com/ToolGits/Toollibs/tree/main) branch, also known as **TAether**, represents the stable Toollibs development line.
> It contains released and verified changes intended for regular use.
>
> The [`nightly`](https://github.com/ToolGits/Toollibs/tree/nightly) branch, also known as **TNether**, represents the current experimental development line.
> It may contain unfinished features, internal changes, regressions, or breaking changes before they reach a stable release.
>
> For the most reliable and predictable experience, use **TAether**.
> If you want to follow ongoing development and test upcoming changes, **TNether** is the experimental option.
>
> The [`community`](https://github.com/ToolGits/Toollibs/tree/community) branch is a legacy branch and is no longer used for active development.
> It originally served a similar purpose to the current `nightly` branch, providing an experimental development space designed with the Toollibs community in mind.
>
> The `community` branch was eventually discontinued and replaced by **TNether** as the project's experimental development line.
> Although it is no longer maintained, the branch remains available as part of Toollibs' history.
>
> If you want to explore what Toollibs looked like during that period and discover a small piece of its older development history, you can still visit the [`community` branch](https://github.com/ToolGits/Toollibs/tree/community).

---

## 📖 About

Toollibs is a **modular C++ Framework Ecosystem** designed for lightweight, portable and extensible software.

Instead of forcing every application into a single monolithic architecture, Toollibs is organized into focused systems that can be built, tested and used independently while remaining part of the same ecosystem.

The project combines:

- Modular C++ systems
- Cross-platform development
- System and platform tooling
- Plugin infrastructure
- Graphics and mathematics utilities
- Input handling
- Audio support
- Runtime verification
- Automated deployment
- Android development support

Toollibs is designed to support both practical software and experimental projects.

---

## 🗂️ Repository Navigation

Important parts of the Toollibs repository are directly accessible below:

- 📦 [`bin/`](./bin/) — Generated binaries and build outputs.
- 📚 [`docs/`](./docs/) — Toollibs website and documentation.
- 📥 [`docs/downloads/`](./docs/downloads/) — Deployed downloadable builds.
- 🔨 [`Makefile`](./Makefile) — Main build system.
- 📦 [`.deploy.sh`](./.deploy.sh) — Automated deployment pipeline.
- 🌐 [`docs/index.html`](./docs/index.html) — Main Toollibs website page.
- 📄 [`LICENSE`](./LICENSE) — MIT License.
- 📖 [`README.md`](./README.md) — Project documentation.
- 🐞 [Issues](https://github.com/ToolGits/Toollibs/issues) — Bug reports and feature requests.

---

## 🧩 Architecture

Toollibs is organized into focused modules and platform-specific systems.

Where available, the module names below link directly to their corresponding repository directories.

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

Main repository areas:

- [`core/`](./core/) — Core runtime systems.
- [`math/`](./math/) — Mathematics and vector systems.
- [`graphics/`](./graphics/) — Graphics-related systems.
- [`input/`](./input/) — Input systems.
- [`fs/`](./fs/) — Filesystem and FS Emulated CMD systems.
- [`plugins/`](./plugins/) — Toollibs plugin infrastructure.
- [`audio/`](./audio/) — Audio systems.
- [`platform/`](./platform/) — Platform-specific utilities.

Each area has a specific responsibility while remaining part of the same Toollibs ecosystem.

---

## ✨ Features

### ⚙️ Core Systems

The [`core/`](./core/) module provides foundational runtime functionality, including:

- Logging
- MainLogger
- Timer-based triggers
- Platform integration

### 🧮 Mathematics

The [`math/`](./math/) module provides reusable mathematical functionality for applications and other Toollibs components.

### 🎨 Graphics

The [`graphics/`](./graphics/) module provides lightweight graphics-related systems, including font rendering and font preview functionality.

### 🎮 Input

The [`input/`](./input/) module provides input-related systems for devices such as keyboards, mice and controllers.

### 📁 FS Emulated CMD

Toollibs includes **FS Emulated CMD**, a terminal-emulator-style environment implemented inside the [`fs/`](./fs/) module.

The system combines Toollibs filesystem functionality with [`replxx`](https://github.com/AmokHuginnsson/replxx) integration to provide interactive terminal functionality.

### 🔌 Plugins

Toollibs includes a plugin infrastructure with built-in components such as:

- MathPlugin
- POP

The plugin sources and related tooling can be explored under [`plugins/`](./plugins/).

POP provides automation-oriented tooling for the Toollibs development workflow, assisting with repetitive repository and development tasks.

### 🎵 Audio

The [`audio/`](./audio/) module provides audio functionality and includes an audio player target.

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

Platform-specific implementations are organized under [`platform/`](./platform/).

---

## 🌍 Platform Support

| Platform | Support | Architecture / Target |
|---|---|---|
| 🐧 Linux | ✅ | Native host architecture |
| 🪟 Windows | ✅ | x86_64 / MinGW |
| 🤖 Android | ✅ | AArch64 / Android NDK |

The build system automatically detects the host architecture and organizes generated binaries under architecture-specific directories.

---

## 🔨 Build System

Toollibs uses a Makefile-based **C++17** build system.

The main build configuration is available in [`Makefile`](./Makefile).

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

The [`bin/`](./bin/) directory contains generated build outputs when present.

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

Android support is integrated directly into the [`Makefile`](./Makefile) through the Android NDK.

The project currently targets:

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

The build system can produce a main runtime executable alongside platform utilities and other Toollibs components.

This allows generated builds to be tested independently before deployment.

---

## 📦 Automated Deployment

Toollibs includes an automated multi-architecture deployment script:

[`./.deploy.sh`](./.deploy.sh)

The deployment pipeline:

1. Checks the current Linux build output.
2. Creates the download directory.
3. Removes previous generated binaries.
4. Deploys Linux executables.
5. Deploys Windows x86_64 binaries.
6. Deploys Android binaries.
7. Generates `index.json`.

Deployment output is placed under [`docs/downloads/`](./docs/downloads/):

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

The generated [`index.json`](./docs/downloads/index.json) provides a machine-readable list of the deployed downloads when the generated file is present.

---

## 🌙 Nightly Development

Toollibs maintains a dedicated [`nightly`](https://github.com/ToolGits/Toollibs/tree/nightly) branch for experimental development.

~~~text
main
  │
  └── Stable Toollibs
       │
       └── v4.4 — RebirthCatalyst


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

Instead of remaining focused on server software, Toollibs evolved from its original **C++ library form** into a larger and more modular **Framework Ecosystem**.

As development continued, Toollibs grew in scope and ambition:

- It evolved from a simple replacement project into a standalone C++ project.
- Its architecture became larger and more modular.
- Its documentation and `README.md` went through major revisions and improvements.
- The project's description and identity were continuously refined.
- The Toollibs website was created.
- The project expanded with new systems, modules and tools.
- ToollibsServer was introduced as the backend/API system for the Toollibs website.
- Toollibs-workstation was created as another branch of the project's evolution and later evolved into ToolGits-workstation.
- Android support was introduced, expanding Toollibs beyond traditional desktop environments.
- The project continued growing in functionality, infrastructure and scope.

The development of Toollibs was therefore not a straight continuation of ServerHub. It was a process of transformation.

What started as a replacement for a discontinued server project became an independent C++ **Framework Ecosystem** with its own architecture, website, documentation, tooling, platform support and identity.

Today, Toollibs is no longer defined by ServerHub or by its original purpose.

ServerHub was the starting point. Toollibs became its own project.

**From a replacement, to a library, to a Framework Ecosystem — Toollibs evolved into what it is today.**

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

For bugs and feature requests, use the repository's [Issues](https://github.com/ToolGits/Toollibs/issues) section.

---

## 🏢 Maintained by ToolGits

Toollibs is an official project of the [ToolGits](https://github.com/ToolGits) organization.

- Organization: https://github.com/ToolGits
- Creator: https://github.com/enzobobdevvideos04-ctrl

Toollibs maintains its own identity within the ToolGits project family, including its own logo and modular C++ Framework Ecosystem.

---

## 📄 License

Toollibs is released under the [MIT License](./LICENSE).

Copyright © 2026 enzobobdevvideos04-ctrl / ToolGits.

---

<p align="center">
  <strong>Toollibs — Modular systems. Verified runtime. Automated deployment.</strong>
</p>