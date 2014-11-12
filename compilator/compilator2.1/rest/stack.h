#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct stek
{
    char* data;
    long max_size;
    long counter;
    int type;
};

int stack_constructor ( struct stek* stek_ctor, long max_size, int type);
/**
    The creation of the stack

    stek_ctor   -   Pointer to a structure
*/
int stack_destructor(struct stek* stek_dtor);
/**
    Destroys the stack

    stek_dtor   -   Pointer to a structure
*/
int stack_ok(struct stek* stek_ok);
/**
    Check the correctness of the stack

    stek_ok     -   Pointer to a structure
*/
int stack_dump (struct stek* stek_push);
/**
    displays information about the stack
    address
    all data stack

    stek_push   -   Pointer to a structure
*/
int push (struct stek* stek_push, double x);

/**
    Adds data in stack

    stek_push   -   Pointer to a structure
    x           -   data is added
*/
double stack_pop(struct stek* stek_pop);
/**
    returns the last value added to the stack

    stek_pop    -   Pointer to a structure
*/

#endif
