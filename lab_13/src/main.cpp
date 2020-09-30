#include "my_array.h"
#include "Product.hpp"


#include <iostream>
#include <cassert>


using namespace lab_13;


// testing simple array with int
void first_test() {
    my_array<int, 10> arr;
    arr.fill(10);
    assert(!arr.empty());
    assert(arr.size() == 10);
    for (size_t i = 0; i < 10; i++) assert(arr[i] == 10);

    arr.at(4) = 80;
    assert(arr[4] == 80);

    bool flag = false;
    try {
        arr.at(10) = 90;
    } catch (const std::out_of_range &error) {
        flag = true;
    }
    assert(flag);
}


// testing const array with int
void second_test() {
    const my_array<int, 10> list = {2, 4, 6};
    int value1 = list[0];
    int value2 = list[1];
    int value3 = list[2];
    assert(value1 == 2);
    assert(value2 == 4);
    assert(value3 == 6);

    bool flag1 = false;
    try {
        const my_array<int, 3> arr = {1, 2, 3, 4};
        (void)arr;
    } catch (const std::out_of_range &error) {
        flag1 = true;
    }
    assert(flag1);

    bool flag2 = false;
    try {
        int element = list.at(10);
        (void)element;
    } catch (const std::out_of_range &error) {
        flag2 = true;
    }
    assert(flag2);
}


// testing array with bool
void third_test() {
    my_array<bool, 10> list;
    list.fill(true);
    assert(list.size() == 10);
    assert(!list.empty());
    for (int i = 0; i < 10; i++) assert(list[i]);

    list[4] = false;
    bool buffer = list[4];
    assert(!buffer);

    list[6] = list[5] = list[4];
    assert(list[6] == false);
    assert(list[5] == false);
    assert(list[4] == false);

    list[6] = list[5] = true;
    assert(list[6] == true);
    assert(list[5] == true);

    bool flag = false;
    try {
        list.at(10) = false;
    } catch (const std::out_of_range &error) {
        flag = true;
    }
    assert(flag);

    my_array<bool, 10> arr = {true, true, false, true};
    assert(arr[0] == true);
    assert(arr[1] == true);
    assert(arr[2] == false);
    assert(arr[3] == true);
}


// testing array with non-trivial type
void fourth_test() {
    using namespace product;
    Product first("box", 40, 1.5);
    Product second("table", 70, 8.4);
    Product third("qwerty", 50, 9.99);

    my_array<Product, 10> list;
    assert(list.size() == 10);
    assert(!list.empty());
    for (int i = 0; i < 10; i++) assert(list[i] == Product());

    my_array<Product, 10> arr = {first, second, third};
    assert(arr[0] == first);
    assert(arr[1] == second);
    assert(arr[2] == third);

    arr[3] = arr[0];
    assert(arr[3] == first);
}


int main() {

    first_test();
    second_test();
    third_test();
    fourth_test();


    return 0;
}
