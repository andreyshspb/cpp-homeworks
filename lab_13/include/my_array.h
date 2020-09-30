#pragma once


#include <iostream>
#include <climits>


namespace lab_13 {

template<typename T, size_t N>
class my_array {
public:
    my_array() = default;
    my_array(std::initializer_list<T> list);
    T &at(size_t index);
    const T &at(size_t index) const;
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(T value);

private:
    T arr_[N] = {};

};


// ============================================BOOL==============================================


template<size_t N>
class my_array<bool, N> {
public:

    class proxy {
    public:
        proxy(char *data, size_t bit);
        proxy &operator=(bool value);
        proxy &operator=(const proxy &other);
        operator bool() const;
        bool operator==(const proxy &other) const;
    private:
        char *data_;
        size_t bit_;
    };

    my_array() = default;
    my_array(std::initializer_list<bool> list);
    proxy at(size_t index);
    bool at(size_t index) const;
    proxy operator[](size_t index);
    bool operator[](size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(bool value);

private:
    char arr_[(N + CHAR_BIT - 1) / CHAR_BIT] = {};

};

} // namespace my_array


#include "my_array_impl.h"

