#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(intrusive_list *our_list) {
    intrusive_node *our_head = malloc(sizeof(intrusive_node));
    our_list->head = our_head;
    our_list->head->prev = NULL;
    our_list->head->next = NULL;
}

void add_node(intrusive_list *our_list, intrusive_node *node) {
    node->prev = our_list->head;
    node->next = our_list->head->next;
    our_list->head->next = node;
    if (node->next != NULL) {
        node->next->prev = node;
    }
}

void remove_node(intrusive_list *our_list, intrusive_node *node) {
    if (node->prev == our_list->head && node->next == NULL) {
        our_list->head->next = NULL;
        return;
    }
    if (node->prev == our_list->head) {
        our_list->head->next = node->next;
        node->next->prev = our_list->head;
        return;
    }
    if (node->next == NULL) {
        node->prev->next = NULL;
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

int get_length(intrusive_list *our_list) {
    int counter = 0;
    for (intrusive_node *cur = our_list->head->next; cur != NULL; cur = cur->next) {
        counter += 1;
    }
    return counter;
}
