#include "tree.h"
#include <assert.h>
#define AKINATOR_BUF 100

int get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    int i = ftell(f);
    fseek(f, 0, SEEK_SET);
    i = i - ftell(f);
    return i;
}

int akinator_shell(node_t *tree, FILE *out)
{
    char cmd = 0;
    assert(tree);
    assert(out);
    printf("__AKINATOR_SHELL__\n");
    while(1)
    {
        fscanf(stdin ,"%s", &cmd);
        switch(cmd)
        {
        case 'g':
            akinator_guess(tree);
            break;
        case 'q':
            return 0;
        case 'd':
            tree_dot_dump(tree);
            break;
        case 's':
            print_tree(tree, out);
            break;
        case 'h':
            printf("g - play Akinator game\nq - quit\nd - dump current database\ns - save database in file");
            break;
        default:
            printf("Unknown command, use help h\n");
            break;
        }
    }
    return 0;
}

int akinator_guess(node_t *n)
{
    char answer = 0;
    char otvet[AKINATOR_BUF] = {};
    char buf[AKINATOR_BUF] = {};
    printf("_I guess_\n\n");
    while(1)
    {
        assert(n);
        assert(n -> data);
        printf("%s\n", n->data);
        scanf("%s", &answer);
        switch(answer)
        {
        case 'y':
            n = get_right(n);
            if(n == NULL)
            {
                printf("I win\n");
                return 0;
            }
            break;
        case 'n':
            {
            node_t* parent = n;
            n = get_left(n);
            //if(get_left(n) == NULL)
            if(n == NULL)
            {
                printf("what is it?\n");
                scanf("%s", buf);

                add_subnodes(parent);
                node_set(get_left(parent), get_data(parent));
                node_set(get_right(parent), buf);

                printf("what is the diffenence between %s and %s\n%s is ", buf, get_data(parent), buf);
                scanf("%s", buf);
                node_set(parent, buf);

                return 0;
            }
            break;
            }
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
    akinator_shell(tree, out);
    fclose(out);
    return 0;
}
