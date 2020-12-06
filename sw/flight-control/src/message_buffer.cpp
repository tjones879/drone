#include "message_buffer.hpp"


StaticMessageBuffer::StaticMessageBuffer()
    : buff_ptr(NULL), buff_size(0),
      message_buffer(NULL) {}

StaticMessageBuffer::StaticMessageBuffer(uint8_t *buff, size_t buffSize)
        : buff_ptr(buff), buff_size(buffSize),
          message_buffer(NULL)
{
    message_buffer = xMessageBufferCreateStatic(buff_size, buff_ptr, &static_buff);
}

size_t StaticMessageBuffer::pull(uint8_t *dstBuffer, size_t maxBufferSize, size_t waitTime)
{
    assert(buff_ptr != NULL && buff_size != 0 && message_buffer != NULL);
    r_mutex.take();
    auto size = xMessageBufferReceive(message_buffer, (void *)dstBuffer,
                                      maxBufferSize, waitTime);
    r_mutex.give();
    return size;
}

size_t StaticMessageBuffer::push(uint8_t *srcBuffer, size_t len)
{
    assert(buff_ptr != NULL && buff_size != 0 && message_buffer != NULL);
    w_mutex.take();
    auto size = xMessageBufferSend(message_buffer, (void *)srcBuffer, len, 0);
    w_mutex.give();
    return size;
}