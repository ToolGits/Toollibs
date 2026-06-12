#pragma once
#include <vector>

namespace toollibs {

struct AudioBuffer {
    std::vector<float> samples;
    int sampleRate = 44100;
    int channels = 2;
    bool valid = false;
};

}