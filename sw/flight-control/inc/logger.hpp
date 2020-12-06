#pragma once
#include "semaphore.hpp"

class Logger
{
public:
    static Logger &get()
    {
        static Logger instance;
        return instance;
    }

    void DEBUG(const char *str);
    void WARN(const char *str);
    void INFO(const char *str);
    void FATAL(const char *str);

    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    void operator=(Logger const &) = delete;
    void operator=(Logger &&) = delete;

private:
    Logger() {}
    void log(const char *str);
    bool enable = true;
};
