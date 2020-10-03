#pragma once
#include <cstdint>

#include "dma.hpp"
#include "i2c.hpp"

namespace mpu {
enum class I2CAddr : uint8_t
{
    LOW = 0x68,
    HI = 0x69
};

enum class Reg : uint8_t
{
    XG_OFFS_TC = 0x00,  //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
    YG_OFFS_TC = 0x01,  //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
    ZG_OFFS_TC = 0x02,  //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
    X_FINE_GAIN = 0x03, //[7:0] X_FINE_GAIN
    Y_FINE_GAIN = 0x04, //[7:0] Y_FINE_GAIN
    Z_FINE_GAIN = 0x05, //[7:0] Z_FINE_GAIN
    XA_OFFS_H = 0x06,   //[15:0] XA_OFFS
    XA_OFFS_L_TC = 0x07,
    YA_OFFS_H = 0x08, //[15:0] YA_OFFS
    YA_OFFS_L_TC = 0x09,
    ZA_OFFS_H = 0x0A, //[15:0] ZA_OFFS
    ZA_OFFS_L_TC = 0x0B,
    SELF_TEST_X = 0x0D,  //[7:5] XA_TEST[4-2] [4:0] XG_TEST[4-0]
    SELF_TEST_Y = 0x0E,  //[7:5] YA_TEST[4-2] [4:0] YG_TEST[4-0]
    SELF_TEST_Z = 0x0F,  //[7:5] ZA_TEST[4-2] [4:0] ZG_TEST[4-0]
    SELF_TEST_A = 0x10,  //[5:4] XA_TEST [3:2] YA_TEST, [1:0] ZA_TEST
    XG_OFFS_USRH = 0x13, //[15:0] XG_OFFS_USR
    XG_OFFS_USRL = 0x14,
    YG_OFFS_USRH = 0x15, //[15:0] YG_OFFS_USR
    YG_OFFS_USRL = 0x16,
    ZG_OFFS_USRH = 0x17, //[15:0] ZG_OFFS_USR
    ZG_OFFS_USRL = 0x18,
    SMPLRT_DIV = 0x19,
    CONFIG = 0x1A,
    GYRO_CONFIG = 0x1B,
    ACCEL_CONFIG = 0x1C,
    FF_THR = 0x1D,
    FF_DUR = 0x1E,
    MOT_THR = 0x1F,
    MOT_DUR = 0x20,
    ZRMOT_THR = 0x21,
    ZRMOT_DUR = 0x22,
    FIFO_EN = 0x23,
    I2C_MST_CTRL = 0x24,
    I2C_SLV0_ADDR = 0x25,
    I2C_SLV0_REG = 0x26,
    I2C_SLV0_CTRL = 0x27,
    I2C_SLV1_ADDR = 0x28,
    I2C_SLV1_REG = 0x29,
    I2C_SLV1_CTRL = 0x2A,
    I2C_SLV2_ADDR = 0x2B,
    I2C_SLV2_REG = 0x2C,
    I2C_SLV2_CTRL = 0x2D,
    I2C_SLV3_ADDR = 0x2E,
    I2C_SLV3_REG = 0x2F,
    I2C_SLV3_CTRL = 0x30,
    I2C_SLV4_ADDR = 0x31,
    I2C_SLV4_REG = 0x32,
    I2C_SLV4_DO = 0x33,
    I2C_SLV4_CTRL = 0x34,
    I2C_SLV4_DI = 0x35,
    I2C_MST_STATUS = 0x36,
    INT_PIN_CFG = 0x37,
    INT_ENABLE = 0x38,
    DMP_INT_STATUS = 0x39,
    INT_STATUS = 0x3A,
    ACCEL_XOUT_H = 0x3B,
    ACCEL_XOUT_L = 0x3C,
    ACCEL_YOUT_H = 0x3D,
    ACCEL_YOUT_L = 0x3E,
    ACCEL_ZOUT_H = 0x3F,
    ACCEL_ZOUT_L = 0x40,
    TEMP_OUT_H = 0x41,
    TEMP_OUT_L = 0x42,
    GYRO_XOUT_H = 0x43,
    GYRO_XOUT_L = 0x44,
    GYRO_YOUT_H = 0x45,
    GYRO_YOUT_L = 0x46,
    GYRO_ZOUT_H = 0x47,
    GYRO_ZOUT_L = 0x48,
    EXT_SENS_DATA_00 = 0x49,
    EXT_SENS_DATA_01 = 0x4A,
    EXT_SENS_DATA_02 = 0x4B,
    EXT_SENS_DATA_03 = 0x4C,
    EXT_SENS_DATA_04 = 0x4D,
    EXT_SENS_DATA_05 = 0x4E,
    EXT_SENS_DATA_06 = 0x4F,
    EXT_SENS_DATA_07 = 0x50,
    EXT_SENS_DATA_08 = 0x51,
    EXT_SENS_DATA_09 = 0x52,
    EXT_SENS_DATA_10 = 0x53,
    EXT_SENS_DATA_11 = 0x54,
    EXT_SENS_DATA_12 = 0x55,
    EXT_SENS_DATA_13 = 0x56,
    EXT_SENS_DATA_14 = 0x57,
    EXT_SENS_DATA_15 = 0x58,
    EXT_SENS_DATA_16 = 0x59,
    EXT_SENS_DATA_17 = 0x5A,
    EXT_SENS_DATA_18 = 0x5B,
    EXT_SENS_DATA_19 = 0x5C,
    EXT_SENS_DATA_20 = 0x5D,
    EXT_SENS_DATA_21 = 0x5E,
    EXT_SENS_DATA_22 = 0x5F,
    EXT_SENS_DATA_23 = 0x60,
    MOT_DETECT_STATUS = 0x61,
    I2C_SLV0_DO = 0x63,
    I2C_SLV1_DO = 0x64,
    I2C_SLV2_DO = 0x65,
    I2C_SLV3_DO = 0x66,
    I2C_MST_DELAY_CTRL = 0x67,
    SIGNAL_PATH_RESET = 0x68,
    MOT_DETECT_CTRL = 0x69,
    USER_CTRL = 0x6A,
    PWR_MGMT_1 = 0x6B,
    PWR_MGMT_2 = 0x6C,
    BANK_SEL = 0x6D,
    MEM_START_ADDR = 0x6E,
    MEM_R_W = 0x6F,
    DMP_CFG_1 = 0x70,
    DMP_CFG_2 = 0x71,
    FIFO_COUNTH = 0x72,
    FIFO_COUNTL = 0x73,
    FIFO_R_W = 0x74,
    WHO_AM_I = 0x75
};

enum class IntSources : uint8_t
{
    DATA_READY = 1,
    I2C_MASTER = 0x8,
    FIFO_OFLOW = 0x10,
};

enum class GyroRange : uint8_t
{
    DEG_250 = 0x0,
    DEG_500 = 0x8,
    DEG_1000 = 0x10,
    DEG_2000 = 0x18
};

enum class AccelRange : uint8_t
{
    G_2 = 0x0,
    G_4 = 0x8,
    G_8 = 0x10,
    G_16 = 0x18
};

enum class LPF : uint8_t
{
    HZ_260 = 0,
    HZ_184 = 1,
    HZ_94 = 2,
    HZ_44 = 3,
    HZ_21 = 4,
    HZ_10 = 5,
    HZ_5 = 6
};

enum class FifoEnable : uint8_t
{
   DISABLE = 0,
   SLV0_FIFO_EN = 1,
   SLV1_FIFO_EN = 2,
   SLV2_FIFO_EN = 4,
   ACCEL_FIFO_EN = 8,
   ZG_FIFO_EN = 16,
   YG_FIFO_EN = 32,
   XG_FIFO_EN = 64,
   TEMP_FIFO_EN = 128,
};

enum class UserControl : uint8_t
{
    NIL = 0,
    SIG_COND_RESET = 1,
    I2C_MST_RESET = 2,
    FIFO_RESET = 4,
    I2C_IF_DIS = 16,
    I2C_MST_EN = 32,
    FIFO_EN = 64,
};
} // namespace mpu

