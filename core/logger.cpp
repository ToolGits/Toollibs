#include "logger.hpp"
#include "platform.hpp"

#include <iostream>
#include <ctime>

namespace Toollibs {

    static std::string GetTime()
    {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        char buffer[9];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);

        return buffer;
    }

    void Logger::Log(LogLevel level, const std::string& message)
    {
        std::string levelText;

        switch (level) {
            case LogLevel::Info:
                levelText = "INFO";
                break;

            case LogLevel::Warning:
                levelText = "WARNING";
                break;

            case LogLevel::Error:
                levelText = "ERROR";
                break;

            case LogLevel::Debug:
                levelText = "DEBUG";
                break;
        }

        std::cout
            << "[" << GetTime() << "] "
            << "[" << levelText << "] "
            << message
            << std::endl;
    }

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

}
