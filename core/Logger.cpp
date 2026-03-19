#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>

class Logger {
private:
    std::mutex log_mutex;

public:
    enum Level { INFO, WARNING, ERROR };

    void log(Level level, const std::string& message) {
        std::lock_guard<std::mutex> lock(log_mutex);

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::cout << "[" << std::put_time(std::localtime(&time), "%F %T") << "] ";

        switch (level) {
            case INFO: std::cout << "[INFO] "; break;
            case WARNING: std::cout << "[WARN] "; break;
            case ERROR: std::cout << "[ERROR] "; break;
        }

        std::cout << message << std::endl;
    }
};

#endif
