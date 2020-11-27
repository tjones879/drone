#pragma once
#include <stdint.h>
#include "logger.hpp"
#include "util.hpp"
#include "spi.hpp"
#include "gpio.hpp"
#include <stdio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <type_traits>
#include <algorithm>

enum class AccGyroReg : uint8_t
{
    ACT_THS = 0x04,
    ACT_DUR = 0x05,
    INT_GEN_CFG_XL = 0x06,
    INT_GEN_THS_X_XL = 0x07,
    INT_GEN_THS_Y_XL = 0x08,
    INT_GEN_THS_Z_XL = 0x09,
    INT_GEN_DUR_XL = 0x0A,
    REFERENCE_G = 0x0B,
    INT1_CTRL = 0x0C,
    INT2_CTRL = 0x0D,
    WHO_AM_I = 0x0F,
    CTRL_REG1_G = 0x10,
    CTRL_REG2_G = 0x11,
    CTRL_REG3_G = 0x12,
    ORIENT_CFG_G = 0x13,
    INT_GEN_SRC_G = 0x14,
    OUT_TEMP_L = 0x15,
    OUT_TEMP_H = 0x16,
    STATUS_REG_1 = 0x17,
    OUT_X_L_G = 0x18,
    OUT_X_H_G = 0x19,
    OUT_Y_L_G = 0x1A,
    OUT_Y_H_G = 0x1B,
    OUT_Z_L_G = 0x1C,
    OUT_Z_H_G = 0x1D,
    CTRL_REG4 = 0x1E,
    CTRL_REG5_XL = 0x1F,
    CTRL_REG6_XL = 0x20,
    CTRL_REG7_XL = 0x21,
    CTRL_REG8 = 0x22,
    CTRL_REG9 = 0x23,
    CTRL_REG10 = 0x24,
    INT_GEN_SRC_XL = 0x26,
    STATUS_REG_2 = 0x27,
    OUT_X_L_XL = 0x28,
    OUT_X_H_XL = 0x29,
    OUT_Y_L_XL = 0x2A,
    OUT_Y_H_XL = 0x2B,
    OUT_Z_L_XL = 0x2C,
    OUT_Z_H_XL = 0x2D,
    FIFO_CTRL = 0x2E,
    FIFO_SRC = 0x2F,
    INT_GEN_CFG_G = 0x30,
    INT_GEN_THS_XH_G = 0x31,
    INT_GEN_THS_XL_G = 0x32,
    INT_GEN_THS_YH_G = 0x33,
    INT_GEN_THS_YL_G = 0x34,
    INT_GEN_THS_ZH_G = 0x35,
    INT_GEN_THS_ZL_G = 0x36,
    INT_GEN_DUR_G = 0x37
};

enum class MagReg : uint8_t
{
    OFFSET_X_REG_L_M = 0x05,
    OFFSET_X_REG_H_M = 0x06,
    OFFSET_Y_REG_L_M = 0x07,
    OFFSET_Y_REG_H_M = 0x08,
    OFFSET_Z_REG_L_M = 0x09,
    OFFSET_Z_REG_H_M = 0x0A,
    WHO_AM_I_M = 0x0F,
    CTRL_REG1_M = 0x20,
    CTRL_REG2_M = 0x21,
    CTRL_REG3_M = 0x22,
    CTRL_REG4_M = 0x23,
    CTRL_REG5_M = 0x24,
    STATUS_REG_M = 0x27,
    OUT_X_L_M = 0x28,
    OUT_X_H_M = 0x29,
    OUT_Y_L_M = 0x2A,
    OUT_Y_H_M = 0x2B,
    OUT_Z_L_M = 0x2C,
    OUT_Z_H_M = 0x2D,
    INT_CFG_M = 0x30,
    INT_SRC_M = 0x31,
    INT_THS_L_M = 0x32,
    INT_THS_H_M = 0x33,
};

class Lsm9ds1
{
public:
    template<AccGyroReg reg, typename valueType, bool readWrite>
    using AccelRegister = PeripheralRegister<Lsm9ds1, AccGyroReg, reg, uint8_t, valueType, readWrite>;

    template<MagReg reg, typename valueType, bool readWrite>
    using MagRegister = PeripheralRegister<Lsm9ds1, MagReg, reg, uint8_t, valueType, readWrite>;

