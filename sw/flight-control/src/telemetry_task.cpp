#include "telemetry_task.hpp"


#include "messages.hpp"
#include "uart.hpp"

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>

uint8_t telemBufferSpace[GPS_MESSAGE_BUFFER_SIZE_BYTES];
StaticMessageBuffer telemetryDownlinkBuffer(telemBufferSpace, sizeof(telemBufferSpace));
TaskHandle_t dma1_channel4_task = NULL;

void TelemetryDownlinkTask(void *parameters)
{
    dma1_channel4_task = xTaskGetCurrentTaskHandle();
    auto dma_dev = dma::DMA(dma::Device(DMA1), dma::Channel(DMA_CHANNEL4),
                            dma::Priority::HIGH);
    UartDev tm_downlink(USART1, UartMode::TX, std::move(dma_dev), 115200);

    TickType_t lastWakeTime;
    const TickType_t frequency = 10;
    lastWakeTime = xTaskGetTickCount();

    #ifdef DEBUG_FLAG
    std::array<uint8_t, 16> taskName{"TM_DOWN"};
    auto expectedCurrentTime = lastWakeTime + frequency;
    #endif

    uint8_t rxGpsBuff[64];
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
            tm_downlink.enable_circ_dma_tx(rxGpsBuff, receiveSize);
            ulTaskNotifyTake(true, portMAX_DELAY);
        }
        //vTaskDelayUntil(&lastWakeTime, frequency);
    }
}

extern "C" {
void dma1_channel4_isr(void)
{
    BaseType_t hi_prio_task_woken = pdFALSE;
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL4, DMA_HTIF)) {
        //Logger::get().WARN("CHANNEL 4 HTIF ISR\n");
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL4, DMA_HTIF);
    }

    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL4, DMA_TCIF)) {
        //Logger::get().WARN("CHANNEL 4 TCIF ISR\n");
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL4, DMA_TCIF);

        // Clean up after the DMA interrupt that was just triggered.
        dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);
        dma_channel_reset(DMA1, DMA_CHANNEL4);

        vTaskNotifyGiveFromISR(dma1_channel4_task, &hi_prio_task_woken);
        portYIELD_FROM_ISR(hi_prio_task_woken);
    }
}
}