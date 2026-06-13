#include "audio/audio.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace toollibs {

// =========================
// STATE
// =========================

bool Audio::initialized = false;

static Mix_Music* musicHandle = nullptr;

// =========================
// INIT
// =========================

bool Audio::init() {

    if (initialized)
        return true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "[Audio] SDL init failed\n";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "[Audio] SDL_mixer init failed\n";
        return false;
    }

    initialized = true;

    std::cout << "[Audio] System ready (SDL backend)\n";
    return true;
}

// =========================
// LOAD
// =========================

bool Audio::load(const std::string& path) {

    if (!initialized)
        return false;

    if (musicHandle) {
        Mix_FreeMusic(musicHandle);
        musicHandle = nullptr;
    }

    musicHandle = Mix_LoadMUS(path.c_str());

    if (!musicHandle) {
        std::cout << "[Audio] Failed to load: " << path << "\n";
        return false;
    }

    return true;
}

// =========================
// PLAY
// =========================

void Audio::play(const std::string& file) {

    if (!load(file)) {
        std::cout << "[Audio] Load failed\n";
        return;
    }

    Mix_PlayMusic(musicHandle, 1);

    std::cout << "[Audio] Playing: " << file << "\n";
}

// =========================
// PAUSE
// =========================

void Audio::pause() {

    if (Mix_PausedMusic())
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

// =========================
// STOP
// =========================

void Audio::stop() {
    Mix_HaltMusic();
}

// =========================
// STATUS
// =========================

bool Audio::isLoaded() {
    return musicHandle != nullptr;
}

// =========================
// SHUTDOWN
// =========================

void Audio::shutdown() {

    if (musicHandle) {
        Mix_FreeMusic(musicHandle);
        musicHandle = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();

    initialized = false;

    std::cout << "[Audio] Shutdown complete\n";
}

}