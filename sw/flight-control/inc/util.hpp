#pragma once

#include <utility>

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
