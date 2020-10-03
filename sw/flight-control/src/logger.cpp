#include "logger.hpp"
#include <cstring>
#include <memory>
#include <stdint.h>

static int semihost_write(uint32_t fh, const char *buffer, unsigned int len);

void Logger::DEBUG(const char *str)
{
    log(str);
}

void Logger::WARN(const char *str)
{
    log(str);
}

void Logger::INFO(const char *str)
{
    log(str);
}

void Logger::FATAL(const char *str)
{
    log(str);
}

void Logger::log(const char *str)
{
    if (!enable)
        return;

    // auto handle = mutex.getRAII();
    semihost_write(0x02, str, strlen(str));
}

enum class HostCommand : uint8_t
{
    OPEN = 0x1,
    CLOSE = 0x2,
    WRITE = 0x5,
    READ = 0x6,
    ISTTY = 0x9,
    EXIT = 0x18,
};

static int __semihost(HostCommand command, void *message)
{
    int command_i = static_cast<int>(command);
    __asm("mov r0, %[cmd] \n"
          "mov r1, %[msg] \n"
          "bkpt #0xAB \n"
          :
          : // Input operand list
          [cmd] "r"(command_i), [msg] "r"(message)
          : "r0", "r1", "memory");

    return 0;
}

static int semihost_write(uint32_t fh, const char *buffer, unsigned int len)
{
    if (len == 0)
        return 0;
    uint32_t args[3];
    args[0] = fh;
    args[1] = (uint32_t)buffer;
    args[2] = (uint32_t)len;
    return __semihost(HostCommand::WRITE, args);
}