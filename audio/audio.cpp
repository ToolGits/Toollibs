#include "audio.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

namespace toollibs {

bool Audio::initialized = false;
void* Audio::music = nullptr;

bool Audio::init() {
    if (initialized) return true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << "\n";
        return false;
    }

    initialized = true;
    return true;
}

void Audio::shutdown() {
    if (music) {
        Mix_FreeMusic((Mix_Music*)music);
        music = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();
    initialized = false;
}

bool Audio::load(const std::string& path) {
    if (!initialized) init();

    if (music) {
        Mix_FreeMusic((Mix_Music*)music);
        music = nullptr;
    }

    music = Mix_LoadMUS(path.c_str());

    if (!music) {
        std::cerr << "Failed to load audio: " << Mix_GetError() << "\n";
        return false;
    }

    return true;
}

void Audio::play() {
    if (!music) return;
    Mix_PlayMusic((Mix_Music*)music, 1);
}

void Audio::pause() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void Audio::stop() {
    Mix_HaltMusic();
}

bool Audio::isLoaded() {
    return music != nullptr;
}

}