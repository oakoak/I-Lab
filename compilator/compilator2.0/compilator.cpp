#include "const.h"
#include "stack.h"
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

int compil(long start, long finish, struct cpu* CPU)
{
    double x1 = 0, x2 = 0;
    long counter = start;
    while((CPU->command[counter] != finish) && (counter < CPU->length) && (counter >= 0))
    {
        switch ((int)CPU->command[counter++])
        {
        case PUSH_CODE:
        {
            push(CPU->buffer,*((double*) &CPU->command[counter]));
            counter+=sizeof(double);
            break;
        }
        case ADD_CODE: push(CPU->buffer, (stack_pop(CPU->buffer) + stack_pop(CPU->buffer))); break;
        case MUL_CODE: push(CPU->buffer, (stack_pop(CPU->buffer) * stack_pop(CPU->buffer))); break;
        case SUB_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            push(CPU->buffer, x2 - x1);
            break;
        }
        case DIV_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (fabs(x1) <= DBL_EPSILON * fmax(fabs(x1),fabs(0)))
                assert(("division by 0",0));
            push(CPU->buffer, x2/x1);
            break;
        }
        case SIN_CODE: push(CPU->buffer,sin(stack_pop(CPU->buffer))); break;
        case COS_CODE: push(CPU->buffer, cos(stack_pop(CPU->buffer))); break;
        case SQRT_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            if (x1 < 0)
                assert(("root of a negative number",0));
            else
                push(CPU->buffer, x1);
            break;
        }
        case JMP_CODE: counter = *((double*) &CPU->command[counter]); break;
        case JA_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 > x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case JAE_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 >= x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case JB_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 < x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case JBE_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 <= x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case JE_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 == x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case JNE_CODE:
        {
            x1 = stack_pop(CPU->buffer);
            x2 = stack_pop(CPU->buffer);
            if (x1 != x2)
                counter = *((double*) &CPU->command[counter]);
            else
                counter++;
            break;
        }
        case CALL_CODE: compil(*((double*) &CPU->command[counter]), RETI_CODE, CPU); break;
        case RETI_CODE:  if (finish == RETI_CODE)
                            return 0; break;
        case POP_CODE: printf("%lg pop\n",stack_pop(CPU->buffer)); break;
        case PUSHX_CODE: push(CPU->buffer, CPU->x); break;
        case PUSHA_CODE: push(CPU->buffer, CPU->a); break;
        case PUSHB_CODE: push(CPU->buffer, CPU->b); break;
        case PUSHC_CODE: push(CPU->buffer, CPU->c); break;
        case PUSHD_CODE: push(CPU->buffer, CPU->d); break;
        case POPX_CODE: CPU->x = stack_pop(CPU->buffer); break;
        case POPA_CODE: CPU->a = stack_pop(CPU->buffer); break;
        case POPB_CODE: CPU->b = stack_pop(CPU->buffer); break;
        case POPC_CODE: CPU->c = stack_pop(CPU->buffer); break;
        case POPD_CODE: CPU->d = stack_pop(CPU->buffer); break;
        default: break;
        }
    }
    if (!((counter <= CPU->length) && (counter >= 0)))
        assert(("invalid pointer",0));
    if (CPU->command[counter] == END_CODE)
        printf("%lg\n",stack_pop(CPU->buffer));
    return 0;
}

int cpu_dump(cpu* CPU)
{
    printf("registers:\n x = %lg\n a = %lg\n b = %lg\n c = %lg\n d = %lg\n", CPU->x, CPU->a, CPU->b, CPU->c, CPU->d);

    stack_dump(CPU->buffer);
    return 0;
}

int cpu_construct(cpu* CPU, char* bin, long length)
{
    CPU->x = 0;
    CPU->a = 0;
    CPU->b = 0;
    CPU->c = 0;
    CPU->d = 0;
    CPU->length = length;
    CPU->command = bin;
    CPU->buffer = (stek*) malloc(sizeof(stek));
    stack_constructor(CPU->buffer,100);
    return 0;
}

int cpu_destructor(cpu* CPU)
{
    free(CPU->command);
    CPU->command = NULL;
    stack_destructor(CPU->buffer);
    free(CPU->buffer);
    CPU->buffer = NULL;
    return 0;
}

int main()
{
    FILE* bin = fopen("bin", "rb");
    assert(bin);
    fseek(bin,0,SEEK_END);
    long const length = ftell(bin)/sizeof(char);
    fseek(bin,0,SEEK_SET);
    char* bin_f = (char*) malloc ( length*sizeof(char) );
    fread(bin_f, sizeof(*bin_f), length, bin);
    fclose(bin);
    bin = NULL;

    struct cpu CPU = {};
    cpu_construct(&CPU, bin_f, length);
    compil(0, END_CODE, &CPU);
    cpu_destructor(&CPU);

    return 0;
}
