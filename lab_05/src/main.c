#include "point_list.h"
#include "clist.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    (void)argc;

    intrusive_list *list = malloc(sizeof(intrusive_list));
    assert(list != NULL);
    init_list(list);

    if (strcmp(argv[1], "loadbin") == 0) {
        FILE *fin = fopen(argv[2], "rb");
        assert(fin != NULL);

        char buffer[6];
        while(fread(buffer, sizeof(char), 6, fin) == 6) {

            int first = ((int) buffer[2] << 16) + ((int) buffer[1] << 8) + buffer[0];
            int second = ((int) buffer[5] << 16) + ((int) buffer[4] << 8) + buffer[3];

            add_point(list, first, second);

        }

        fclose(fin);
    } else if (strcmp(argv[1], "loadtext") == 0) {
        FILE *fin = fopen(argv[2], "r");
        assert(fin != NULL);

        int first = 0;
        int second = 0;

        while(fscanf(fin, "%d %d\n", &first, &second) == 2) {
            add_point(list, first, second);
        }

        fclose(fin);
    }



    if (strcmp(argv[3], "print") == 0) {
        apply(list, print, argv[4]);
        printf("\n");
    } else if (strcmp(argv[3], "count") == 0) {
        int sum = 0;
        apply(list, count, &sum);
        printf("%d\n", sum);
    } else if (strcmp(argv[3], "savetext") == 0) {
        FILE *fout = fopen(argv[4], "w");
        assert(fout != NULL);

        apply(list, fill_text, fout);

        fclose(fout);
    } else if (strcmp(argv[3], "savebin") == 0) {
        FILE *fout = fopen(argv[4], "wb");
        assert(fout != NULL);

        apply(list, fill_bin, fout);

        fclose(fout);
    }

    remove_all_points(list);
    free(list);

    return 0;
}
