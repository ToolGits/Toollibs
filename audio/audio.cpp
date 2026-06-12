#include "audio.hpp"

#include <filesystem>
#include <cstdlib>
#include <algorithm>

namespace fs = std::filesystem;

namespace toollibs::audio
{

Audio::Audio()
    : m_format(AudioFormat::Unknown),
      m_volume(100),
      m_loaded(false)
{
}

bool Audio::load(const std::string& path)
{
    if (!fs::exists(path))
        return false;

    auto ext = fs::path(path).extension().string();

    std::transform(
        ext.begin(),
        ext.end(),
        ext.begin(),
        ::tolower
    );

    if (ext == ".wav")
        m_format = AudioFormat::WAV;
    else if (ext == ".ogg")
        m_format = AudioFormat::OGG;
    else if (ext == ".mp3")
        m_format = AudioFormat::MP3;
    else
        return false;

    m_path = path;
    m_loaded = true;

    return true;
}

void Audio::play()
{
    if (!m_loaded)
        return;

    std::string cmd;

    cmd =
        "ffplay -nodisp -autoexit \"" +
        m_path +
        "\" >/dev/null 2>&1";

    std::system(cmd.c_str());
}

void Audio::pause()
{
}

void Audio::stop()
{
}

void Audio::setVolume(int volume)
{
    m_volume = volume;
}

bool Audio::isLoaded() const
{
    return m_loaded;
}

AudioFormat Audio::getFormat() const
{
    return m_format;
}

std::string Audio::getPath() const
{
    return m_path;
}

}