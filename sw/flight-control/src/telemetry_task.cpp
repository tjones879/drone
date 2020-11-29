#include "telemetry_task.hpp"


#include "messages.hpp"
#include "uart.hpp"

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>

uint8_t telemBufferSpace[GPS_MESSAGE_BUFFER_SIZE_BYTES];
StaticMessageBuffer telemetryDownlinkBuffer(telemBufferSpace, sizeof(telemBufferSpace));

void TelemetryDownlinkTask(void *parameters)
{
    auto dma_dev = dma::DMA(dma::Device(DMA1), dma::Channel(DMA_CHANNEL5),
                            dma::Priority::HIGH);
    UartDev tm_downlink(USART1, USART1_DR, UartMode::TX, std::move(dma_dev));

    TickType_t lastWakeTime;
    const TickType_t frequency = 10;
    lastWakeTime = xTaskGetTickCount();

    #ifdef DEBUG_FLAG
    std::array<uint8_t, 16> taskName{"TM_DOWN"};
    auto expectedCurrentTime = lastWakeTime + frequency;
    #endif

    uint8_t rxGpsBuff[32];
    for (;;)
    {
        #ifdef DEBUG_FLAG
        if (lastWakeTime > expectedCurrentTime)
        {
            // Log the fact that we failed to meet a deadline
            auto deadline = messages::SOFTWARE::MissedDeadline(taskName, lastWakeTime - expectedCurrentTime);
            tm_downlink.write_data_block(deadline.serialize());
        }
        expectedCurrentTime = lastWakeTime + frequency;
        #endif
        
        auto receiveSize = telemetryDownlinkBuffer.pull(rxGpsBuff, sizeof(rxGpsBuff));
        if (receiveSize)
        {
            tm_downlink.write_data_block(rxGpsBuff, receiveSize);
            //ulTaskNotifyTake(true, portMAX_DELAY)//;
        }
        vTaskDelayUntil(&lastWakeTime, frequency);
    }
}
