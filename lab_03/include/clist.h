#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node {
    struct intrusive_node *prev;
    struct intrusive_node *next;
} intrusive_node;

typedef struct intrusive_list {
    struct intrusive_node *head;
} intrusive_list;


void init_list(intrusive_list *our_list);
void add_node(intrusive_list *our_list, intrusive_node *node);
void remove_node(intrusive_list *our_list, intrusive_node *node);


int get_length(intrusive_list *our_list);

#endif
