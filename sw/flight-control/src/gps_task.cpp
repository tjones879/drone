#include "gps_task.hpp"
#include "telemetry_task.hpp"
#include "messages.hpp"
#include "uart.hpp"

uint8_t gpsBufferSpace[GPS_BUFFER_SIZE];
StaticMessageBuffer gpsBuffer(gpsBufferSpace, sizeof(gpsBufferSpace));
TaskHandle_t usart2_isr_task = NULL;

std::array<uint8_t, MAX_NMEA_LENGTH> nmeaSentence;
size_t pos = 0;

void GpsTask(void *parameters)
{
    usart2_isr_task = xTaskGetCurrentTaskHandle();
    auto dma_dev = dma::DMA();
    UartDev gps_rx(USART2, UartMode::RX, std::move(dma_dev), 9600);
    const portTickType frequency = 10;
    std::array<uint8_t, 82> localNmea;


    for (;;)
    {
        /*
        uint8_t buff[16];
        buff[16] = 0x00;
        for (size_t i = 0; i < sizeof(buff) - 1; i++)
            buff[i] = gps_rx.read_data_block();
        */
        size_t rxSize = gpsBuffer.pull(&localNmea[0], sizeof(localNmea), portMAX_DELAY);
        
        telemetryDownlinkBuffer.push(&localNmea[0], rxSize);
        //Logger::get().WARN((char *)&localNmea[0]);
    }
}

extern "C" 
{
void usart2_isr(void)
{
    volatile uint32_t reg;
    do {
        reg = USART_SR(USART2);
        if (reg & USART_SR_RXNE)
        {
            nmeaSentence[pos++] = usart_recv_blocking(USART2);

            if (pos >= sizeof(nmeaSentence))
                Logger::get().WARN("\n\nMAXLEN\n\n");

            if (pos >= sizeof(nmeaSentence) ||
                (nmeaSentence[pos - 1] == '\n' && 
                 nmeaSentence[pos - 2] == '\r'))
            {
                gpsBuffer.push(&nmeaSentence[0], pos);
                pos = 0;
            }
        }
    } while (reg & USART_SR_RXNE);

    /*
    if (wake_task)
    {
        //vTaskNotifyGiveFromISR(usart2_isr_task, &wake_task);
        portYIELD_FROM_ISR(wake_task);
    }
    */
}
}
