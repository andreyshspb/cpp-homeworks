#pragma once


#include <iostream>
#include <cstddef>


namespace my_vector {


    template<typename T>
    class my_vector;


    template<typename T>
    std::ostream &operator<<(std::ostream &out, const my_vector<T> &vector);


    template<typename T>
    class my_vector {
    public:

        my_vector() noexcept = default;
        explicit my_vector(std::size_t size);
        my_vector(const my_vector<T> &other);
        my_vector(my_vector<T> &&other) noexcept;
        my_vector<T> &operator=(const my_vector<T> &vector);
        my_vector<T> &operator=(my_vector<T> &&vector) noexcept;
        ~my_vector();

        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;
        bool empty() const noexcept;
        void resize(std::size_t new_len);
        void reserve(std::size_t new_capacity);

        T &operator[](std::size_t index);
        const T &operator[](std::size_t index) const;

        void push_back(const T &value);
        void push_back(T &&value);
        void pop_back() noexcept;
        void clear() noexcept;

        friend std::ostream &operator<< <T> (std::ostream &out, const my_vector<T> &vector);

    private:
        std::size_t capacity_ = 0;
        std::size_t len_ = 0;
        T *array_ = nullptr;

        std::size_t near_power_two(std::size_t number);
        void swap(my_vector<T> &vector) noexcept;
        void delete_data(T *data, std::size_t pointer) noexcept;

    };


}  // namespace "my_vector"


#include "my_vector_impl.h"


