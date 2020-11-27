#pragma once
#include "logger.hpp"
#include "util.hpp"
#include <stdio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>

namespace spi {

enum class Device : uint32_t
{
    DEV1 = SPI1,
    DEV2 = SPI2,
};

enum class Rate : uint32_t
{
    DIV_2 = SPI_CR1_BR_FPCLK_DIV_2,
    DIV_4 = SPI_CR1_BR_FPCLK_DIV_4,
    DIV_8 = SPI_CR1_BR_FPCLK_DIV_8,
    DIV_16 = SPI_CR1_BR_FPCLK_DIV_16,
    DIV_32 = SPI_CR1_BR_FPCLK_DIV_32,
    DIV_64 = SPI_CR1_BR_FPCLK_DIV_64,
    DIV_128 = SPI_CR1_BR_FPCLK_DIV_128,
    DIV_256 = SPI_CR1_BR_FPCLK_DIV_256,
};

enum class Polarity : uint32_t
{
    IDLE_LO = SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
    IDLE_HI = SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE,
};

enum class Phase : uint32_t
{
    A = SPI_CR1_CPHA_CLK_TRANSITION_1,
    B = SPI_CR1_CPHA_CLK_TRANSITION_2,
};

enum class FrameSize : uint32_t
{
    BYTE = SPI_CR1_DFF_8BIT,
    SHORT = SPI_CR1_DFF_16BIT,
};

enum class BitOrder : uint32_t
{
    MSB = SPI_CR1_MSBFIRST,
    LSB = SPI_CR1_LSBFIRST,
};
}

class SPIBus
{
public:
    SPIBus(spi::Device spi_dev, spi::Rate baudrate, spi::Polarity pol,
              spi::Phase phase, spi::FrameSize size, spi::BitOrder order)
        : dev(static_cast<uint32_t>(spi_dev))
    {
        spi_reset(dev);
        spi_disable(dev);
        spi_enable_software_slave_management(dev);
        spi_init_master(dev, static_cast<uint32_t>(baudrate),
                        static_cast<uint32_t>(pol), static_cast<uint32_t>(phase),
                        static_cast<uint32_t>(size), static_cast<uint32_t>(order));
        spi_enable(dev);
        spi_set_nss_high(dev);
    }

    SPIBus(const SPIBus &) = delete;
    SPIBus &operator=(const SPIBus &) = delete;
    SPIBus(SPIBus &&) = delete;
    SPIBus &operator=(SPIBus &&) = delete;

    uint16_t xfer(uint16_t addr)
    {
        gpio_clear(GPIOB, GPIO12);
        auto val = spi_xfer(dev, addr);
        gpio_set(GPIOB, GPIO12);
        return val;
    }

    uint16_t read(uint8_t addr)
    {
        uint16_t real_addr = 0x80 | addr;
        real_addr <<= 8;
        spi_send(dev, real_addr);
        return spi_read(dev);
        /*
        uint16_t val = spi_xfer(dev, real_addr);
        return val;
        */
    }

    void write(uint8_t reg, uint8_t val)
    {
        uint16_t payload = reg;
        payload <<= 8;
        payload |= val;

        spi_xfer(dev, payload);
    }
private:
    uint32_t dev;
};
