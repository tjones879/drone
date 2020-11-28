#include "logger.hpp"
#include "uart.hpp"
#include "spi.hpp"
#include "lsm9ds1.hpp"
#include "gpio.hpp"
#include "messages.hpp"

#include <libopencm3/cm3/cortex.h>
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/message_buffer.h>

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#define configASSERT ( x )     if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
#define GPS_MESSAGE_BUFFER_SIZE_BYTES 128

volatile int received = 0;
static uint8_t gpsMessageBuff[GPS_MESSAGE_BUFFER_SIZE_BYTES];
StaticMessageBuffer_t gpsStaticBuffer;
MessageBufferHandle_t gpsMessageBuffer;

extern "C"
{
    void _fini(void);
}

void _fini(void) {}

void platform_setup()
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_AFIO);
    rcc_periph_clock_enable(RCC_SPI2);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO13 | GPIO15);
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO14);

    gpio_set(GPIOB, GPIO12);
}

void toggle_led()
{
    gpio_toggle(GPIOC, GPIO13);
}

void LedFlashTask(void *parameters)
{
    portTickType lastWakeTime;
    const portTickType frequency = 1000;
    lastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        toggle_led();
        vTaskDelayUntil(&lastWakeTime, frequency);
    }
}

void TelemetryTask(void *parameters)
{
    //UartDev uart1(0, USART1_DR, dma::DMA(dma::Device(DMA1), dma::Channel(DMA_CHANNEL5),
    //                          dma::Priority::HIGH));
    uint8_t rxGpsBuff[16];
    for (;;)
    {
        size_t receiveSize = xMessageBufferReceive(gpsMessageBuffer,
                                                   (void *)rxGpsBuff,
                                                   sizeof(rxGpsBuff),
                                                   0);
        if (receiveSize)
        {

        }
    }
}

void GNSSTask(void *parameters)
{
    for (;;)
    {

    }
}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t task, char *taskName)
{
    for (;;)
    {
        continue;
    }
}

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **idleTaskTCBBuffer,
                                              StackType_t **idleTaskStackBuffer,
                                              uint32_t *idleTaskStackSize)
{
    static StaticTask_t idleTaskTCB;
    static StackType_t idleTaskStack[configMINIMAL_STACK_SIZE];
    *idleTaskTCBBuffer = &idleTaskTCB;
    *idleTaskStackBuffer = idleTaskStack;
    *idleTaskStackSize = configMINIMAL_STACK_SIZE;
}

