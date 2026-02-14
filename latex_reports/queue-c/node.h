#ifndef NODE_H
#define NODE_H

typedef struct node node;

struct node {
    int value;
    node *next;
};

#endif