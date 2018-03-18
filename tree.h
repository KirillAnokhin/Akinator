#ifndef _TREE_H_
#define _TREE_H_
#include <stdio.h>
#include <stdlib.h>
typedef struct node_t node_t;
struct node_t
{
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
    char *data;
};

int tree_dot_dump_rec(node_t* n, FILE* output);
node_t* read_tree(char **cur);

#endif

