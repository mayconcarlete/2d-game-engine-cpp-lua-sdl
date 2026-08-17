#include <Logger/Logger.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <format>
#include <string>

namespace {
    constexpr auto GREEN = "\033[32m";
    constexpr auto RED = "\033[31m";
    constexpr auto RESET = "\033[0m";

    std::chrono::local_time<std::chrono::milliseconds> Now() {
        const auto now = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());

        const std::time_t seconds = std::chrono::system_clock::to_time_t(now);
        std::tm local{};
        localtime_r(&seconds, &local);

        const std::chrono::seconds offset{local.tm_gmtoff};
        return std::chrono::local_time<std::chrono::milliseconds>{(now + offset).time_since_epoch()};
    }
}

std::vector<LoggerEntry> Logger::messages;

void Logger::Info(const std::string& message){
    const auto entry = std::format("[INFO] - {:%Y-%m-%d %H:%M:%S} - {}", Now(), message);
    messages.push_back({LoggerType::LOGGER_INFO, entry});
    std::cout << GREEN << entry << RESET << "\n";
}

void Logger::Error(const std::string& message){
    const auto entry = std::format("[ERROR] - {:%Y-%m-%d %H:%M:%S} - {}", Now(), message);
    messages.push_back({LoggerType::LOGGER_ERROR, entry});
    std::cout << RED << entry << RESET << "\n";
}