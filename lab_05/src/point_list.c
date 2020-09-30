#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "point_list.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

point_node *get_point(intrusive_node *node) {
    return container_of(node, point_node, node);
}

int match_point(intrusive_node *node, int x, int y) {
    point_node *pnode = get_point(node);
    return pnode->x == x && pnode->y == y;
}

void delete_point(intrusive_list *list, intrusive_node *node) {
    remove_node(list, node);
    free(get_point(node));
}

void print_point(intrusive_node *node) {
    point_node *pnode = get_point(node);
    printf("(%d, %d)", pnode->x, pnode->y);
}


void remove_point(intrusive_list *list, int x, int y) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    while (node != head) {
        intrusive_node *next = node->next;

        if (match_point(node, x, y))
            delete_point(list, node);

        node = next;
    }
}

void add_point(intrusive_list *list, int x, int y) {
    point_node *pnode = malloc(sizeof(point_node));
    pnode->x = x;
    pnode->y = y;

    add_node(list, &pnode->node);

}

void show_all_points(intrusive_list *list) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    printf("%d: ", get_length(list));

    for (int i = 0; node != head; i++, node = node->next) {
        if (i) printf(" ");
        print_point(node);
    }

    printf("\n");
}

void remove_all_points(intrusive_list *list) {
    while (list->head.next != &list->head)
        delete_point(list, list->head.next);
}




void print(intrusive_node *node, void *data) {
    char *format = (char*)data;
    point_node *pnode = get_point(node);
    printf(format, pnode->x, pnode->y);
}

void count(intrusive_node *node, void *data) {
    (void)node;
    int *sum = (int*)data;
    *sum = *sum + 1;
}

void fill_text(intrusive_node *node, void *data) {
    point_node *pnode = get_point(node);
    fprintf((FILE*)data, "%d %d\n", pnode->x, pnode->y);
}

void fill_bin(intrusive_node *node, void *data) {
    point_node *pnode = get_point(node);

    int first_char = (1 << 8) - 1;
    int second_char = ((1 << 16) - 1) - first_char;
    int third_char = ((1 << 24) - 1) - first_char - second_char;

    char buffer[6];

    int first = pnode->x;
    int second = pnode->y;

    buffer[0] = (char)(first & first_char);
    buffer[1] = (char)(first & second_char);
    buffer[2] = (char)(first & third_char);
    buffer[3] = (char)(second & first_char);
    buffer[4] = (char)(second & second_char);
    buffer[5] = (char)(second & third_char);

    fwrite(buffer, sizeof(char), 6, (FILE*)data);

}
