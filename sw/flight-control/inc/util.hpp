#pragma once

#include <utility>
#include <stdint.h>
#include <stddef.h>

template <typename T>
class StrongType
{
public:
    explicit StrongType(T const& value)
        : value_(value) {}
    explicit StrongType(T&& value)
        : value_(std::move(value)) {}

    T& get()
    {
        return value_;
    }

    T const& get() const
    {
        return value_;
    }

private:
    T value_;
};


template<typename Peripheral, typename RegisterType, RegisterType reg,
         typename RegisterSize, typename valueType, bool readWrite>
struct PeripheralRegister
{
    constexpr PeripheralRegister(Peripheral &device) : dev(device) {}

    void set_bits(valueType val)
    {
        static_assert(readWrite, "Requires read-write register");

        auto writeValue = 0 | (static_cast<RegisterSize>(val));
        dev.write(reg, writeValue);
    }

    uint8_t get_bits()
    {
        return dev.read(reg);
    }

    Peripheral &dev;
};
