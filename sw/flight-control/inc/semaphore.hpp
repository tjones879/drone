#pragma once
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/semphr.h>
#include <FreeRTOS/timers.h>

bool pdToBoolean(BaseType_t val);

/**
 * @brief SemaphoreHandle provides a weak RAII interface for taking
 *        and giving semaphores in FreeRTOS.
 *
 * Note that SemaphoreHandle does not obtain ownership of the semaphore
 * and will not handle allocation or deallocation of the object.
 */
class SemaphoreHandle
{
    SemaphoreHandle_t *semaphore;

public:
    SemaphoreHandle(SemaphoreHandle_t *handle, TickType_t ticksToWait);
    SemaphoreHandle(SemaphoreHandle &&other);
    SemaphoreHandle &operator=(SemaphoreHandle &&other);
    ~SemaphoreHandle();

    SemaphoreHandle(const SemaphoreHandle &other) = delete;
    SemaphoreHandle &operator=(const SemaphoreHandle &other) = delete;
};

/**
 * @brief A C++ wrapper around the BinarySemaphore provided by FreeRTOS.
 *
 * Note that BinarySemaphore expresses strict ownership of semaphore object
 * itself rather than the value it represents. A new semaphore object will
 * be allocated with each construction of a BinarySemaphore object.
 */
class BinarySemaphore
{
    SemaphoreHandle_t semaphore;
    StaticSemaphore_t staticBuffer;

public:
    BinarySemaphore();
    ~BinarySemaphore();
    bool take(TickType_t blockTime = portMAX_DELAY);
    bool give();
    bool giveFromISR(BaseType_t *taskWoken);
    SemaphoreHandle getRAII(TickType_t blockTime = portMAX_DELAY);

private:
    BinarySemaphore(const BinarySemaphore &) = delete;
    BinarySemaphore &operator=(const BinarySemaphore &) = delete;
};
