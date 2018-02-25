#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tree.h"

int node_create()
{
    node *n = (node*) calloc(1, sizeof(node));
    assert(n);
    return n;
}

int node_set(node *n, char *str)
{
    assert(n);
    assert(str);
    int len = strlen(str);
    if(!n->data)
        free(n->data);
    n -> data = (char*)calloc(len + 1, sizeof(char));
    assert(n->data);
    strncpy(n -> data, str, strlen(str) + 1);
    return 0;
}

node* get_left(node *n)
{
    assert(n);
    return n->left;
}

node* get_right(node *n)
{
    assert(n);
    return n->right;
}

char* get_data(node *n)
{
    assert(n);
    return n -> data;
}

int set_left(node *n, node *left)
{
    assert(n);
    assert(left);
    n->left = left;
    return 0;
}


int set_right(node *n, node *right)
{
    assert(n);
    assert(right);
    n->right = right;
    return 0;
}

int add_subnodes(node *n)
{
    assert(n);
    n -> left  = node_create();
    n -> right = node_create();
    return 0;
}

int tree_dot_dump(node* n)
{
    assert(n);
    FILE* dot = fopen("dumptext.dot", "w");
    fprintf(dot, "digraph dump {\n    node [shape = record];\n");
    tree_dot_dump_rec(n, dot);
    fprintf(dot, "}");
    fclose(dot);
    system("dot -Tps dumptext.dot -o dumpimg.ps");
    system("xdg-open dumpimg.ps");
    return 0;
}

int tree_dot_dump_rec(node* n, FILE* output)
{
    assert(n);
    fprintf(output, "%d [shape = record, label = \"{%s}\"];\n", n, n -> data);
    if(n -> left != NULL)
    {
        fprintf(output, "%d -> %d\n", n, n -> left);
        tree_dot_dump_rec(n -> left, output);
    }
    if(n -> right != NULL)
    {
        tree_dot_dump_rec(n -> right, output);
        fprintf(output, "%d -> %d\n", n, n -> right);
    }
    return 0;
}
