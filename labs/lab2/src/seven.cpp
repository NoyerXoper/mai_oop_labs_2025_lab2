#include "seven.hpp"

#include <memory>
#include <initializer_list>
#include <stdexcept>

namespace {
inline std::size_t Mod7Diff(std::size_t a, std::size_t b) {
    return a > b ? (a - b) % 7 : (7 + a - b) % 7;
}
void RemoveLeadingZeroes(Array& array) {
    while (array.Size() > 0 && array.Back() == 0) {
        array.PopBack();
    }
}
}

Seven::Seven(): _digits(1, '0') {}
Seven::Seven(std::size_t size, unsigned char digit): _digits(size, digit) {
    if (size == 0) {
        throw std::invalid_argument("Number can't be a length of 0");
    }
    if (digit > 6) {
        throw std::invalid_argument("Digit can't be greater that 6");
    }
    RemoveLeadingZeroes(_digits);
}
Seven::Seven(const std::initializer_list<unsigned char>& il): _digits(il.size(), 0) {
    if (il.size() == 0) {
        throw std::invalid_argument("Initializer list can't be empty");
    }
    std::size_t i = il.size();
    for(auto it = il.begin(); it != il.end(); ++it) {
        if (*it > 6) {
            throw std::invalid_argument("Numbers in initializer list must be not greater that 6");
        }
        _digits.Get(--i) = *it;
    }
    RemoveLeadingZeroes(_digits);
}

Seven::Seven(const std::string& str): _digits(str.size()) {
    if (str.size() == 0) {
        throw std::invalid_argument("String can't be empty");
    }
    for(auto it = str.rbegin(); it != str.rend(); ++it) {
        if (*it > '6' || *it < '0') {
            throw std::invalid_argument("Characters in string must be digits and be not greater that 6");
        }
        _digits.PushBack(*it - '0');
    }
    RemoveLeadingZeroes(_digits);
}

Seven::Seven(const Seven& other) = default;
Seven::Seven(Seven&& other) noexcept = default;
Seven::~Seven() noexcept = default;


bool Seven::Equals(const Seven& other) const noexcept {
    return _digits.Equals(other._digits);
}
bool Seven::Smaller(const Seven& other) const noexcept {
    if (_digits.Size() > other._digits.Size()) {
        return false;
    }
    if (_digits.Size() < other._digits.Size()) {
        return true;
    }

    for (int i = _digits.Size() - 1; i > 0; --i) {
        if (_digits.Get(i) > other._digits.Get(i)) {
            return false;
        }
        if (_digits.Get(i) < other._digits.Get(i)) {
            return true;
        }
    }
    return _digits.Get(0) < other._digits.Get(0);
}

bool Seven::Greater(const Seven& other) const noexcept {
    if (_digits.Size() < other._digits.Size()) {
        return false;
    }
    if (_digits.Size() > other._digits.Size()) {
        return true;
    }

    for (int i = _digits.Size() - 1; i > 0; --i) {
        if (_digits.Get(i) < other._digits.Get(i)) {
            return false;
        }
        if (_digits.Get(i) > other._digits.Get(i)) {
            return true;
        }
    }
    return _digits.Get(0) > other._digits.Get(0);
}

Seven Seven::Add(const Seven& first, const Seven& second) {
    Seven result(std::max(first._digits.Size(), second._digits.Size()) + 1, 0);

    std::size_t minLength = std::min(first._digits.Size(), second._digits.Size());
    std::size_t carry = 0;
    std::size_t digit;

    for (int i = 0; i < minLength; ++i) {
        digit = first._digits.Get(i) + second._digits.Get(i) + carry;
        result._digits.PushBack(digit % 7);
        carry = digit > 7;
    } 

    for (int i = minLength; i < first._digits.Size(); ++i) {
        digit = first._digits.Get(i) + carry;
        result._digits.PushBack(digit % 7);
        carry = digit > 7;
    }
    for (int i = minLength; i < second._digits.Size(); ++i) {
        digit = second._digits.Get(i) + carry;
        result._digits.PushBack(digit % 7);
        carry = digit > 7;
    }
    return result;
}

Seven Seven::Subtract(const Seven& first, const Seven& second) {
    if (first._digits.Size() < second._digits.Size()) {
        throw std::invalid_argument("First number must be greater or equal to second");
    }
    Seven result(std::max(first._digits.Size(), second._digits.Size()), 0);

    std::size_t minLength = second._digits.Size();
    std::size_t carry = 0;
    std::size_t digit;

    for (int i = 0; i < minLength; ++i) {
        digit = Mod7Diff(Mod7Diff(first._digits.Get(i), second._digits.Get(i)), carry);
        result._digits.PushBack(digit);
        carry = (second._digits.Get(i) + carry) > first._digits.Get(i);
    } 

    for (int i = minLength; i < first._digits.Size(); ++i) {
        digit = Mod7Diff(first._digits.Get(i), carry);
        result._digits.PushBack(digit);
        carry = carry > first._digits.Get(i);
    }

    RemoveLeadingZeroes(result._digits);

    if (carry) {
        throw std::invalid_argument("First number must be greater or equal to second");
    }
    return result;
}
