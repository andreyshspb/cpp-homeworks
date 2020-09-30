#pragma once


#include <iostream>
#include <memory>
#include <algorithm>
#include <new>


namespace my_vector {


    template<typename T>
    my_vector<T>::my_vector(size_t size) {
        capacity_ = near_power_two(size);
        len_ = size;
        array_ = reinterpret_cast<T *>(new char[capacity_ * sizeof(T)]);

        std::size_t pointer;
        try {
            for (pointer = 0; pointer < len_; pointer++) {
                new(&array_[pointer]) T();
            }
        } catch (...) {
            delete_data(array_, pointer);
            throw;
        }
    }


    template<typename T>
    my_vector<T>::my_vector(const my_vector<T> &other) {
        capacity_ = near_power_two(other.len_);
        len_ = other.len_;
        array_ = reinterpret_cast<T *>(new char[capacity_ * sizeof(T)]);

        std::size_t pointer;
        try {
            for (pointer = 0; pointer < len_; pointer++) {
                new(&array_[pointer]) T(other.array_[pointer]);
            }
        } catch (...) {
            delete_data(array_, pointer);
            throw;
        }

    }


    template<typename T>
    my_vector<T>::my_vector(my_vector<T> &&other) noexcept {
        swap(other);
    }


    template<typename T>
    my_vector<T> &my_vector<T>::operator=(const my_vector<T> &vector) {
        my_vector<T> temp(vector);
        swap(temp);
        return *this;
    }


    template<typename T>
    my_vector<T> &my_vector<T>::operator=(my_vector<T> &&vector) noexcept {
        swap(vector);
        return *this;
    }


    template<typename T>
    my_vector<T>::~my_vector() {
        delete_data(array_, len_);
    }


    template<typename T>
    std::size_t my_vector<T>::size() const noexcept {
        return len_;
    }


    template<typename T>
    std::size_t my_vector<T>::capacity() const noexcept {
        return capacity_;
    }


    template<typename T>
    bool my_vector<T>::empty() const noexcept {
        return len_ == 0;
    }


    template<typename T>
    void my_vector<T>::resize(std::size_t new_len) {
        while (size() < new_len) push_back(T());
        while (size() > new_len) pop_back();
    }


    template<typename T>
    void my_vector<T>::reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        new_capacity = near_power_two(new_capacity);

        T *temp_array = reinterpret_cast<T *>(new char[new_capacity * sizeof(T)]);
        for (std::size_t i = 0; i < len_; i++) {
            new(&temp_array[i]) T(std::move(array_[i]));
        }

        delete_data(array_, len_);
        capacity_ = new_capacity;
        array_ = temp_array;

    }


    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }


    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }



    template<typename T>
    void my_vector<T>::push_back(const T &value) {
        push_back(T(value));
    }


    template<typename T>
    void my_vector<T>::push_back(T &&value) {
        reserve(len_ + 1);
        new(&array_[len_++]) T(std::move(value));
    }


    template<typename T>
    void my_vector<T>::pop_back() noexcept {
        if (len_ == 0) return;
        array_[--len_].~T();
    }


    template<typename T>
    void my_vector<T>::clear() noexcept {
        for (std::size_t i = len_; i > 0; i--) {
            array_[i - 1].~T();
        }
        len_ = 0;
    }


    template<typename T>
    std::ostream &operator<<(std::ostream &out, const my_vector<T> &vector) {
        for (std::size_t i = 0; i < vector.len_; i++) {
            out << (vector.array_[i]);
            if (i < vector.len_ - 1) out << ' ';
        }
        return out;
    }


    template<typename T>
    std::size_t my_vector<T>::near_power_two(std::size_t number) {
        if (number == 0) return 0;
        std::size_t i = 1;
        while (i < number) i *= 2;
        return i;
    }


    template<typename T>
    void my_vector<T>::swap(my_vector<T> &vector) noexcept {
        std::swap(capacity_, vector.capacity_);
        std::swap(len_, vector.len_);
        std::swap(array_, vector.array_);
    }


    template<typename T>
    void my_vector<T>::delete_data(T *data, std::size_t pointer) noexcept {
        for (std::size_t i = pointer; i > 0; i--) {
            data[i - 1].~T();
        }
        delete[] reinterpret_cast<char *>(data);
    }

}  // namespace "my_vector"