int main()
{
    platform_setup();
    Logger::get().INFO("Hello World\n");
    gpsMessageBuffer = xMessageBufferCreateStatic(sizeof(gpsMessageBuff), gpsMessageBuff, &gpsStaticBuffer);


    xTaskCreate(LedFlashTask, "LED", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(TelemetryTask, "Telemetry", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();

    while (true)
    {}

    /*
    SPIBus spi(spi::Device::DEV2, spi::Rate::DIV_16, spi::Polarity::IDLE_HI,
               spi::Phase::A, spi::FrameSize::SHORT, spi::BitOrder::MSB);
    GpioPin accel_cs(GPIOB, GPIO12, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
    GpioPin mag_cs(GPIOB, GPIO9, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL);
    accel_cs.set();
    */


    /*
    Lsm9ds1 imu(spi, std::move(accel_cs), std::move(mag_cs));
    imu.initAccel();
    imu.initGyro();
    imu.initFifo(8);

    while(true)
    {
        uint16_t acc[32 * 6 + 1];
        uint8_t num_samples = 32;
        imu.readFifo(acc, num_samples);
        uart1.write_data_block((uint8_t *)acc, num_samples * 12);
    }
    */

    /*
    SPIBus spi(spi::Device::DEV2, spi::Rate::DIV_16, spi::Polarity::IDLE_HI,
                  spi::Phase::A, spi::FrameSize::SHORT, spi::BitOrder::MSB);
    uint16_t val = spi.read(0x0F);
    char log[8];
    snprintf(log, 8, "%x\n", val);
    Logger::get().INFO(log);
    val = spi.read(0x1E);
    snprintf(log, 8, "%x\n", val);
    Logger::get().INFO(log);
    uart1.enable_circ_dma_rx();
    while (1)
    {
        if (received)
        {
            //Logger::get().WARN("RECEIVED\n");
            received = 0;
            toggle_led();
        }
    }

    MPU6050 mpu6050(mpu::I2CAddr::LOW);
    bool good = mpu6050.testConnection();
    if (!good)
        mpu6050.power.set_bits<0>();
    while (!good)
    {
        Logger::get().WARN("WHOAMI BAD\n");
        good = mpu6050.testConnection();
    }
    mpu6050.power.set_bits<0x80>();
    toggle_led();
    good = mpu6050.testConnection();
    for (unsigned i = 0; i < 10000000; i++)
        asm("nop");
    if (!good)
        mpu6050.power.set_bits<0>();
    while (!good)
    {
        Logger::get().WARN("WHOAMI BAD\n");
        good = mpu6050.testConnection();
    }

    mpu6050.power.set_bits<0>();
    //mpu6050.signal_reset.set_bits<0x07>(); // Reset gyro, acc, temp
    mpu6050.sampleRate.set_bits<0x01>();
    mpu6050.power.set_bits<3>(); // Set gyro x as PLL
    mpu6050.accelRange.set_bits<mpu::AccelRange::G_2>();
    mpu6050.gyroRange.set_bits<mpu::GyroRange::DEG_250>();
    mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::DISABLE)>();
    mpu6050.userControl.set_bits<mpu::UserControl::FIFO_RESET>();
    mpu6050.userControl.set_bits<mpu::UserControl::FIFO_EN>();
    //mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN)>();
    mpu6050.fifoEnable.set_bits<0x78>();

    uint8_t fifo_en = mpu6050.fifoEnable.get_bits();
    if (fifo_en & static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN) !=
        static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN))
    {
        char enable[64];
        snprintf(enable, 64, "FIFO_EN FAILED: %hu (expected: %hu)\n", fifo_en | static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN), static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN));
        Logger::get().WARN(enable);
    }

    auto tmpA = static_cast<mpu::AccelRange>(mpu6050.accelRange.get_bits());
    char accel[16];
    switch (tmpA) {
    case mpu::AccelRange::G_2:
        Logger::get().WARN("2G\n");
        break;
    case mpu::AccelRange::G_4:
        Logger::get().WARN("4G\n");
        break;
    case mpu::AccelRange::G_8:
        Logger::get().WARN("8G\n");
        break;
    case mpu::AccelRange::G_16:
        Logger::get().WARN("16G\n");
        break;
    default:
        snprintf(accel, 16, "%x\n", tmpA);
        Logger::get().WARN("UNKNOWN ACCEL\n");
        Logger::get().WARN(accel);
    }

    const uint16_t buffLen = 2048;
    uint8_t buff[buffLen];
    uint16_t continued = 0;
    while (1) {
        uint16_t fifoDepth = mpu6050.getFifoCount();
        if (mpu6050.intSource.get_bits() & static_cast<uint8_t>(mpu::IntSources::FIFO_OFLOW) ||
            fifoDepth > 1024)
        {
            mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::DISABLE)>();
            mpu6050.userControl.set_bits<mpu::UserControl::FIFO_RESET>();
            mpu6050.userControl.set_bits<mpu::UserControl::FIFO_EN>();
            //mpu6050.fifoEnable.set_bits<0x78>();
            //mpu6050.fifoEnable.set_bits<static_cast<uint8_t>(mpu::FifoEnable::ACCEL_FIFO_EN)>();
            //Logger::get().WARN("OFLOW\n");
        }

        fifoDepth = mpu6050.getFifoCount();
        if (fifoDepth > 1024)
        {
            char log[8];
            snprintf(log, 8, "%d\n", fifoDepth);
            Logger::get().WARN(log);
        }

        uint16_t readLen = std::min(buffLen, fifoDepth);
        uint16_t numRead = 0;
        while (numRead < fifoDepth)
        {
            mpu6050.readFifo(buff, readLen);
            uart1.write_data_block(buff, readLen);
            toggle_led();
            numRead += readLen;
            readLen = std::min(buffLen, (uint16_t)(fifoDepth - numRead));
        }

        //for (auto i = 0; i < 18 * (fifo_count / 18); i++)
        for (auto i = 0; i < readLen / 6; i++)
        {
            //vals[i % 6] = mpu6050.fifoRW.get_bits();
            char acc[64];
            uint16_t x = buff[i * 6] << 8 | buff[i * 6 + 1];
            uint16_t y = (uint16_t)buff[i * 6 + 2] << 8 | buff[i * 6 + 3];
            uint16_t z = (uint16_t)buff[i * 6 + 4] << 8 | buff[i * 6 + 5];
            auto x = buff_16[3 * i];
            auto y = buff_16[3 * i + 1];
            auto z = buff_16[3 * i + 2];
            snprintf(acc, 64, "accel = <%u, %u, %u>\n",
                     x, y, z);
            Logger::get().WARN(acc);

        }

        uint8_t real_buff[6];
        real_buff[0] = mpu6050.accelOutXH.get_bits();
        real_buff[1] = mpu6050.accelOutXL.get_bits();
        real_buff[2] = mpu6050.accelOutYH.get_bits();
        real_buff[3] = mpu6050.accelOutYL.get_bits();
        real_buff[4] = mpu6050.accelOutZH.get_bits();
        real_buff[5] = mpu6050.accelOutZL.get_bits();
        uart1.write_data_block(real_buff, 6);
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
