#include <jni.h>
#include <string>

#include "audio/audio.hpp"

using namespace Toollibs;

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_toollibs_audio_ToollibsAudio_init(
    JNIEnv*,
    jclass
) {
    return Audio::init();
}

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_load(
    JNIEnv* env,
    jclass,
    jstring path
) {
    if (!path)
        return;

    const char* cpath =
        env->GetStringUTFChars(path, nullptr);

    if (!cpath)
        return;

    Audio::load(std::string(cpath));

    env->ReleaseStringUTFChars(path, cpath);
}

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_play(
    JNIEnv* env,
    jclass,
    jstring path
) {
    if (!path)
        return;

    const char* cpath =
        env->GetStringUTFChars(path, nullptr);

    if (!cpath)
        return;

    Audio::play(std::string(cpath));

    env->ReleaseStringUTFChars(path, cpath);
}

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_pause(
    JNIEnv*,
    jclass
) {
    Audio::pause();
}

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_stop(
    JNIEnv*,
    jclass
) {
    Audio::stop();
}

JNIEXPORT void JNICALL
Java_com_toollibs_audio_ToollibsAudio_shutdown(
    JNIEnv*,
    jclass
) {
    Audio::shutdown();
}

}
