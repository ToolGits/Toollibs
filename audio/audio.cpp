#include "audio.hpp"
#include <iostream>
#include <string>

#ifdef __ANDROID__
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/log.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <sndfile.h>

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"

namespace toollibs {

// =========================
// STATE
// =========================

bool Audio::initialized = false;
static Mix_Music* musicHandle = nullptr;
static std::string currentFile;

// =========================
// INIT (LINUX + ANDROID)
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

#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_INFO, "ToollibsAudio", "Audio system initialized (Android)");
#else
    std::cout << "[Audio] System ready (Linux SDL backend)\n";
#endif

    return true;
}

// =========================
// DETECT EXTENSION
// =========================

static std::string getExt(const std::string& path) {
    size_t pos = path.find_last_of(".");
    if (pos == std::string::npos) return "";
    return path.substr(pos);
}

// =========================
// LOAD DECODER LAYER
// =========================

static bool loadWav(const std::string& path) {
    SF_INFO info;
    SNDFILE* file = sf_open(path.c_str(), SFM_READ, &info);
    if (!file) return false;

    std::vector<float> buffer(info.frames * info.channels);
    sf_readf_float(file, buffer.data(), info.frames);
    sf_close(file);

    std::cout << "[Audio] WAV loaded (libsndfile)\n";
    return true;
}

static bool loadOgg(const std::string& path) {

    int channels, sampleRate;
    short* output = nullptr;

    int samples = stb_vorbis_decode_filename(
        path.c_str(),
        &channels,
        &sampleRate,
        &output
    );

    if (samples <= 0) return false;

    free(output);

    std::cout << "[Audio] OGG loaded (stb_vorbis)\n";
    return true;
}

static bool loadMp3(const std::string& path) {

    mp3dec_ex_t dec;
    if (mp3dec_ex_open(&dec, path.c_str(), MP3D_SEEK_TO_SAMPLE))
        return false;

    mp3dec_ex_close(&dec);

    std::cout << "[Audio] MP3 loaded (minimp3)\n";
    return true;
}

// =========================
// LOAD
// =========================

bool Audio::load(const std::string& path) {

    if (!initialized)
        return false;

    currentFile = path;

    std::string ext = getExt(path);

    if (ext == ".wav") {
        loadWav(path);
    }
    else if (ext == ".ogg") {
        loadOgg(path);
    }
    else if (ext == ".mp3") {
        loadMp3(path);
    }
    else {
        std::cout << "[Audio] Unsupported format\n";
        return false;
    }

    if (musicHandle)
        Mix_FreeMusic(musicHandle);

    musicHandle = Mix_LoadMUS(path.c_str());

    return musicHandle != nullptr;
}

// =========================
// PLAYBACK (SDL BACKEND)
// =========================

void Audio::play(const std::string& file) {
      if (!musicHandle) {
        std::cout << "[Audio] No audio loaded\n";
        return;
    }

    Mix_PlayMusic(musicHandle, 1);
  }
}

    if (!musicHandle) {
        std::cout << "[Audio] No audio loaded\n";
        return;
    }

    Mix_PlayMusic(musicHandle, 1);
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

#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_INFO, "ToollibsAudio", "Audio shutdown");
#else
    std::cout << "[Audio] Shutdown complete\n";
#endif
}

}