#pragma once


#include <cassert>
#include <stdexcept>


namespace lab_13 {


template<typename T, size_t N>
my_array<T, N>::my_array(std::initializer_list<T> list) {
    if (list.size() > N) throw std::out_of_range("too many");
    size_t i = 0;
    for (auto &element : list) {
        arr_[i] = element;
        i += 1;
    }
}


template<typename T, size_t N>
T &my_array<T, N>::at(size_t index) {
    if (index < 0|| N <= index) throw std::out_of_range("bad index");
    return arr_[index];
}


template<typename T, size_t N>
const T &my_array<T, N>::at(size_t index) const {
    if (index < 0|| N <= index) throw std::out_of_range("bad index");
    return arr_[index];
}


template<typename T, size_t N>
T &my_array<T, N>::operator[](size_t index) {
    return arr_[index];
}


template<typename T, size_t N>
const T &my_array<T, N>::operator[](size_t index) const {
    return arr_[index];
}


template<typename T, size_t N>
bool my_array<T, N>::empty() const {
    return N == 0;
}


template<typename T, size_t N>
size_t my_array<T, N>::size() const {
    return N;
}


template<typename T, size_t N>
void my_array<T, N>::fill(T value) {
    for (size_t i = 0; i < N; i++) {
        arr_[i] = value;
    }
}


// ============================================BOOL==============================================

// ============CLASS_PROXY=============

template<size_t N>
my_array<bool, N>::proxy::proxy(char *data, size_t bit) : data_(data), bit_(bit) {}


template<size_t N>
typename my_array<bool, N>::proxy &my_array<bool, N>::proxy::operator=(bool value) {
    *data_ &= ~(1 << bit_);
    *data_ |= (value << bit_);
    return *this;
}


template<size_t N>
typename my_array<bool, N>::proxy &my_array<bool, N>::proxy::operator=(const proxy &other) {
     bool value = bool(other);
     operator=(value);
     return *this;
}


template<size_t N>
my_array<bool, N>::proxy::operator bool() const {
    return ((*data_) >> bit_) & 1;
}


template<size_t N>
bool my_array<bool, N>::proxy::operator==(const typename my_array<bool, N>::proxy &other) const {
    return (bool)(*this) == (bool)other;
}

// ===============METHODS==============

template<size_t N>
my_array<bool, N>::my_array(std::initializer_list<bool> list) : my_array() {
    if (list.size() > N) throw std::out_of_range("too many");
    size_t i = 0;
    for (const bool &element : list) {
        operator[](i) = element;
        i += 1;
    }
}


template<size_t N>
typename my_array<bool, N>::proxy my_array<bool, N>::at(size_t index) {
    if (index < 0|| N <= index) throw std::out_of_range("bad index");
    return my_array<bool, N>::proxy(arr_ + (index / CHAR_BIT), index % CHAR_BIT);
}


template<size_t N>
bool my_array<bool, N>::at(size_t index) const {
    if (index < 0|| N <= index) throw std::out_of_range("bad index");
    return ((*(arr_ + (index / CHAR_BIT))) >> (index % CHAR_BIT)) & 1;
}


template<size_t N>
typename my_array<bool, N>::proxy my_array<bool, N>::operator[](size_t index) {
    return my_array<bool, N>::proxy(arr_ + (index / CHAR_BIT), index % CHAR_BIT);
}


template<size_t N>
bool my_array<bool, N>::operator[](size_t index) const {
    return ((*(arr_ + (index / CHAR_BIT))) >> (index % CHAR_BIT)) & 1;
}


template<size_t N>
bool my_array<bool, N>::empty() const {
    return N == 0;
}


template<size_t N>
size_t my_array<bool, N>::size() const {
    return N;
}


template<size_t N>
void my_array<bool, N>::fill(bool value) {
    for (size_t i = 0; i < N; i++) {
        operator[](i) = value;
    }
}


} // namespace my_array

