#pragma once

#include <cstdint>
#include <libopencm3/stm32/dma.h>

namespace dma {
enum class Size : std::uint32_t
{
    BYTE = DMA_CCR_PSIZE_8BIT,
    HALF_WORD = DMA_CCR_PSIZE_16BIT,
    FULL_WORD = DMA_CCR_PSIZE_32BIT,
};

enum class Priority : std::uint32_t
{
    LOW = DMA_CCR_PL_LOW,
    MEDIUM = DMA_CCR_PL_MEDIUM,
    HIGH = DMA_CCR_PL_HIGH,
    VERY_HIGH = DMA_CCR_PL_VERY_HIGH
};

} // namespace dma

class DMA
{
public:
    DMA(std::uint32_t dev, std::uint8_t channel) : dev(dev), channel(channel) {}

    void enableCircularMode() { dma_enable_circular_mode(dev, channel); }

    void enable() { dma_enable_channel(dev, channel); }

    void disable() { dma_disable_channel(dev, channel); }

    void setNumData(std::uint16_t data)
    {
        dma_set_number_of_data(dev, channel, data);
    }

    void setPriority(dma::Priority priority)
    {
        dma_set_priority(dev, channel, static_cast<std::uint32_t>(priority));
    }

    void setPeripheralAddress(std::uint32_t address)
    {
        dma_set_peripheral_address(dev, channel, address);
    }

    void setPeripheralSize(dma::Size size)
    {
        dma_set_peripheral_size(dev, channel, static_cast<std::uint32_t>(size));
    }

    void read() {}

private:
    std::uint32_t dev;
    std::uint8_t channel;
};