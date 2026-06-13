#include "audio/audio.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// =========================
// UTIL
// =========================

static bool endsWith(const std::string& s, const std::string& suf) {
    return s.size() >= suf.size() &&
           s.compare(s.size() - suf.size(), suf.size(), suf) == 0;
}

// =========================
// SCANNER SAFE
// =========================

static std::vector<std::string> scanAudio(const std::string& path) {

    std::vector<std::string> files;

    if (!fs::exists(path)) {
        std::cout << "[Audio] Folder not found: " << path << "\n";
        return files;
    }

    for (const auto& entry : fs::directory_iterator(path)) {

        if (!entry.is_regular_file())
            continue;

        std::string file = entry.path().string();

        if (endsWith(file, ".wav") ||
            endsWith(file, ".ogg") ||
            endsWith(file, ".mp3")) {
            files.push_back(file);
        }
    }

    return files;
}

// =========================
// UI
// =========================

static void header() {
    std::cout <<
R"(

╔══════════════════════════════════════╗
║           TOOLLIBS AUDIO            ║
║           Terminal Player           ║
╚══════════════════════════════════════╝

)";
}

static void menu() {
    std::cout <<
R"(
┌──────────── MENU ────────────┐
│  1 - List songs              │
│  2 - Play song               │
│  3 - Stop                    │
│  4 - Exit                    │
└──────────────────────────────┘
> ";
)
}

// =========================
// MAIN
// =========================

int main() {

    toollibs::Audio audio;

    if (!audio.init()) {
        std::cout << "[Audio] Failed to initialize system\n";
        return 1;
    }

    std::string path = "./audio_files";

    header();

    while (true) {

        menu();

        int opt;
        std::cin >> opt;

        if (opt == 1) {

            auto files = scanAudio(path);

            std::cout << "\n[AUDIO FILES]\n";

            if (files.empty()) {
                std::cout << "No audio files found.\n\n";
            } else {
                for (size_t i = 0; i < files.size(); i++) {
                    std::cout << " [" << i << "] " << files[i] << "\n";
                }
                std::cout << "\n";
            }
        }

        else if (opt == 2) {

            auto files = scanAudio(path);

            if (files.empty()) {
                std::cout << "No audio available.\n";
                continue;
            }

            std::cout << "Select index: ";

            int idx;
            std::cin >> idx;

            if (idx < 0 || idx >= (int)files.size()) {
                std::cout << "Invalid index\n";
                continue;
            }

            std::cout << "\n▶ Playing: " << files[idx] << "\n\n";

            audio.play(files[idx]);
        }

        else if (opt == 3) {

            std::cout << "■ Stopping audio...\n";

            audio.stop();
        }

        else if (opt == 4) {

            std::cout << "Bye!\n";
            break;
        }

        else {
            std::cout << "Invalid option\n";
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }

    audio.shutdown();

    return 0;
}