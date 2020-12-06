#pragma once

#include <stdint.h>

#include "message_buffer.hpp"

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/stream_buffer.h>

#define GPS_BUFFER_SIZE 256
#define MAX_NMEA_LENGTH 82

extern uint8_t gpsBufferSpace[GPS_BUFFER_SIZE];
extern StaticMessageBuffer gpsBuffer;
extern TaskHandle_t usart2_isr_task;

extern std::array<uint8_t, MAX_NMEA_LENGTH> nmeaSentence;
extern size_t pos;

void GpsTask(void *parameters);
