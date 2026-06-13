#ifndef TOOLLIBS_AUDIO_HPP
#define TOOLLIBS_AUDIO_HPP

#include <string>

namespace toollibs {

class Audio {
public:
    static bool init();
    static void shutdown();

    static bool load(const std::string& path);
    static void play(const std::string& file);

    static void pause();
    static void stop();

    static bool isLoaded();

private:
    static bool initialized;
};

}

#endif