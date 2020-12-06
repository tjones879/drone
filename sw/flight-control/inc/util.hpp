#pragma once

#include <utility>
#include <stdint.h>
#include <stddef.h>
#include <limits>

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


template <typename T>
inline bool operator==(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T>
inline bool operator!=(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
inline bool operator<(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return lhs.get() < rhs.get();
}

template <typename T>
inline bool operator>(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return lhs.get() > rhs.get();
}

template <typename T>
inline bool operator<=(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return lhs.get() <= rhs.get();
}

template <typename T>
inline bool operator>=(const StrongType<T>& lhs, const StrongType<T>& rhs)
{
    return lhs.get() >= rhs.get();
}

template<typename Peripheral, typename RegisterType, RegisterType reg,
         typename RegisterSize, typename valueType, bool readWrite>
struct PeripheralRegister
{
    constexpr PeripheralRegister(Peripheral &device) : dev(device) {}

    void set_bits(valueType val)
    {
        static_assert(readWrite, "Requires read-write register");

        auto writeValue = static_cast<RegisterSize>(val);
        dev.write(reg, writeValue);
    }

    RegisterSize get_bits()
    {
        return static_cast<RegisterSize>(dev.read(reg) & std::numeric_limits<RegisterSize>::max());
    }

    Peripheral &dev;
};
