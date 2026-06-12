#include <jni.h>
#include <string>
#include "../../audio/audio.hpp"

using namespace toollibs;

extern "C" {

// =========================
// INIT
// =========================

JNIEXPORT jboolean JNICALL
Java_com_toollibs_audio_ToollibsAudio_init(JNIEnv*, jclass) {
    return Audio::init();
}

// =========================
// LOAD
// =========================

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_load(JNIEnv* env, jclass, jstring path) {

    const char* cpath = env->GetStringUTFChars(path, 0);

    Audio::load(std::string(cpath));

    env->ReleaseStringUTFChars(path, cpath);
}

// =========================
// PLAY
// =========================

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_play(JNIEnv*, jclass) {
    Audio::play();
}

// =========================
// PAUSE
// =========================

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_pause(JNIEnv*, jclass) {
    Audio::pause();
}

// =========================
// STOP
// =========================

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_stop(JNIEnv*, jclass) {
    Audio::stop();
}

// =========================
// SHUTDOWN
// =========================

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_shutdown(JNIEnv*, jclass) {
    Audio::shutdown();
}

}