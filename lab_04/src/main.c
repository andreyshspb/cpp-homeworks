#include "mergesort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int int_cmp(const void *first, const void *second) {
    return *(int*)first - *(int*)second;
}

int str_cmp(const void *first, const void *second) {
    return strcmp(*(char**)first, *(char**)second);
}

int char_cmp(const void *first, const void *second) {
    return *(char*)first - *(char*)second;
}

int main(int argc, char *argv[]) {

    if (argc == 1 || argc == 2) {
        return 0;
    }

    if (strcmp(argv[1], "int") == 0) {
        int *arr = malloc(sizeof(int) * argc);
        for (int i = 2; i < argc; i++) {
            int x = atoi(argv[i]);
            arr[i - 2] = x;
        }
        
        mergesort(arr, argc - 2, sizeof(int), int_cmp);
	
	for (int i = 0; i < argc - 2; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        free(arr);
    } else if (strcmp(argv[1], "char") == 0) {
        char *arr = malloc(sizeof(char) * argc);
        for (int i = 2; i < argc; i++) {
            arr[i - 2] = argv[i][0];
        }

        mergesort(arr, argc - 2, sizeof(char), char_cmp);

        for (int i = 0; i < argc - 2; i++) {
            printf("%c ", arr[i]);
        }
        printf("\n");

       free(arr);
    } else if (strcmp(argv[1], "str") == 0) {
        mergesort(argv + 2, argc - 2, sizeof(char*), str_cmp);

        for (int i = 2; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    return 0;
}
