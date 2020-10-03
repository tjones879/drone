#include "logger.hpp"
#include "mpu6050.hpp"
#include "uart.hpp"
#include <FreeRTOS/FreeRTOS.h>
#include <libopencm3/cm3/cortex.h>
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

volatile int received = 0;

extern "C"
{
    void _fini(void);
}

void _fini(void) {}

void platform_setup()
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

void toggle_led()
{
    gpio_toggle(GPIOC, GPIO13);
}

int main()
{
    platform_setup();
    // Logger::get().INFO("Hello World");

    UartDev uart1(0);
    uart1.dma_read();
    while (1)
    {
        if (received)
        {
            //Logger::get().WARN("RECEIVED\n");
            received = 0;
            toggle_led();
        }
    }

    /*
    MPU6050 mpu6050(mpu::I2CAddr::LOW, DMA(DMA1, 5));


    if (mpu6050.testConnection())
        Logger::get().INFO("WHOAMI GOOD\n");
    else
        Logger::get().WARN("WHOAMI BAD\n");

    mpu6050.power.set_bits<0>();
    mpu6050.accelRange.set_bits<mpu::AccelRange::G_2>();
    mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::DISABLE)>();
    mpu6050.userControl.set_bits<mpu::UserControl::FIFO_RESET>();
    mpu6050.userControl.set_bits<mpu::UserControl::FIFO_EN>();
    mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN)>();

    uint8_t fifo_en = mpu6050.fifoEnable.get_bits();
    if (fifo_en & static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN) != 
        static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN))
    {
        char enable[64];
        snprintf(enable, 64, "FIFO_EN FAILED: %hu (expected: %hu)\n", fifo_en | static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN), static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN));
        Logger::get().WARN(enable);
    }

    auto tmpA = static_cast<mpu::AccelRange>(mpu6050.accelRange.get_bits());
    switch (tmpA) {
    case mpu::AccelRange::G_2:
        Logger::get().WARN("2G\n");
        break;
    case mpu::AccelRange::G_16:
        Logger::get().WARN("16G\n");
        break;
    case mpu::AccelRange::G_8:
        Logger::get().WARN("8G\n");
        break;
    case mpu::AccelRange::G_4:
        Logger::get().WARN("4G\n");
        break;
    }

    const uint16_t buffLen = 1024;
    uint8_t buff[buffLen];
    uint16_t continued = 0;
    while (1) {

        uint32_t vals[18];
        const uint16_t fifo_count = mpu6050.getFifoCount();
        if (fifo_count < 256)
        {
            continued++;
            if (continued > 5000)
            {
                toggle_led();
                Logger::get().WARN("CONTINUED\n");
                continued -= 5000;
            }
            continue;
        }

        mpu6050.readFifo(buff, std::min(fifo_count, buffLen));

        //for (auto i = 0; i < 18 * (fifo_count / 18); i++)
        for (auto i = 0; i < fifo_count; i++)
        {
            vals[i % 18] = mpu6050.fifoRW.get_bits();
            if (i % 18 == 0)
            {
                char acc[64];
                uint16_t x = vals[0] << 8 | vals[1];
                uint16_t y = vals[2] << 8 | vals[3];
                uint16_t z = vals[4] << 8 | vals[5];
                snprintf(acc, 64, "accel = <%u, %u, %u>\n",
                         x, y, z);
                Logger::get().WARN(acc);
            }
        }

        uint16_t acc_xh = mpu6050.accelOutXH.get_bits();
        uint16_t acc_xl = mpu6050.accelOutXL.get_bits();
        uint16_t acc_yh = mpu6050.accelOutYH.get_bits();
        uint16_t acc_yl = mpu6050.accelOutYL.get_bits();
        uint16_t acc_zh = mpu6050.accelOutZH.get_bits();
        uint16_t acc_zl = mpu6050.accelOutZL.get_bits();
        char acc[64];
        snprintf(acc, 64, "accel = <%hu %hu, %hu %hu, %hu %hu>\n",
                 acc_xh, acc_xl, acc_yh, acc_yl, acc_zh, acc_zl);
        Logger::get().WARN(acc);
    }
        */
    uint32_t counter = 0;
    while (1)
    {
        toggle_led();
        counter++;
        if (counter >= 1019)
            counter -= 50;
        else if (counter % 13)
            counter += 5;
        asm("nop");
    }
}

extern "C" {
void dma1_channel5_isr(void)
{
    //Logger::get().WARN("ISR\n");
    received = 1;
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_HTIF)) {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_HTIF);
    }

    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TCIF)) {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_TCIF);
    }
    /*
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_GIF);
        received = 1;

        usart_disable(USART1);
        dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);
        dma_channel_reset(DMA1, DMA_CHANNEL5);
        //usart_disable_rx_dma(USART1);
    }
    */
}
}
/*
            NEO-6M
*/
