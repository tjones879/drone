#include <lfsr.h>

GLFSR::GLFSR(uint32_t seed, uint32_t polynomial)
    : polynomial(polynomial), data(seed)
{}

uint32_t GLFSR::next()
{
    uint32_t lsb = data & 1u;
    data >>= 1;
    if (lsb)
        data &= polynomial;

    return data;
}
