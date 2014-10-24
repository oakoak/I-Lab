#include "stack.h"
int stack_constructor ( struct stek* stek_ctor, long max_size )
{
    stek_ctor->max_size = max_size;
    stek_ctor->data = ( double* ) calloc ( stek_ctor->max_size, sizeof(stek_ctor) );
    if (stek_ctor->data == NULL)
        {
            printf("Not enough memory for the stack size %d",max_size);
            abort();
        }
    stek_ctor->counter = 0;
    return 0;
}

int stack_destructor(struct stek* stek_dtor)
{
    free(stek_dtor->data);
    stek_dtor->data = NULL;
    stek_dtor->counter = -1;
    stek_dtor->max_size = -1;
    return 0;
}

int stack_ok(struct stek* stek_ok)
{
    return (stek_ok) && (stek_ok->counter >= 0) && (stek_ok->max_size > stek_ok->counter);
}

int stack_dump (struct stek* stek_push)
{
    if (stack_ok(stek_push))
        printf("Bad stack");
    else
        printf("Good stack ");
    printf(" [0x%lx] \n", (unsigned long)stek_push);
    printf("counter = %d \nmax_size = %d\n", stek_push->counter, stek_push->max_size);
    printf("DATA [0x%lx]:\n", (unsigned long)stek_push->data);
    if (stek_push->data)
    {
        for (long i = 0; i < stek_push->max_size;i++)
        {
            printf(" data[%d] = %lg ",i,stek_push->data[i]);
            if (i >= stek_push->counter)
            {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("END OF DATA\n");
    return 0;
}

int push (struct stek* stek_push, double x)
{
    if (stek_push->counter == stek_push->max_size)
    {
        double* P = (double*) realloc((void*) stek_push->data, (stek_push->max_size+=100)*sizeof(*stek_push->data));
        if (P!=NULL)
            stek_push->data = P;
        else
        {
            printf("Memory is over, you can read the data.\n");
            return 1;
        }

    }

    if (!stack_ok(stek_push))
    {
        stack_dump(stek_push);
        printf("INVALID STACK");
        abort();
    }

    stek_push->data[stek_push->counter++] = x;
    return 0;
}

double stack_pop(struct stek* stek_pop)
{
    if (!stack_ok(stek_pop))
    {
        stack_dump(stek_pop);
        printf("INVALID STACK");
        abort();
    }

    if (stek_pop->counter == 0)
    {
        printf("Stack is empty, first enter the data\n");
        return 1;
    }

    if ((stek_pop->counter-200 < stek_pop->max_size) && (stek_pop->counter >0))
        stek_pop->data = (double*) realloc(stek_pop->data, (stek_pop->max_size/=10)*sizeof(*stek_pop->data));
    return stek_pop->data[--stek_pop->counter];
}
