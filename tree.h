#ifndef _TREE_H_
#define _TREE_H_

typedef struct node_t node_t;
struct node_t
{
    struct node_t *left;
    struct node_t *right;
    char *data;
};
#endif

