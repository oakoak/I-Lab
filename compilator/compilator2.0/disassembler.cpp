#include "const.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int print(FILE* dis, char* bin, long length)
{
    long counter = 0;
    char* rtr_val = (char*) calloc (MAX_LENGHT_COMMAND, sizeof(char));
    while (counter < length)
    {
        switch (bin[counter++])
        {
            case PUSH_CODE: strcpy(rtr_val,"PUSH"); break;
            case ADD_CODE: strcpy(rtr_val, "ADD"); break;
            case MUL_CODE: strcpy(rtr_val, "MUL"); break;
            case SUB_CODE: strcpy(rtr_val, "SUB"); break;
            case DIV_CODE: strcpy(rtr_val, "DIV"); break;
            case SIN_CODE: strcpy(rtr_val, "SIN"); break;
            case COS_CODE: strcpy(rtr_val, "COS"); break;
            case SQRT_CODE: strcpy(rtr_val, "SQRT"); break;
            case END_CODE: strcpy(rtr_val, "END"); break;
            case JMP_CODE: strcpy(rtr_val, "JMP"); break;
            case JA_CODE: strcpy(rtr_val, "JA"); break;
            case JAE_CODE: strcpy(rtr_val, "JAE"); break;
            case JB_CODE: strcpy(rtr_val, "JB"); break;
            case JBE_CODE: strcpy(rtr_val, "JBE"); break;
            case JE_CODE: strcpy(rtr_val, "JE"); break;
            case JNE_CODE: strcpy(rtr_val, "JNE"); break;
            case POP_CODE: strcpy(rtr_val, "POP"); break;
            case PUSHX_CODE: strcpy(rtr_val, "PUSH X"); break;
            case PUSHA_CODE: strcpy(rtr_val, "PUSH A"); break;
            case PUSHB_CODE: strcpy(rtr_val, "PUSH B"); break;
            case PUSHC_CODE: strcpy(rtr_val, "PUSH C"); break;
            case PUSHD_CODE: strcpy(rtr_val, "PUSH D"); break;
            case POPX_CODE: strcpy(rtr_val, "POP X"); break;
            case POPA_CODE: strcpy(rtr_val, "POP A"); break;
            case POPB_CODE: strcpy(rtr_val, "POP B"); break;
            case POPC_CODE: strcpy(rtr_val, "POP C"); break;
            case POPD_CODE: strcpy(rtr_val, "POP D"); break;
            case CALL_CODE: strcpy(rtr_val, "CALL"); break;
            case RETI_CODE: strcpy(rtr_val, "RETI"); break;
            default: break;
        }
        fprintf(dis,"%s ", rtr_val);
        if ((bin[counter-1] == PUSH_CODE) || (bin[counter-1] == CALL_CODE) || (rtr_val[0] == 'J'))
        {
            fprintf(dis,"%lg", *((double*) &bin[counter]));
            counter += sizeof(double);
        }
        fprintf(dis,"\n");
    }
    free(rtr_val);
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

    FILE* dis = fopen("dis_sourse.txt","w");
    assert(dis != NULL);
    print(dis, bin_f, length);
    fclose(dis);
    free(bin_f);
    dis = NULL;
    return 0;
}
