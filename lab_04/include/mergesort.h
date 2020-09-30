#pragma once
#include <stddef.h>

void mergesort(void *arr_boring, size_t cnt_element, size_t size_element, int (*comparator)(const void*, const void*));
