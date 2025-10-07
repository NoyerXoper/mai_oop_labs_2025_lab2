#pragma once

#include <initializer_list>
#include <string>

#include "array.hpp"

class Seven {
public:
    Seven();
    Seven(std::size_t size, unsigned char digit);
    Seven(const std::initializer_list<unsigned char>& il);
    Seven(const std::string& str);

    Seven(const Seven& other);
    Seven(Seven&& other) noexcept;
    virtual ~Seven() noexcept;

    bool Equals(const Seven& other) const noexcept;
    bool Greater(const Seven& other) const noexcept;
    bool Smaller(const Seven& other) const noexcept;

    static Seven Add(const Seven& first, const Seven& second);
    static Seven Subtract(const Seven& first, const Seven& second);

private:
    Array _digits;
};
