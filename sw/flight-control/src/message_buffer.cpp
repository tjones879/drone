#include "message_buffer.hpp"
#include <cassert>
#include "logger.hpp"


StaticMessageBuffer::StaticMessageBuffer()
    : buff_ptr(NULL), buff_size(0),
      message_buffer(NULL) {}

StaticMessageBuffer::StaticMessageBuffer(uint8_t *buff, size_t buffSize)
        : buff_ptr(buff), buff_size(buffSize),
          message_buffer(NULL)
{
    message_buffer = xMessageBufferCreateStatic(buff_size, buff_ptr, &static_buff);
}

size_t StaticMessageBuffer::pull(uint8_t *dstBuffer, size_t maxBufferSize)
{
    assert(buff_ptr != NULL && buff_size != 0 && message_buffer != NULL);
    return xMessageBufferReceive(message_buffer, (void *)dstBuffer,
                                 maxBufferSize, 0);
}

size_t StaticMessageBuffer::push(uint8_t *srcBuffer, size_t len)
{
    assert(buff_ptr != NULL && buff_size != 0 && message_buffer != NULL);
    return xMessageBufferSend(message_buffer, (void *)srcBuffer, len, 0);
}