#include "audio/audio.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace Toollibs {

bool Audio::initialized = false;
static Mix_Music* musicHandle = nullptr;

bool Audio::init() {
    if (initialized)
        return true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "[Audio] SDL init failed: "
                  << SDL_GetError() << "\n";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "[Audio] SDL_mixer init failed: "
                  << Mix_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    initialized = true;
    std::cout << "[Audio] System ready (SDL backend)\n";
    return true;
}

bool Audio::load(const std::string& path) {
    if (!initialized)
        return false;

    Mix_Music* newMusic = Mix_LoadMUS(path.c_str());

    if (!newMusic) {
        std::cout << "[Audio] Failed to load: "
                  << path << " ("
                  << Mix_GetError() << ")\n";
        return false;
    }

    if (musicHandle) {
        Mix_FreeMusic(musicHandle);
        musicHandle = nullptr;
    }

    musicHandle = newMusic;
    return true;
}

void Audio::play(const std::string& file) {
    if (!load(file)) {
        std::cout << "[Audio] Load failed\n";
        return;
    }

    if (Mix_PlayMusic(musicHandle, 1) < 0) {
        std::cout << "[Audio] Playback failed: "
                  << Mix_GetError() << "\n";
        return;
    }

    std::cout << "[Audio] Playing: " << file << "\n";
}

void Audio::pause() {
    if (!initialized)
        return;

    if (Mix_PlayingMusic()) {
        if (Mix_PausedMusic())
            Mix_ResumeMusic();
        else
            Mix_PauseMusic();
    }
}

void Audio::stop() {
    if (!initialized)
        return;

    Mix_HaltMusic();
}

bool Audio::isLoaded() {
    return musicHandle != nullptr;
}

void Audio::shutdown() {
    if (!initialized)
        return;

    Mix_HaltMusic();

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
