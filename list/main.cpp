#include "list.h"

int main()
{
    struct List* p;
    long n = 0;
    int i = 0;
    while (1)
    {
        for (i = 0; i<1000;i++)
            p = add_right_element_list(p,n++);
        printf("%ld\n",n);
    }
}
