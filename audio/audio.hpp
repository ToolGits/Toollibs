#pragma once

#include <string>

namespace toollibs::audio
{

enum class AudioFormat
{
    Unknown,
    WAV,
    OGG,
    MP3
};

class Audio
{
public:

    Audio();

    bool load(const std::string& path);

    void play();
    void pause();
    void stop();

    void setVolume(int volume);

    bool isLoaded() const;

    AudioFormat getFormat() const;

    std::string getPath() const;

private:

    std::string m_path;
    AudioFormat m_format;
    int m_volume;
    bool m_loaded;
};

}