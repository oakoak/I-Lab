#include "list.h"

int main()
{
    struct List* p = NULL;
    long n = 0;
    int i = 0;

        for (i = 0; i < 100000;i++)
            p = add_right_element_list(p,n++);
        printf("%ld\n",n);
    delete_element_list(p->left);
    delete_all_list(p);
    return 0;
}
