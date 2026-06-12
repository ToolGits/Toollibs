#include "audio.hpp"

#include <iostream>
#include <vector>

#ifdef __ANDROID__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <sndfile.h>

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"

namespace toollibs {

// =========================
// STATIC STATE
// =========================

bool Audio::initialized = false;
static Mix_Music* sdlMusic = nullptr;
static std::string currentPath;

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
// LOAD AUDIO
// =========================

bool Audio::load(const std::string& path) {

    if (!initialized)
        return false;

    currentPath = path;

    if (sdlMusic) {
        Mix_FreeMusic(sdlMusic);
        sdlMusic = nullptr;
    }

    // SDL_mixer handles formats internally
    sdlMusic = Mix_LoadMUS(path.c_str());

    if (!sdlMusic) {
        std::cout << "[Audio] Failed to load: " << path << "\n";
        return false;
    }

    std::cout << "[Audio] Loaded: " << path << "\n";
    return true;
}

// =========================
// PLAY
// =========================

void Audio::play() {

    if (!sdlMusic) {
        std::cout << "[Audio] No audio loaded\n";
        return;
    }

    Mix_PlayMusic(sdlMusic, 1);
}

// =========================
// PAUSE
// =========================

void Audio::pause() {

    if (!initialized) return;

    if (Mix_PausedMusic())
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

// =========================
// STOP
// =========================

void Audio::stop() {

    if (!initialized) return;

    Mix_HaltMusic();
}

// =========================
// IS LOADED
// =========================

bool Audio::isLoaded() {
    return sdlMusic != nullptr;
}

// =========================
// SHUTDOWN
// =========================

void Audio::shutdown() {

    if (!initialized)
        return;

    if (sdlMusic) {
        Mix_FreeMusic(sdlMusic);
        sdlMusic = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();

    initialized = false;

    std::cout << "[Audio] Shutdown complete\n";
}

}