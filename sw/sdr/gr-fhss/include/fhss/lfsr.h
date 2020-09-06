#ifndef lfsr_H
#define lfsr_H

#include <stdint.h>

class GLFSR
{
public:
    GLFSR(uint32_t seed, uint32_t polynomial);
    uint32_t next();
private:
    uint32_t polynomial;
    uint32_t data;
};

#endif /* lfsr_H */
