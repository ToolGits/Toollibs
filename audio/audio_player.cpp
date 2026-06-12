#include "audio.hpp"

#include <iostream>

using namespace toollibs::audio;

static void printHelp()
{
    std::cout
        << "Toollibs Audio Player\n"
        << "Usage:\n"
        << "audio_player <file>\n";
}

static const char* formatToString(AudioFormat format)
{
    switch(format)
    {
        case AudioFormat::WAV:
            return "WAV";

        case AudioFormat::OGG:
            return "OGG";

        case AudioFormat::MP3:
            return "MP3";

        default:
            return "UNKNOWN";
    }
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printHelp();
        return 1;
    }

    Audio audio;

    if(!audio.load(argv[1]))
    {
        std::cout
            << "FAIL: unable to load file\n";

        return 1;
    }

    std::cout
        << "Loaded: "
        << audio.getPath()
        << "\n";

    std::cout
        << "Format: "
        << formatToString(audio.getFormat())
        << "\n";

    audio.play();

    return 0;
}