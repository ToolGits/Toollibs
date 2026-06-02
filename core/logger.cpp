#include "../platform/platform.hpp"
#include "logger.hpp"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Toollibs {

// =========================
// SAFE TIME FORMATTER
// =========================
static std::string GetTime()
{
    std::time_t now = std::time(nullptr);

    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%H:%M:%S");

    return oss.str();
}

// =========================
// MAIN LOGGER
// =========================
void Logger::Log(LogLevel level, const std::string& message)
{
    std::string levelText = "UNKNOWN";

    switch (level)
    {
        case LogLevel::Info:    levelText = "INFO";    break;
        case LogLevel::Warning: levelText = "WARNING"; break;
        case LogLevel::Error:   levelText = "ERROR";   break;
        case LogLevel::Debug:   levelText = "DEBUG";   break;
        default: break;
    }

    std::cout
        << "[" << GetTime() << "] "
        << "[" << levelText << "] "
        << message
        << std::endl;
}

// =========================
// WRAPPERS
// =========================
void Logger::Info(const std::string& message)
{
    Log(LogLevel::Info, message);
}

void Logger::Warning(const std::string& message)
{
    Log(LogLevel::Warning, message);
}

void Logger::Error(const std::string& message)
{
    Log(LogLevel::Error, message);
}

void Logger::Debug(const std::string& message)
{
    Log(LogLevel::Debug, message);
}

} // namespace Toollibs