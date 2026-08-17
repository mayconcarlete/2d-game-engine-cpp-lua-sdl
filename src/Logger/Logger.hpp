#pragma once

#include <string>
#include <vector>

enum class LoggerType {
    LOGGER_INFO,
    LOGGER_WARN,
    LOGGER_ERROR
};

struct LoggerEntry {
    LoggerType type;
    std::string message;
};

class Logger {
    public:
        static std::vector<LoggerEntry> messages;
        static void Info(const std::string& message);
        static void Error(const std::string& message);
};