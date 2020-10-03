#pragma once
#include "logger.hpp"
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

class I2CDev
{
public:
    I2CDev(uint32_t device) : dev(device), dataReg(I2C2_DR)
    {
        rcc_periph_clock_enable(RCC_GPIOB);
        rcc_periph_clock_enable(RCC_I2C2);
        rcc_periph_clock_enable(RCC_AFIO);

        gpio_set_mode(GPIOB,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                      GPIO_I2C2_SCL | GPIO_I2C2_SDA);

        i2c_peripheral_disable(dev);
        i2c_reset(dev);
        I2C_CR1(dev) &= ~I2C_CR1_STOP;
        i2c_set_standard_mode(dev);

        /* APB1 is running at 36MHz. */
        i2c_set_clock_frequency(dev, I2C_CR2_FREQ_36MHZ);

        /* 400KHz - I2C Fast Mode */
        //i2c_set_fast_mode(dev);

        /*
         * fclock for I2C is 36MHz APB2 -> cycle time 28ns, low time at 400kHz
         * incl trise -> Thigh = 1600ns; CCR = tlow/tcycle = 0x1C,9;
         * Datasheet suggests 0x1e.
         */
        i2c_set_ccr(dev, 0x36);
        i2c_set_dutycycle(dev, I2C_CCR_DUTY_DIV2);
        i2c_set_ccr(dev, 180);

        /*
         * fclock for I2C is 36MHz -> cycle time 28ns, rise time for
         * 400kHz => 300ns and 100kHz => 1000ns; 300ns/28ns = 10;
         * Incremented by 1 -> 11.
         */
        // i2c_set_trise(dev, 0x0b);
        i2c_set_own_7bit_slave_address(I2C2, 0x23);

        i2c_peripheral_enable(dev);
    }

    I2CDev(const I2CDev &) = delete;
    I2CDev &operator=(const I2CDev &) = delete;
    I2CDev(I2CDev &&) = delete;
    I2CDev &operator=(I2CDev &&) = delete;

    void send_start_block()
    {
        // Logger::get().DEBUG("START");
        auto tmp = 0;
        while (I2C_SR2(dev) & I2C_SR2_BUSY) {
            tmp++;
            if (tmp > 500L) {
                resetI2CBug();
                break;
            }
        }
        I2C_SR1(dev) &= ~I2C_SR1_AF;
        i2c_clear_stop(dev);
        i2c_enable_ack(dev);
        i2c_send_start(dev);

        while (!((I2C_SR1(dev) & I2C_SR1_SB) &&
                 (I2C_SR2(dev) & (I2C_SR2_MSL | I2C_SR2_BUSY))))
            ;
    }

    void send_addr_block(uint8_t addr, bool read)
    {
        // Logger::get().DEBUG("ADDR");
        i2c_send_7bit_address(dev, addr, read);

        while (!(I2C_SR1(dev) & I2C_SR1_ADDR))
            ;
        /* {
        if (I2C_SR1(dev) & I2C_SR1_AF) {
            i2c_send_stop(dev);
            (void)I2C_SR1(dev);
            (void)I2C_SR2(dev);
            Logger::get().FATAL("ADDR FAILED");
            return;
        }
    }
    */
        (void)I2C_SR2(dev);
    }

    void send_data_block(uint8_t data)
    {
        // Logger::get().DEBUG("SEND DATA\n");
        i2c_send_data(dev, data);
        while (!(I2C_SR1(dev) & (I2C_SR1_BTF | I2C_SR1_TxE)))
            ;
        volatile auto tmp = I2C_SR1(dev);
        tmp |= I2C_SR2(dev);
    }

    uint8_t read_data_block()
    {
        // Logger::get().DEBUG("READING");
        uint32_t reg32 __attribute((unused));
        i2c_disable_ack(dev);

        while (!(I2C_SR1(dev) & I2C_SR1_RxNE))
            ;

        uint8_t data = i2c_get_data(dev);

        return data;
    }

    void read_data_blocks(uint8_t *buff, size_t buff_len)
    {
        uint32_t reg32 __attribute((unused));
        i2c_disable_ack(dev);

        while (!(I2C_SR1(dev) & I2C_SR1_RxNE))
            ;

        for (auto i = 0; i < buff_len; i++)
        {
            buff[i] = i2c_get_data(dev);
        }
    }

    void resetI2CBug()
    {
        // Process detailed in errata sheet
        // Logger::get().DEBUG("RESETTING");
        i2c_peripheral_disable(dev);
        gpio_set_mode(GPIOB,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_OPENDRAIN,
                      GPIO_I2C2_SCL | GPIO_I2C2_SDA);
        gpio_set(GPIOB, GPIO_I2C2_SCL | GPIO_I2C2_SDA);
        volatile auto tmp = GPIO_IDR(GPIOB);
        gpio_clear(GPIOB, GPIO_I2C2_SDA);
        tmp = GPIO_IDR(GPIOB);
        gpio_clear(GPIOB, GPIO_I2C2_SCL);
        tmp = GPIO_IDR(GPIOB);
        gpio_set(GPIOB, GPIO_I2C2_SCL);
        tmp = GPIO_IDR(GPIOB);
        gpio_set(GPIOB, GPIO_I2C2_SDA);
        tmp = GPIO_IDR(GPIOB);
        gpio_set_mode(GPIOB,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                      GPIO_I2C2_SCL | GPIO_I2C2_SDA);
        I2C_CR1(dev) |= I2C_CR1_SWRST;
        I2C_CR1(dev) &= ~I2C_CR1_SWRST;
        i2c_set_standard_mode(dev);

        /* APB1 is running at 36MHz. */
        i2c_set_clock_frequency(dev, I2C_CR2_FREQ_36MHZ);

        /* 400KHz - I2C Fast Mode */
        i2c_set_fast_mode(dev);

        /*
         * fclock for I2C is 36MHz APB2 -> cycle time 28ns, low time at
         * 400kHz incl trise -> Thigh = 1600ns; CCR = tlow/tcycle = 0x1C,9;
         * Datasheet suggests 0x1e.
         */
        i2c_set_ccr(dev, 0x36);
        i2c_set_dutycycle(dev, I2C_CCR_DUTY_DIV2);
        i2c_set_ccr(dev, 180);

        /*
         * fclock for I2C is 36MHz -> cycle time 28ns, rise time for
         * 400kHz => 300ns and 100kHz => 1000ns; 300ns/28ns = 10;
         * Incremented by 1 -> 11.
         */
        // i2c_set_trise(dev, 0x0b);
        //i2c_set_own_7bit_slave_address(I2C2, 0x23);

        i2c_peripheral_enable(dev);
    }

    void send_stop() { i2c_send_stop(dev); }

    const std::uint32_t dataReg;

private:
    uint32_t dev;
};
