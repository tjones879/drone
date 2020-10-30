#include <stdint.h>

namespace IMU {
const uint8_t system_id = 1;

class GyroSample {
    GyroSample (int16_t _x, int16_t _y, int16_t _z)
    : x(_x),
      y(_y),
      z(_z)
    {}
public:
    const uint8_t id = 1;
    // 
    int16_t x;
    // 
    int16_t y;
    // 
    int16_t z;
};

class AccelSample {
    AccelSample (int16_t _x, int16_t _y, int16_t _z)
    : x(_x),
      y(_y),
      z(_z)
    {}
public:
    const uint8_t id = 2;
    // 
    int16_t x;
    // 
    int16_t y;
    // 
    int16_t z;
};

class MagSample {
    MagSample (int16_t _x, int16_t _y, int16_t _z)
    : x(_x),
      y(_y),
      z(_z)
    {}
public:
    const uint8_t id = 3;
    // 
    int16_t x;
    // 
    int16_t y;
    // 
    int16_t z;
};

class GyroConfig {
    GyroConfig (int16_t _x_bias, int16_t _y_bias, int16_t _z_bias, uint16_t _sample_rate)
    : x_bias(_x_bias),
      y_bias(_y_bias),
      z_bias(_z_bias),
      sample_rate(_sample_rate)
    {}
public:
    const uint8_t id = 4;
    // 
    int16_t x_bias;
    // 
    int16_t y_bias;
    // 
    int16_t z_bias;
    // sample_scale: - 245DPS - 500DPS - 2000DPS
    uint16_t sample_rate;
};

class AccelConfig {
    AccelConfig (uint16_t _sample_rate)
    : sample_rate(_sample_rate)
    {}
public:
    const uint8_t id = 5;
    // sample_scale: - 2G - 4G - 8G - 16G
    uint16_t sample_rate;
};

class MagConfig {
    MagConfig (uint16_t _sample_rate)
    : sample_rate(_sample_rate)
    {}
public:
    const uint8_t id = 6;
    // sample_scale: - 4G - 8G - 12G - 16G
    uint16_t sample_rate;
};

}