    Lsm9ds1(SPIBus& spi_bus, GpioPin&& accel_chip_select, GpioPin&& mag_chip_select)
        : bus(spi_bus), ag_cs(std::move(accel_chip_select)),
          mag_cs(std::move(mag_chip_select)),
          who_am_i_xl(*this),
          ctrl_g_1(*this),
          ctrl_4(*this),
          ctrl_xl_5(*this),
          ctrl_xl_6(*this),
          ctrl_8(*this),
          ctrl_9(*this),
          gyro_x_h(*this),
          gyro_x_l(*this),
          gyro_y_h(*this),
          gyro_y_l(*this),
          gyro_z_h(*this),
          gyro_z_l(*this),
          acc_x_h(*this),
          acc_x_l(*this),
          acc_y_h(*this),
          acc_y_l(*this),
          acc_z_h(*this),
          acc_z_l(*this),
          fifo_ctrl(*this),
          fifo_src(*this),
          who_am_i_m(*this)
    {
        ctrl_9.set_bits(0x00); // Disable FIFO
    }

    void initAccel()
    {
        constexpr uint8_t odr = 0x06; // ODR_XL [2:0]  952 Hz
        constexpr uint8_t fs = 0x01; // FS_XL  [1:0]  +/-16G
        //constexpr uint8_t ctrl_reg = bw | (bw_scal_odr << 2) | (fs << 3) | (odr << 5);
        constexpr uint8_t ctrl_reg = (fs << 3) | (odr << 5);
        ctrl_xl_6.set_bits(ctrl_reg);
        ctrl_xl_5.set_bits(0x38);
    }

    void initGyro()
    {
        constexpr uint8_t odr = 0x06; // ODR_G [2:0]  952 Hz
        constexpr uint8_t dps = 0x03; // FS_G  [1:0]  2000 deg/s
        constexpr uint8_t ctrl_reg = (odr << 5) | (dps << 3);
        ctrl_g_1.set_bits(ctrl_reg);
        ctrl_4.set_bits(0x38);
    }

    void initFifo(uint8_t threshold)
    {
        ctrl_9.set_bits(0x04 | 0x02); // I2C_DIS | FIFO_EN
        ctrl_8.set_bits(0x40); // Enable BDU
        constexpr uint8_t fmode = 0x20; // Set FIFO mode
        fifo_ctrl.set_bits(fmode | (threshold & 0x1F));
    }

    void resetFifo()
    {
        Logger::get().INFO("RESET\n");
        gpio_toggle(GPIOC, GPIO13);
        uint8_t reg_9 = ctrl_9.get_bits();
        ctrl_9.set_bits(reg_9 & ~0x02); // FIFO DISABLE
        fifo_ctrl.set_bits(0x00);

        initFifo(32);
    }

    void readFifo(uint16_t *samples, uint8_t &num_samples)
    {
        auto fifo_status = fifo_src.get_bits();
        const uint8_t fifo_depth = fifo_status & 0x3f;
        // Check for overrun
        if (fifo_status & 0x40)
        {
            num_samples = 0;
            resetFifo();
        }
        else
        {
            num_samples = std::min(num_samples, fifo_depth);
            if (num_samples)
            {
                for (unsigned i = 0; i < num_samples; i++)
                {
                    samples[6 * i] = getGyroX();
                    samples[6 * i + 1] = getGyroY();
                    samples[6 * i + 2] = getGyroZ();
                    samples[6 * i + 3] = getAccelX();
                    samples[6 * i + 4] = getAccelY();
                    samples[6 * i + 5] = getAccelZ();
                }
            }
        }
    }

