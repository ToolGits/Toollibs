#include "audio/audio.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// =========================
// UI DRAWING
// =========================

void drawHeader() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║           AUDIO PLAYER             ║\n";
    std::cout << "║        Toollibs v3.0 Module         ║\n";
    std::cout << "╚══════════════════════════════════════╝\n\n";
}

void drawMenu() {
    std::cout << "┌──────────── MENU ────────────┐\n";
    std::cout << "│  [1] List audio files        │\n";
    std::cout << "│  [2] Play audio              │\n";
    std::cout << "│  [3] Stop audio              │\n";
    std::cout << "│  [4] Exit                    │\n";
    std::cout << "└──────────────────────────────┘\n\n";
    std::cout << "➤ Select option: ";
}

void drawBox(const std::string& title) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║ " << title;

    for (int i = 0; i < (36 - (int)title.size()); i++)
        std::cout << " ";

    std::cout << "║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
}

// =========================
// AUDIO SCANNER
// =========================

std::vector<std::string> scanAudio(const std::string& path) {
    std::vector<std::string> files;

    for (auto& entry : fs::directory_iterator(path)) {

        if (!entry.is_regular_file())
            continue;

        std::string file = entry.path().string();

        if (file.ends_with(".wav") ||
            file.ends_with(".ogg") ||
            file.ends_with(".mp3")) {

            files.push_back(file);
        }
    }

    return files;
}

// =========================
// MAIN
// =========================

int main() {

    Audio audio;
    audio.init();

    std::string path = "./audio_files";

    drawHeader();

    while (true) {

        drawMenu();

        int option;
        std::cin >> option;

        if (option == 1) {

            drawBox("AUDIO FILES");

            auto files = scanAudio(path);

            if (files.empty()) {
                std::cout << "⚠ No audio files found.\n";
            } else {
                for (size_t i = 0; i < files.size(); i++) {
                    std::cout << " [" << i << "] " << files[i] << "\n";
                }
            }

            std::cout << "\n";

        }

        else if (option == 2) {

            auto files = scanAudio(path);

            if (files.empty()) {
                std::cout << "⚠ No audio available.\n";
                continue;
            }

            std::cout << "Select index: ";
            int idx;
            std::cin >> idx;

            if (idx < 0 || idx >= (int)files.size()) {
                std::cout << "Invalid index.\n";
                continue;
            }

            drawBox("PLAYING AUDIO");

            std::cout << "▶ " << files[idx] << "\n\n";

            audio.play(files[idx]);
        }

        else if (option == 3) {

            drawBox("AUDIO STOP");

            std::cout << "■ Stopping playback...\n\n";

            audio.stop();
        }

        else if (option == 4) {

            drawBox("EXIT");

            std::cout << "Closing Audio Player...\n\n";
            break;
        }

        else {
            std::cout << "Invalid option.\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    audio.shutdown();

    return 0;
}