#pragma once

#include "logger.hpp"
#include "util.hpp"
#include <stdio.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>

class GpioPin
{
public:
    GpioPin(uint32_t gpio_port, uint32_t gpio_pin, uint32_t mode, uint32_t function)
        : port(gpio_port), pin(gpio_pin)
    {
        gpio_set_mode(port, mode, function, pin);
    }

    GpioPin(GpioPin &&) = default;
    GpioPin &operator=(GpioPin &&) = default;
    GpioPin(const GpioPin &) = delete;
    GpioPin &operator=(const GpioPin &) = delete;

    void set()
    {
        gpio_set(port, pin);
    }

    void clear()
    {
        gpio_clear(port, pin);
    }

private:
    uint32_t port;
    uint32_t pin;
};
