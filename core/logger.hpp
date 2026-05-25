#pragma once

#include <string>

namespace Toollibs {

    enum class LogLevel {
        Info,
        Warning,
        Error,
        Debug
    };

    class Logger {
    public:
        static void Log(LogLevel level, const std::string& message);

        static void Info(const std::string& message);
        static void Warning(const std::string& message);
        static void Error(const std::string& message);
        static void Debug(const std::string& message);
    };

}
