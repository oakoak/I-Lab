#include "const.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double x = 0, a = 0, b = 0, c = 0, d = 0;


int compil(double* bin, long start, long finish, const long lenght, struct stek* buffer)
{
    long counter = start;
    while((bin[counter] != finish) && (counter <lenght))
    {
        switch ((int)bin[counter++])
        {
        case PUSH_CODE: push(buffer, bin[counter++]);
            break;
        case ADD_CODE: push(buffer, (stack_pop(buffer) + stack_pop(buffer)));
            break;
        case MUL_CODE: push(buffer, (stack_pop(buffer) * stack_pop(buffer)));
            break;
        case SUB_CODE: push(buffer, 1 / (stack_pop(buffer) / stack_pop(buffer)));
            break;
        case DIV_CODE: push(buffer, ( - stack_pop(buffer) + stack_pop(buffer)));
            break;
        case SIN_CODE: push(buffer, sin(stack_pop(buffer)));
            break;
        case COS_CODE: push(buffer, cos(stack_pop(buffer)));
            break;
        case SQRT_CODE: push(buffer, sqrt(stack_pop(buffer)));
            break;
        case JMP_CODE: counter = bin[counter];
            break;
        case JA_CODE:  break;
        case JAE_CODE:  break;
        case JB_CODE:  break;
        case JBE_CODE:  break;
        case JE_CODE:  break;
        case JNE_CODE:  break;
        case CALL_CODE: compil(bin_f, stack_pop(buffer), RETI_CODE, length, &buffer);
            break;
        case RETI_CODE:  break;
        case POP_CODE: printf("%lg pop\n",stack_pop(buffer));
            break;
        case PUSHX_CODE: push(buffer, x);
            break;
        case PUSHA_CODE: push(buffer, a);
            break;
        case PUSHB_CODE: push(buffer, b);
            break;
        case PUSHC_CODE: push(buffer, c);
            break;
        case PUSHD_CODE: push(buffer, d);
            break;
        case POPX_CODE: x = stack_pop(buffer);
            break;
        case POPA_CODE: a = stack_pop(buffer);
            break;
        case POPB_CODE: b = stack_pop(buffer);
            break;
        case POPC_CODE: c = stack_pop(buffer);
            break;
        case POPD_CODE: d = stack_pop(buffer);
            break;
        default: break;
        }
    }
    if (bin[counter] == END_CODE)
        printf("%lg\n",stack_pop(buffer));
    return 0;
}

int main()
{
    FILE* bin = fopen("bin", "rb");
    assert(bin);
    fseek(bin,0,SEEK_END);
    long const length = ftell(bin)/sizeof(double);
    fseek(bin,0,SEEK_SET);
    double* bin_f = (double*) malloc ( length*sizeof(double) );
    fread(bin_f, sizeof(*bin_f), length, bin);
    fclose(bin);
    bin = NULL;

    struct stek buffer = {};
    stack_constructor(&buffer,100);
    compil(bin_f, 0, END_CODE, length, &buffer);
    stack_destructor(&buffer);

    return 0;
}
