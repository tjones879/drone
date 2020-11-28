#include "semaphore.hpp"

SemaphoreHandle::SemaphoreHandle(SemaphoreHandle_t *handle,
                                 TickType_t ticksToWait)
  : semaphore(handle)
{
    xSemaphoreTake(*semaphore, ticksToWait);
}

SemaphoreHandle::SemaphoreHandle(SemaphoreHandle &&other)
{
    semaphore = other.semaphore;
    other.semaphore = nullptr;
}

SemaphoreHandle &SemaphoreHandle::operator=(SemaphoreHandle &&other)
{
    semaphore = other.semaphore;
    other.semaphore = nullptr;
}

SemaphoreHandle::~SemaphoreHandle()
{
    if (semaphore) {
        xSemaphoreGive(*semaphore);
        semaphore = nullptr;
    }
}

BinarySemaphore::BinarySemaphore()
{
    semaphore = xSemaphoreCreateBinaryStatic(&staticBuffer);
    give();
}

BinarySemaphore::~BinarySemaphore()
{
    vSemaphoreDelete(semaphore);
}

bool BinarySemaphore::take(TickType_t blockTime)
{
    auto result = xSemaphoreTake(semaphore, blockTime);
    return pdToBoolean(result);
}

SemaphoreHandle BinarySemaphore::getRAII(TickType_t blockTime)
{
    return SemaphoreHandle(&semaphore, blockTime);
}

bool BinarySemaphore::give()
{
    auto result = xSemaphoreGive(semaphore);
    return pdToBoolean(result);
}

bool BinarySemaphore::giveFromISR(BaseType_t *taskWoken)
{
    return false;
}

bool pdToBoolean(BaseType_t val)
{
    if (val == pdTRUE)
        return true;
    else
        return false;
}