class MPU6050
{
public:
    MPU6050(mpu::I2CAddr devAddr, DMA dmaDev)
    noexcept
      : interruptSources(*this)
      , lpf(*this)
      , accelRange(*this)
      , gyroRange(*this)
      , accelOutXH(*this)
      , accelOutXL(*this)
      , accelOutYH(*this)
      , accelOutYL(*this)
      , accelOutZH(*this)
      , accelOutZL(*this)
      , fifoEnable(*this)
      , fifoCountH(*this)
      , fifoCountL(*this)
      , fifoRW(*this)
      , power(*this)
      , userControl(*this)
      , addr(devAddr)
      , i2c(I2C2)
      , dmaDev(dmaDev)
    {
        /*
        dmaDev.disable();
        dmaDev.setPeripheralAddress(i2c.dataReg);
        dmaDev.setPeripheralSize(dma::Size::BYTE);
        dmaDev.setPriority(dma::Priority::VERY_HIGH);
        dmaDev.enable();
        */
    }
    /**
     * Test that we have a valid connection to a MPU6050.
     *
     * The contents of the WHO_AM_I register should always
     * contain 0x68.
     */
    bool testConnection()
    {
        auto val = readRegister(mpu::Reg::WHO_AM_I);
        if (val != 0x68)
            return false;
        else
            return true;
    }

