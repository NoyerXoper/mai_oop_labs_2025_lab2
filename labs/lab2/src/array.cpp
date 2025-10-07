#include "array.hpp"

#include <memory>

constexpr std::size_t DEFAULT_CAPACITY = 10;

Array::Array(): _capacity(DEFAULT_CAPACITY), _size(0), _data(new unsigned char[_capacity]) {}
Array::Array(std::size_t size): _capacity(size), _size(0), _data(new unsigned char[size]) {}
Array::Array(std::size_t size, unsigned char ch): _capacity(size), _size(size), _data(new unsigned char[_capacity]) {
    for (int i = 0; i < size; ++i) {
        _data[i] = ch;
    }
}
Array::Array(const std::initializer_list<unsigned char>& il): _capacity(il.size()), _size(il.size()), _data(new unsigned char[_capacity]) {
    int i = 0;
    for (unsigned char ch: il) {
        _data[i++] = ch;
    }
}

Array::Array(const std::string& str): _capacity(str.size()), _size(str.size()), _data(new unsigned char[str.size()]) {
    int i = 0;
    for (unsigned char ch: str) {
        _data[i++] = ch;
    }
}

Array::Array(const Array& other): _capacity(other._capacity), _size(other._size), _data(new unsigned char[_capacity]) {
    std::uninitialized_copy(other._data, other._data + other._size, _data);
}

Array::Array(Array&& other) noexcept: _capacity(other._capacity), _size(other._size), _data(other._data)  {
    other._capacity = 0;
    other._size= 0;
    other._data = nullptr;
}

Array::~Array() noexcept {
    delete[] _data;
}

std::size_t Array::Size() const noexcept {
    return _size;
}

std::size_t Array::Capacity() const noexcept {
    return _capacity;
}

unsigned char& Array::Get(std::size_t i) noexcept {
    return _data[i];
}

unsigned char Array::Get(std::size_t i) const noexcept {
    return _data[i];
}

void Array::PushBack(unsigned char ch) {
    CheckCapacity(_size + 1);
    _data[_size] = ch;
    ++_size;
}

void Array::PopBack() {
    if (_size > 0) {
        --_size;
    }
}


unsigned char& Array::Front() {
    return _data[0];
};

unsigned char Array::Front() const {
    return _data[0];
}

unsigned char& Array::Back() {
    return _data[_size - 1];
}

unsigned char Array::Back() const {
    return _data[_size - 1];
}

void Array::Reserve(std::size_t size) {
    // if capacity is greater of equal to new capacity, just do nothing
    if (_capacity >= size) {
        return;
    }

    unsigned char* new_data = new unsigned char[size];
    _capacity = size;
    if (_data) {
        std::uninitialized_move(_data, _data + _size, new_data);
    }
    delete[] _data;
    _data = new_data;
}

bool Array::Equals(const Array& other) const noexcept {
    if (_size != other._size) {
        return false;
    }
    for (int i = 0; i < _size; ++i) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

void Array::CheckCapacity(std::size_t size) {
    if (size <= _capacity) {
        return;
    }
    Reserve(std::max(2 * _capacity, static_cast<std::size_t>(10)));
}

