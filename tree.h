#ifndef _TREE_H_
#define _TREE_H_

typedef struct node node;
struct node
{
    struct node *left;
    struct node *right;
    char *data;
};
#endif

