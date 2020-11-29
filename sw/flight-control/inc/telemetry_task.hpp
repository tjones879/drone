#pragma once

#include <stdint.h>

#include "message_buffer.hpp"

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/stream_buffer.h>

#define GPS_MESSAGE_BUFFER_SIZE_BYTES 128

extern uint8_t telemBufferSpace[GPS_MESSAGE_BUFFER_SIZE_BYTES];
extern StaticMessageBuffer telemetryDownlinkBuffer;

void TelemetryDownlinkTask(void *parameters);
