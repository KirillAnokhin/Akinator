#include "tree.h"

int main()
{
    node *n = node_create();
    node_set(n, "MIPT");
    add_subnodes(n);
    node_set(get_left(n), "FROG");
    node_set(get_right(n), "pussy");
    tree_dot_dump(n);
    return 0;
}
