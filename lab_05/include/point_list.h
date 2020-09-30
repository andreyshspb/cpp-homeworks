
#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "clist.h"

typedef struct point_node {
    int x;
    int y;
    intrusive_node node;
} point_node;

void remove_point(intrusive_list *list, int x, int y);

void add_point(intrusive_list *list, int x, int y);

void show_all_points(intrusive_list *list);

void remove_all_points(intrusive_list *list);

void print(intrusive_node *node, void *unused);

void count(intrusive_node *node, void *data);

void fill_text(intrusive_node *node, void *data);

void fill_bin(intrusive_node *node, void *data);

#endif
