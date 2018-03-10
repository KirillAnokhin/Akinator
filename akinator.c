#include "tree.h"
#include <assert.h>

int get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    int i = ftell(f);
    fseek(f, 0, SEEK_SET);
    i = i - ftell(f);
    return i;
}

int akinator_guess(node_t *n)
{
    char answer = 0;
    printf("\nOtvechay da/net\n");
    while(1)
    {
        assert(n);
        assert(n -> data);
        printf("%s\n", n->data);
        scanf("%s", &answer);
        switch(answer)
        {
        case 'd':
            n = get_right(n);
            if(n == NULL)
            {
                printf("I win\n");
                return 0;
            }
            break;
        case 'n':
            n = get_left(n);
            if(n == NULL)
            {
                printf(":(\n");
                return 0;
            }
            break;
        case 'q':
            return 0;
        default:
            printf("dont understand\n");

        }
    }
}

int main()
{


    FILE *out = fopen("out.txt", "r");
    assert(out);
    int size = get_file_size(out);
    char *buf = (char*) calloc(size + 5, sizeof(char));
    char *bufc = buf;
    fread(buf, sizeof(char), size, out);
    node_t *tree = read_tree((char**) &bufc);
    free(buf);
    fclose(out);
    tree_dot_dump(tree);
    akinator_guess(tree);
    return 0;
}
