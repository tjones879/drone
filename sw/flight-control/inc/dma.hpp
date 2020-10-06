#pragma once

#include <cstdint>
#include <libopencm3/stm32/dma.h>
#include "util.hpp"

namespace dma {
enum class Device : std::uint32_t
{
    DMA_1 = DMA1,
    DMA_2 = DMA2
};

enum class PeripheralSize : std::uint32_t
{
    BYTE = DMA_CCR_PSIZE_8BIT,
    HALF_WORD = DMA_CCR_PSIZE_16BIT,
    FULL_WORD = DMA_CCR_PSIZE_32BIT,
};

enum class MemorySize : std::uint32_t
{
    BYTE = DMA_CCR_MSIZE_8BIT,
    HALF_WORD = DMA_CCR_MSIZE_16BIT,
    FULL_WORD = DMA_CCR_MSIZE_32BIT,
};

enum class Priority : std::uint32_t
{
    LOW = DMA_CCR_PL_LOW,
    MEDIUM = DMA_CCR_PL_MEDIUM,
    HIGH = DMA_CCR_PL_HIGH,
    VERY_HIGH = DMA_CCR_PL_VERY_HIGH
};

enum class Interrupt : std::uint32_t
{
    GLOBAL = DMA_GIF,
    TRANSFER_COMPLETE = DMA_TCIF,
    TRANSFER_HALF = DMA_HTIF,
    TRANSFER_ERROR = DMA_TEIF
};

using Address = StrongType<uint32_t>;
using DataLength = StrongType<uint32_t>;
using Channel = StrongType<uint8_t>;

class DMA
{
public:
    DMA(Device dev, Channel channel, Priority priority)
        : dev(static_cast<uint32_t>(dev)), channel(channel.get()),
          priority(static_cast<uint32_t>(priority))
    {
        dma_clear_interrupt_flags(this->dev, this->channel, DMA_GIF);
        dma_channel_reset(this->dev, this->channel);
        dma_set_priority(this->dev, this->channel, this->priority);
    }

    void enable(DataLength num_data, bool circular)
    {
        if (circular)
            dma_enable_circular_mode(dev, channel);

        dma_enable_channel(dev, channel);
    }

    void disable()
    {
        dma_disable_channel(dev, channel);
    }

    void setNumData(std::uint16_t data)
    {
        dma_set_number_of_data(dev, channel, data);
    }

    void enableInterrupt(Interrupt interrupt)
    {
        switch (interrupt)
        {
        case Interrupt::TRANSFER_COMPLETE:
            dma_enable_transfer_complete_interrupt(dev, channel);
            break;
        case Interrupt::TRANSFER_HALF:
            dma_enable_half_transfer_interrupt(dev, channel);
            break;
        case Interrupt::TRANSFER_ERROR:
            dma_enable_transfer_error_interrupt(dev, channel);
            break;
        }
    }

    void disableInterrupt(Interrupt interrupt)
    {
        switch (interrupt)
        {
        case Interrupt::TRANSFER_COMPLETE:
            dma_disable_transfer_complete_interrupt(dev, channel);
            break;
        case Interrupt::TRANSFER_HALF:
            dma_disable_half_transfer_interrupt(dev, channel);
            break;
        case Interrupt::TRANSFER_ERROR:
            dma_disable_transfer_error_interrupt(dev, channel);
            break;
        }
    }

    void clearInterrupt(Interrupt interrupt)
    {
        dma_clear_interrupt_flags(dev, channel, static_cast<uint32_t>(interrupt));
    }

    void setPeripheralAddress(Address addr, PeripheralSize size, bool increment)
    {
        dma_set_peripheral_address(dev, channel, addr.get());
        dma_set_peripheral_size(dev, channel, static_cast<std::uint32_t>(size));
        if (increment)
            dma_enable_peripheral_increment_mode(dev, channel);
        else
            dma_disable_peripheral_increment_mode(dev, channel);
    }

    void setMemoryAddress(Address addr, MemorySize size, bool increment)
    {
        dma_set_memory_address(dev, channel, addr.get());
        dma_set_memory_size(dev, channel, static_cast<std::uint32_t>(size));
        if (increment)
            dma_enable_memory_increment_mode(dev, channel);
        else
            dma_disable_memory_increment_mode(dev, channel);
    }

private:
    std::uint32_t dev;
    std::uint8_t channel;
    std::uint32_t priority;
};
} // namespace dma

