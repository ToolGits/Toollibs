#include "audio/audio.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static std::string lowerExtension(const fs::path& path) {
    std::string ext = path.extension().string();

    std::transform(
        ext.begin(),
        ext.end(),
        ext.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        }
    );

    return ext;
}

static std::vector<fs::path> findAudioFiles(const fs::path& directory) {
    std::vector<fs::path> files;

    try {
        if (!fs::exists(directory) || !fs::is_directory(directory))
            return files;

        for (const auto& entry : fs::directory_iterator(directory)) {
            if (!entry.is_regular_file())
                continue;

            const std::string ext = lowerExtension(entry.path());

            if (ext == ".wav" ||
                ext == ".ogg" ||
                ext == ".mp3") {
                files.push_back(entry.path());
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cout << "[AudioPlayer] Filesystem error: "
                  << e.what() << "\n";
    }

    std::sort(
        files.begin(),
        files.end(),
        [](const fs::path& a, const fs::path& b) {
            return a.filename().string() < b.filename().string();
        }
    );

    return files;
}

int main() {
    if (!Toollibs::Audio::init())
        return 1;

    const fs::path audioDirectory = "./audio_files";

    while (true) {
        std::vector<fs::path> files =
            findAudioFiles(audioDirectory);

        std::cout << "\n=== Toollibs Audio Player ===\n";
        std::cout << "1. List audio files\n";
        std::cout << "2. Play audio\n";
        std::cout << "3. Stop\n";
        std::cout << "4. Exit\n";
        std::cout << "> ";

        int option;

        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            std::cout << "[AudioPlayer] Invalid input.\n";
            continue;
        }

        if (option == 1) {
            if (files.empty()) {
                std::cout << "[AudioPlayer] No audio files found.\n";
                continue;
            }

            for (std::size_t i = 0; i < files.size(); ++i) {
                std::cout << i + 1
                          << ". "
                          << files[i].filename().string()
                          << "\n";
            }
        }
        else if (option == 2) {
            if (files.empty()) {
                std::cout << "[AudioPlayer] No audio files found.\n";
                continue;
            }

            std::cout << "Select file: ";

            std::size_t index;

            if (!(std::cin >> index) ||
                index < 1 ||
                index > files.size()) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );
                std::cout << "[AudioPlayer] Invalid selection.\n";
                continue;
            }

            Toollibs::Audio::play(files[index - 1].string());
        }
        else if (option == 3) {
            Toollibs::Audio::stop();
        }
        else if (option == 4) {
            break;
        }
        else {
            std::cout << "[AudioPlayer] Unknown option.\n";
        }
    }

    Toollibs::Audio::shutdown();
    return 0;
}
