#ifdef __ANDROID__

#include <aaudio/AAudio.h>
#include <android/log.h>

static AAudioStream* stream = nullptr;

bool androidAudioInit() {

    AAudioStreamBuilder* builder;

    if (AAudio_createStreamBuilder(&builder) != AAUDIO_OK)
        return false;

    AAudioStreamBuilder_setDirection(builder, AAUDIO_DIRECTION_OUTPUT);
    AAudioStreamBuilder_setPerformanceMode(builder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);

    if (AAudioStreamBuilder_openStream(builder, &stream) != AAUDIO_OK)
        return false;

    AAudioStream_requestStart(stream);

    __android_log_print(ANDROID_LOG_INFO, "ToollibsAudio", "AAudio initialized");

    return true;
}

void androidAudioShutdown() {

    if (stream) {
        AAudioStream_requestStop(stream);
        AAudioStream_close(stream);
        stream = nullptr;
    }
}

#endif