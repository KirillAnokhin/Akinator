#include "tree.h"

int main()
{
    node_t *n = node_create();
    node_t *tree = n;
    node_set(n, "MIPT");
    add_subnodes(n);
    node_set(get_left(n), "FROG");
    node_set(get_right(n), "pussy");
    n = get_right(n);
    add_subnodes(n);
    node_set(get_left(n), "KOT");
    node_set(get_right(n), "poltorashka");
    tree_dot_dump(tree);
    return 0;
}