    int16_t getAccelX()
    {
        uint16_t lo = acc_x_l.get_bits() & 0xff;
        uint16_t hi = acc_x_h.get_bits() & 0xff;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    int16_t getAccelY()
    {
        uint16_t lo = acc_y_l.get_bits() & 0xFF;
        uint16_t hi = acc_y_h.get_bits() & 0xFF;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    int16_t getAccelZ()
    {
        uint16_t lo = gyro_z_l.get_bits() & 0xFF;
        uint16_t hi = gyro_z_h.get_bits() & 0xFF;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    int16_t getGyroX()
    {
        uint16_t lo = gyro_x_l.get_bits() & 0xff;
        uint16_t hi = gyro_x_h.get_bits() & 0xff;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    int16_t getGyroY()
    {
        uint16_t hi = gyro_y_h.get_bits() & 0xFF;
        uint16_t lo = gyro_y_l.get_bits() & 0xFF;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    int16_t getGyroZ()
    {
        uint16_t hi = gyro_z_h.get_bits() & 0xFF;
        uint16_t lo = gyro_z_l.get_bits() & 0xFF;
        return static_cast<int16_t>((hi << 8) | lo);
    }

    void write(AccGyroReg reg, uint8_t val)
    {
        ag_cs.clear();
        bus.write(static_cast<uint8_t>(reg), val);
        ag_cs.set();
    }

    void write(MagReg reg, uint8_t val)
    {
        mag_cs.clear();
        bus.write(static_cast<uint8_t>(reg), val);
        mag_cs.set();
    }

    uint16_t read(AccGyroReg reg)
    {
        ag_cs.clear();
        auto val = bus.read(static_cast<uint8_t>(reg));
        ag_cs.set();
        return val;
    }

    uint16_t read(MagReg reg)
    {
        mag_cs.clear();
        auto val = bus.read(static_cast<uint8_t>(reg));
        mag_cs.set();
        return val;
    }

    void readBurst(AccGyroReg reg, uint8_t *vals, size_t count)
    {
        ag_cs.clear();
        vals[0] = bus.read(static_cast<uint8_t>(reg)) & 0xFF;
        uint16_t *vals_16 = (uint16_t *)(vals + 1);
        for (unsigned i = 0; i < count - 1; i++)
        {
            vals_16[i] = bus.read(0x00);
        }
        vals[2 * count - 1] = bus.read(0x00) >> 8;
        ag_cs.set();
    }

private:
    SPIBus &bus;
    GpioPin ag_cs;
    GpioPin mag_cs;
public:
    AccelRegister<AccGyroReg::WHO_AM_I, uint8_t, false> who_am_i_xl;
    AccelRegister<AccGyroReg::CTRL_REG1_G, uint8_t, true> ctrl_g_1;
    AccelRegister<AccGyroReg::CTRL_REG4, uint8_t, true> ctrl_4;
    AccelRegister<AccGyroReg::CTRL_REG5_XL, uint8_t, true> ctrl_xl_5;
    AccelRegister<AccGyroReg::CTRL_REG6_XL, uint8_t, true> ctrl_xl_6;
    AccelRegister<AccGyroReg::CTRL_REG8, uint8_t, true> ctrl_8;
    AccelRegister<AccGyroReg::CTRL_REG9, uint8_t, true> ctrl_9;
    AccelRegister<AccGyroReg::OUT_X_H_G, uint8_t, false> gyro_x_h;
    AccelRegister<AccGyroReg::OUT_X_L_G, uint8_t, false> gyro_x_l;
    AccelRegister<AccGyroReg::OUT_Y_H_G, uint8_t, false> gyro_y_h;
    AccelRegister<AccGyroReg::OUT_Y_L_G, uint8_t, false> gyro_y_l;
    AccelRegister<AccGyroReg::OUT_Z_H_G, uint8_t, false> gyro_z_h;
    AccelRegister<AccGyroReg::OUT_Z_L_G, uint8_t, false> gyro_z_l;
    AccelRegister<AccGyroReg::OUT_X_H_XL, uint8_t, false> acc_x_h;
    AccelRegister<AccGyroReg::OUT_X_L_XL, uint8_t, false> acc_x_l;
    AccelRegister<AccGyroReg::OUT_Y_H_XL, uint8_t, false> acc_y_h;
    AccelRegister<AccGyroReg::OUT_Y_L_XL, uint8_t, false> acc_y_l;
    AccelRegister<AccGyroReg::OUT_Z_H_XL, uint8_t, false> acc_z_h;
    AccelRegister<AccGyroReg::OUT_Z_L_XL, uint8_t, false> acc_z_l;
    AccelRegister<AccGyroReg::FIFO_CTRL, uint8_t, true> fifo_ctrl;
    AccelRegister<AccGyroReg::FIFO_SRC, uint8_t, false> fifo_src;

    MagRegister<MagReg::WHO_AM_I_M, uint8_t, false> who_am_i_m;
};
