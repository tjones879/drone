#pragma once
#include "logger.hpp"
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include "dma.hpp"

extern volatile int received;

enum class UartMode : std::uint32_t
{
    TX = USART_MODE_TX,
    RX = USART_MODE_RX,
    TX_RX = USART_MODE_TX_RX,
};

class UartDev
{
public:

    UartDev(uint32_t device, const uint32_t data_reg, UartMode mode, dma::DMA &&dma_struct)
        : dev(device), dataReg(data_reg), dma_handle(std::move(dma_struct))
    {

        usart_set_baudrate(device, 115200);
        usart_set_databits(device, 8);
        usart_set_stopbits(device, USART_STOPBITS_1);
        usart_set_parity(device, USART_PARITY_NONE);
        usart_set_flow_control(device, USART_FLOWCONTROL_NONE);
        usart_set_mode(device, static_cast<uint32_t>(mode));

        usart_enable(device);
    }

    UartDev(const UartDev &) = delete;
    UartDev &operator=(const UartDev &) = delete;
    UartDev(UartDev &&) = delete;
    UartDev &operator=(UartDev &&) = delete;

    void write_data_block(uint8_t *data, uint32_t data_len)
    {
        for (auto i = 0; i < data_len; i++)
            usart_send_blocking(USART1, data[i]);
    }

    uint8_t read_data_block()
    {
        // Logger::get().DEBUG("READING");
        return usart_recv_blocking(USART1);
    }

    void enable_circ_dma_rx()
    {
        nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
        nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);

        dma_handle.setPeripheralAddress(dma::Address((uint32_t)&dataReg),
                                        dma::PeripheralSize::BYTE,
                                        false);
        dma_handle.setMemoryAddress(dma::Address((uint32_t)this->fifo),
                                    dma::MemorySize::BYTE,
                                    true);
        dma_handle.setRxMode(true);

        dma_handle.enableInterrupt(dma::Interrupt::TRANSFER_COMPLETE);
        dma_handle.enableChannel(dma::DataLength(size), true);

        usart_enable_rx_dma(dev);
    }

    void enable_circ_dma_tx(uint8_t *buffer, uint16_t full_buff_len)
    {
        dma_handle.enableChannel(dma::DataLength(full_buff_len), true);
        //dma_handle.enableIrq();
        dma_handle.setPeripheralAddress(dma::Address((uint32_t)&dataReg),
                                        dma::PeripheralSize::BYTE,
                                        false);
        dma_handle.setMemoryAddress(dma::Address((uint32_t)buffer),
                                    dma::MemorySize::BYTE,
                                    true);
        dma_handle.setRxMode(false);
        dma_handle.enableInterrupt(dma::Interrupt::TRANSFER_COMPLETE);
        usart_enable_tx_dma(dev);
    }

    void logDMAConfig()
    {
        uint32_t cr = DMA1_CCR5;
        if (cr & DMA_CCR_EN)
            Logger::get().WARN("EN, ");
        if (cr & DMA_CCR_TCIE)
            Logger::get().WARN("TCIE, ");
        if (cr & DMA_CCR_HTIE)
            Logger::get().WARN("HTIE, ");
        if (cr & DMA_CCR_TEIE)
            Logger::get().WARN("TEIE, ");
        if (cr & DMA_CCR_DIR)
            Logger::get().WARN("DIR, ");
        if (cr & DMA_CCR_CIRC)
            Logger::get().WARN("CIRC, ");
        if (cr & DMA_CCR_PINC)
            Logger::get().WARN("PINC, ");
        if (cr & DMA_CCR_MINC)
            Logger::get().WARN("MINC, ");
        Logger::get().WARN("\n");
    }

    void logDMAInt()
    {
        if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TCIF))
            Logger::get().WARN("UNSERVICED TCIF\n");
        if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TEIF))
            Logger::get().WARN("UNSERVICED TEIF\n");
        if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_HTIF))
            Logger::get().WARN("UNSERVICED HTIF\n");
        if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_GIF))
            Logger::get().WARN("UNSERVICED GIF\n");
    }

    const std::uint32_t dataReg;
    static const int size = 512;
    char fifo[size];
private:
    uint32_t dev;
    dma::DMA dma_handle;
};

