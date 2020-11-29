#pragma once

#include <array>
#include <cassert>

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/message_buffer.h>

#include "logger.hpp"
#include "semaphore.hpp"

class StaticMessageBuffer
{
public:
    StaticMessageBuffer();
    StaticMessageBuffer(uint8_t *buff, size_t buffSize);
    size_t pull(uint8_t *dstBuff, size_t maxBufferSize);
    size_t push(uint8_t *srcBuff, size_t len);

    template <size_t buffLen>
    size_t push(std::array<uint8_t, buffLen> srcBuff);
private:
    uint8_t *buff_ptr;
    size_t buff_size;
    StaticMessageBuffer_t static_buff;
    MessageBufferHandle_t message_buffer;
    BinarySemaphore mutex;
};

template<size_t buffLen>
size_t StaticMessageBuffer::push(std::array<uint8_t, buffLen> srcBuffer)
{
    assert(buff_ptr != NULL && buff_size != 0 && message_buffer != NULL);
    mutex.take();
    Logger::get().DEBUG((const char *)srcBuffer.data());
    auto size = xMessageBufferSend(message_buffer, (void *)srcBuffer.data(), buffLen, 0);
    mutex.give();
    return size;
}