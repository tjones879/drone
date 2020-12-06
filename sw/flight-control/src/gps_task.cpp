#include "gps_task.hpp"
#include "telemetry_task.hpp"
#include "messages.hpp"
#include "uart.hpp"
#include <optional>

uint8_t gpsBufferSpace[GPS_BUFFER_SIZE];
StaticMessageBuffer gpsBuffer(gpsBufferSpace, sizeof(gpsBufferSpace));
TaskHandle_t usart2_isr_task = NULL;

std::array<uint8_t, MAX_NMEA_LENGTH> nmeaSentence;
size_t pos = 0;

uint8_t fromHex(char hex)
{
    if (hex >= 'A' && hex <= 'F')
        return hex - 'A' + 10;
    else if (hex >= 'a' && hex <= 'f')
        return hex - 'a' + 10;
    else
        return hex - '0';
}

std::optional<messages::GNSS::InvalidSentence> verifyChecksum(uint8_t *buff, size_t buffLen)
{
    if (buffLen == 0 || !buff)
        return messages::GNSS::InvalidSentence{true, 0, 0};

    // Verify that we start with the $ delimiter
    if (buff[0] != '$')
        return messages::GNSS::InvalidSentence{true, 0, 0};

    size_t pos = 1;
    uint8_t calculated = 0;
    while (pos < buffLen)
    {
        if (buff[pos] == '*')
            break;

        calculated ^= buff[pos];
        pos += 1;
    }

    // We went through the entire buffer without seeing the end delimiter
    // The GPS sentence should always terminate with |*|A|B|CR|LF
    // and pos should be the location of *
    if (pos > buffLen - 5)
        return messages::GNSS::InvalidSentence{true, 0, 0};

    // We have not identified any framing errors. Check against the reported sum.
    pos += 1; // Skip over the * and the next two characters should be hex
    uint8_t reported = fromHex(buff[pos]) * 16 + fromHex(buff[pos + 1]);
    if (reported != calculated)
        return messages::GNSS::InvalidSentence{false, calculated, reported};

    return {};
}

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
        auto error = verifyChecksum(&localNmea[0], rxSize);
        
        if (!error)
            telemetryDownlinkBuffer.push(&localNmea[0], rxSize);
        else
            telemetryDownlinkBuffer.push(error->serialize());

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
