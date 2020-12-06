#pragma once

#include <stdint.h>

#include "message_buffer.hpp"

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/stream_buffer.h>

#define TELEM_BUFFER_SIZE 128

extern uint8_t telemBufferSpace[TELEM_BUFFER_SIZE];
extern StaticMessageBuffer telemetryDownlinkBuffer;
extern TaskHandle_t dma1_channel4_task;

void TelemetryDownlinkTask(void *parameters);
extern "C" void dma1_channel4_isr(void);
