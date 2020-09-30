#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void coping(char *from, char *to, size_t size_element) {
    size_t i = 0;
    while (i < size_element) {
        *to++ = *from++;
        i += 1;
    }
}

void merge(char *first_arr, size_t cnt_first, char *second_arr, size_t cnt_second, size_t size_element, int (*comparator)(const void*, const void*)) {
    size_t first = 0;
    size_t second = 0;

    char *buffer = malloc(size_element * (cnt_first + cnt_second));
    assert(buffer != NULL);

    while (first < cnt_first && second < cnt_second) {
        if (comparator(first_arr + first * size_element, second_arr + second * size_element) <= 0) {
            coping(first_arr + first * size_element, buffer + (first + second) * size_element, size_element);
            first += 1;
        } else {
            coping(second_arr + second * size_element, buffer + (first + second) * size_element, size_element);
            second += 1;
        }
    }
    while (first < cnt_first) {
        coping(first_arr + first * size_element, buffer + (first + second) * size_element, size_element);
        first += 1;
    }
    while (second < cnt_second) {
        coping(second_arr + second * size_element, buffer + (first + second) * size_element, size_element);
        second += 1;
    }

    size_t cur = 0;
    while (cur < cnt_first + cnt_second) {
        coping(buffer + cur * size_element, first_arr + cur * size_element, size_element);
        cur += 1;
    }

    free(buffer);
}

void mergesort(void *arr_boring, size_t cnt_element, size_t size_element, int (*comparator)(const void*, const void*)) {

    if (cnt_element == 1) {
        return;
    }

    char *arr = (char*)arr_boring;

    size_t cnt_first = cnt_element / 2;
    size_t cnt_second = cnt_element - cnt_first;

    char *first_arr = arr;
    char *second_arr = arr + cnt_first * size_element;

    mergesort(first_arr, cnt_first, size_element, comparator);
    mergesort(second_arr, cnt_second, size_element, comparator);

    merge(first_arr, cnt_first, second_arr, cnt_second, size_element, comparator);

}
