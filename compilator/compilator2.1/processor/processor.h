#ifndef PROC_H
#define PROC_H

#include "../rest/const.h"
#include "../rest/stack.h"
#include "../rest/read_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define DBL_EPSILON 0.00000001

struct cpu
{
    double x;
    double a;
    double b;
    double c;
    double d;
    long length;
    struct stek* buffer;
    char* command;
};


int compil(long start, long finish, cpu* CPU);

int cpu_dump(cpu* CPU);

int cpu_construct(cpu* CPU, char* bin, long length);

int cpu_destructor(cpu* CPU);

#endif
