#include "stack.h"

int main()
{
    struct stek st = {};
    stack_constructor(&st, 5);
    for(int i=0; i<101;i++)
        push(&st, 3);
    stack_dump(&st);
    return 0;
}
