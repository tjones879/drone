#pragma once

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/message_buffer.h>

class StaticMessageBuffer
{
public:
    StaticMessageBuffer();
    StaticMessageBuffer(uint8_t *buff, size_t buffSize);
    size_t pull(uint8_t *dstBuff, size_t maxBufferSize);
    size_t push(uint8_t *srcBuff, size_t len);
private:
    uint8_t *buff_ptr;
    size_t buff_size;
    StaticMessageBuffer_t static_buff;
    MessageBufferHandle_t message_buffer;
};