#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tree.h"
#define BUF_SIZE 30

node_t* node_create()
{
    node_t *n = (node_t*) calloc(1, sizeof(node_t));
    assert(n);
    return n;
}

int node_set(node_t *n, char *str)
{
    assert(n);
    assert(str);
    if(n -> data != NULL)
        free(n -> data);
    int len = strlen(str);
    if(!n->data)
        free(n->data);
    n -> data = (char*)calloc(len + 1, sizeof(char));
    strncpy(n -> data, str, len + 1);
    return 0;
}

node_t* get_left(node_t* n)
{
    assert(n);
    return n->left;
}

node_t* get_right(node_t* n)
{
    assert(n);
    return n->right;
}

node_t* get_parent(node_t* n)
{
    assert(n);
    return n->parent;
}

char* get_data(node_t* n)
{
    assert(n);
    return n -> data;
}

int set_left(node_t *n, node_t *left)
{
    assert(n);
    assert(left);
    n->left = left;
    left-> parent = n;
    return 0;
}

int set_right(node_t *n, node_t *right)
{
    assert(n);
    assert(right);
    n->right = right;
    right-> parent = n;
    return 0;
}

int set_parent(node_t *n, node_t *parent)
{
    assert(n);
    assert(parent);
    n->parent = parent;
    return 0;
}

int add_subnodes(node_t *n)
{
    assert(n);
    n -> left  = node_create();
    n -> right = node_create();
    return 0;
}

int tree_dot_dump(node_t* n)
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

int tree_dot_dump_rec(node_t* n, FILE* output)
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

int node_free(node_t* n)
{
    assert(n);
    assert(n -> data);
    free(n -> data);
    return 0;
}

int print_tree(node_t* n, FILE *out)
{
    fprintf(out, "(\"%s\"", n -> data);


    if(n -> left != NULL)
    {
        print_tree(n -> left, out);
    }
    if(n -> right != NULL)
    {
        print_tree(n -> right, out);
    }
    fprintf(out,")" );

    return 0;
}

node_t* read_tree(char **cur)
{
    char str[BUF_SIZE] = {};
    int i = 0;
    node_t *n = node_create();

    while(1)
    {
        assert(*cur);
        if(**cur == '\"')
            break;
        (*cur)++;
    }
    (*cur)++;
    while(**cur != '\"')
    {
        str[i] = **cur;
        (*cur)++;
        i++;
    }
    node_set(n, str);
    (*cur)++;
    while(1)
    {
        if(**cur == ')')
        {
            (*cur)++;
            return n;
        }
        if(**cur == '(')
        {
            set_left(n, read_tree(cur));
            set_right(n, read_tree(cur));
            if(**cur == ')')
            {
                (*cur)++;
                return n;
            }
        }
        (*cur)++;
    }
    return n;
}
