#include "logger.hpp"
#include "mpu6050.hpp"
#include <FreeRTOS/FreeRTOS.h>
#include <libopencm3/cm3/cortex.h>
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <stdlib.h>

extern "C"
{
    void _fini(void);
}

void _fini(void) {}

void platform_setup()
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(
    GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

void toggle_led()
{
    gpio_toggle(GPIOC, GPIO13);
}

int main()
{
    platform_setup();
    // Logger::get().INFO("Hello World");
    MPU6050 mpu6050(mpu::I2CAddr::LOW);

    if (mpu6050.testConnection())
        Logger::get().INFO("Good");
    else
        Logger::get().WARN("Bad");

    while (1) {
        toggle_led();
        for (int i = 0; i < 1000000; i++)
            __asm("nop");
    }
}