    void setAccel(uint8_t val) { writeRegister(mpu::Reg::ACCEL_CONFIG, val); }

    uint8_t getAccel() { return readRegister(mpu::Reg::ACCEL_CONFIG); }

    void setSampleRate(float targetRate)
    {
        auto divisor = [](auto target) constexpr noexcept->uint8_t
        {
            if (target > 8000.f || target < 0.f)
                return 0;
            return static_cast<uint8_t>(8000.f / target) - 1;
        };

        writeRegister(mpu::Reg::SMPLRT_DIV, divisor(targetRate));
    }

    float getSampleRate()
    {
        auto val = readRegister(mpu::Reg::SMPLRT_DIV);
        return 8000.f / (1.f + val);
    }

    // DMP Initialize

    // Get interrupt status
    // dmpGetQuarternion
    // dmpGetGravity
    // dmpGetYawPitchRoll
    uint16_t getFifoCount()
    {
        return ((uint16_t) fifoCountH.get_bits()) << 8 | (uint16_t)fifoCountL.get_bits();
    }

    void readFifo(uint8_t *buff, size_t buffLen)
    {
        readRegisterBurst(mpu::Reg::FIFO_R_W, buff, buffLen);
    }

    template<mpu::Reg reg, typename valueType>
    struct Register
    {
        constexpr Register(MPU6050 &device) : dev(device) {}

        template<valueType val>
        void set_bits()
        {
            auto writeValue = 0 | (static_cast<uint8_t>(val));
            dev.writeRegister(reg, writeValue);
        }

        uint8_t get_bits() { return dev.readRegister(reg); }

        MPU6050 &dev;
    };

    Register<mpu::Reg::INT_ENABLE, mpu::IntSources> interruptSources;
    Register<mpu::Reg::CONFIG, mpu::LPF> lpf;
    Register<mpu::Reg::ACCEL_CONFIG, mpu::AccelRange> accelRange;
    Register<mpu::Reg::GYRO_CONFIG, mpu::GyroRange> gyroRange;
    Register<mpu::Reg::PWR_MGMT_1, uint8_t> power;
    Register<mpu::Reg::ACCEL_XOUT_H, uint8_t> accelOutXH;
    Register<mpu::Reg::ACCEL_XOUT_L, uint8_t> accelOutXL;
    Register<mpu::Reg::ACCEL_YOUT_H, uint8_t> accelOutYH;
    Register<mpu::Reg::ACCEL_YOUT_L, uint8_t> accelOutYL;
    Register<mpu::Reg::ACCEL_ZOUT_H, uint8_t> accelOutZH;
    Register<mpu::Reg::ACCEL_ZOUT_L, uint8_t> accelOutZL;
    Register<mpu::Reg::FIFO_EN, uint8_t> fifoEnable;
    Register<mpu::Reg::FIFO_R_W, uint8_t> fifoRW;
    Register<mpu::Reg::USER_CTRL, mpu::UserControl> userControl;

private:
    mpu::I2CAddr addr;
    I2CDev i2c;
    DMA dmaDev;
    // Internal registers
    Register<mpu::Reg::FIFO_COUNTH, uint8_t> fifoCountH;
    Register<mpu::Reg::FIFO_COUNTL, uint8_t> fifoCountL;

    /**
     * Page 36 of the MPU-60x0 DS specifies the protocol to read a register.
     */
    uint8_t readRegister(mpu::Reg reg)
    {
        i2c.send_start_block();
        i2c.send_addr_block(static_cast<uint8_t>(addr), false);
        i2c.send_data_block(static_cast<uint8_t>(reg));

        i2c.send_start_block();
        i2c.send_addr_block(static_cast<uint8_t>(addr), true);
        auto data = i2c.read_data_block();
        i2c.send_stop();
        return data;
    }

    void readRegisterBurst(mpu::Reg reg, uint8_t *buff, size_t buffLen)
    {
        i2c.send_start_block();
        i2c.send_addr_block(static_cast<uint8_t>(addr), false);
        i2c.send_data_block(static_cast<uint8_t>(reg));

        i2c.send_start_block();
        i2c.send_addr_block(static_cast<uint8_t>(addr), true);
        i2c.read_data_blocks(buff, buffLen);
        i2c.send_stop();
    }

    void writeRegister(mpu::Reg reg, uint8_t val)
    {
        i2c.send_start_block();
        i2c.send_addr_block(static_cast<uint8_t>(addr), false);
        i2c.send_data_block(static_cast<uint8_t>(reg));

        i2c.send_data_block(val);
        i2c.send_stop();
    }
};
