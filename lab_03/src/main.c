#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const char add[4] = "add";
const char rm[3] = "rm";
const char print[6] = "print";
const char rma[4] = "rma";
const char len[4] = "len";
const char end[5] = "exit";

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point;

const int offset = offsetof(point, node);

// point *all_points[4096];
// int cnt = 0;


void add_point(intrusive_list *our_list, int x, int y) {
    point *our_point = malloc(sizeof(point));
    our_point->x = x;
    our_point->y = y;

    add_node(our_list, &our_point->node);

    // all_points[cnt] = our_point;
    // cnt += 1;
}

void remove_point(intrusive_list *our_list, int x, int y) {
    for (intrusive_node *cur = our_list->head->next; cur != NULL; cur = cur->next) {
        point *our_point = (point*)((char*)cur - offset);
        if (our_point->x == x && our_point->y == y) {
            remove_node(our_list, &our_point->node);
            free(our_point);
        }
    }
}

void show_all_points(intrusive_list *our_list) {
    for (intrusive_node *cur = our_list->head->next; cur != NULL; cur = cur->next) {
        point *our_point = (point*)((char*)cur - offset);
        printf("(%d %d) ", our_point->x, our_point->y);
    }
    printf("\n");
}

void remove_all_points(intrusive_list *our_list) {
    while (our_list->head->next != NULL) {
        remove_node(our_list, our_list->head->next);
    }
}

int main(void) {

    intrusive_list *our_list = malloc(sizeof(intrusive_list));
    init_list(our_list);

    char buffer[512];
    scanf("%511s", buffer);

    while (strcmp(buffer, end) != 0) {
        if (strcmp(buffer, add) == 0) {
            int x = 0;
            int y = 0;
            scanf("%d %d", &x, &y);
            add_point(our_list, x, y);
        } else if (strcmp(buffer, rm) == 0) {
            int x = 0;
            int y = 0;
            scanf("%d %d", &x, &y);
            remove_point(our_list, x, y);
        } else if (strcmp(buffer, print) == 0) {
            show_all_points(our_list);
        } else if (strcmp(buffer, rma) == 0) {
            remove_all_points(our_list);
        } else if (strcmp(buffer, len) == 0) {
            int length = get_length(our_list);
            printf("%d\n", length);
        } else {
            printf("Unknown command\n");
        }
        scanf("%511s", buffer);
    }

    free(our_list->head);
    free(our_list);
    // for (int i = 0; i < cnt; i++) {
    //     free(all_points[i]);
    // }

    return 0;
}
