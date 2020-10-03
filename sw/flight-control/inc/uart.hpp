#pragma once
#include "logger.hpp"
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>

extern volatile int received;

class UartDev
{
public:

    UartDev(uint32_t device) : dev(device), dataReg(USART1_DR)
    {
        rcc_periph_clock_enable(RCC_GPIOA);
        rcc_periph_clock_enable(RCC_USART1);
        rcc_periph_clock_enable(RCC_AFIO);
        rcc_periph_clock_enable(RCC_DMA1);

        gpio_set_mode(GPIOB,
                      GPIO_MODE_INPUT,
                      GPIO_CNF_INPUT_FLOAT,
                      GPIO_USART1_RX);

        usart_set_baudrate(USART1, 9600);
        usart_set_databits(USART1, 8);
        usart_set_stopbits(USART1, USART_STOPBITS_1);
        usart_set_parity(USART1, USART_PARITY_NONE);
        usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
        usart_set_mode(USART1, USART_MODE_RX);

        usart_enable(USART1);

        nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
        nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);
    }

    UartDev(const UartDev &) = delete;
    UartDev &operator=(const UartDev &) = delete;
    UartDev(UartDev &&) = delete;
    UartDev &operator=(UartDev &&) = delete;

    uint8_t read_data_block()
    {
        // Logger::get().DEBUG("READING");
        return usart_recv_blocking(USART1);
    }

    void enable_circ_dma_rx()
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_GIF);
        dma_channel_reset(DMA1, DMA_CHANNEL5);

        nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
        nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);

        dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)&USART1_DR);
        dma_set_read_from_peripheral(DMA1, DMA_CHANNEL5);

        dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
        dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);

        dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_VERY_HIGH);

        dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL5);
        dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
        dma_enable_circular_mode(DMA1, DMA_CHANNEL5);

        dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)this->fifo);
        dma_set_number_of_data(DMA1, DMA_CHANNEL5, size);

        dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);
        dma_enable_channel(DMA1, DMA_CHANNEL5);

        usart_enable_rx_dma(USART1);
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
};

