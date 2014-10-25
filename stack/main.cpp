#include "stack.h"

int main()
{
    struct stek st = {};
    stack_constructor(&st, 5);
    double n;
    long i = 0;
    while (1)
    {
        for (i = 0; i<1000;i++)
            push(&st,n++);
        printf("%lg\n",n);
    }

    return 0;
}
