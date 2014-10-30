#include "const.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

double get_code_by_cmd_name(char* cmd);

struct address_command
{
    char* name;
    long address;
    struct address_command* next;
};

int exit_assembler(char* message)
{
    printf("%s\n", message);
    abort();
}

double adress_j(address_command* head, char* name_j)
{
    while((head != NULL) && (strcmp(head->name, name_j) != 0))
        head = head->next;
    if (head != NULL)
        return head->address;
    return -1;
}

int assembler(stek* commands_buffer, address_command* head)
{
    FILE* source = fopen("source.txt","r");
    assert(source != 0);
    char* litera = (char*) calloc(MAX_LENGHT_COMMAND, sizeof(char));
    double litera_d = 0;
    char b = 0;
                    int i=0;

    while (feof(source) == 0)
    {

        if (litera_d != POP_CODE)
            b = fscanf(source,"%s",litera);
        if (b <= 0)
            break;
        printf("%s\n", litera);
        litera_d = get_code_by_cmd_name(litera);

        if (litera_d == PUSH_CODE)
        {
            double push_value = 0;
            if (fscanf(source,"%lg",&push_value) > 0)
            {
                push(commands_buffer,litera_d);
                push(commands_buffer,push_value);
            }
            else
            {
                char* push_register = (char*) calloc(MAX_LENGHT_COMMAND, sizeof(char));
                fscanf(source,"%s", push_register);
                if (strcmp(push_register,"X") == 0)
                    push(commands_buffer,PUSHX_CODE);                   ///push register x
                else if (strcmp(push_register,"A") == 0)
                    push(commands_buffer,PUSHA_CODE);                   ///push register a
                else if (strcmp(push_register,"B") == 0)
                    push(commands_buffer,PUSHB_CODE);                   ///push register b
                else if (strcmp(push_register,"C") == 0)
                    push(commands_buffer,PUSHC_CODE);                   ///push register c
                else if (strcmp(push_register,"D") == 0)
                    push(commands_buffer,PUSHD_CODE);                   ///push register d
                else
                    assert(("WRONG_COMMAND",0));
                free(push_register);
            }
        }
        else if (litera_d == POP_CODE)
        {
            char* add_value = (char*) calloc(MAX_LENGHT_COMMAND, sizeof(char));
            b = fscanf(source,"%s",add_value);
            if (strcmp(add_value,"X") == 0)
            {
                push(commands_buffer,POPX_CODE);
                b = fscanf(source,"%s",litera);
            }
            else if (strcmp(add_value,"A") == 0)
            {
                push(commands_buffer,POPA_CODE);
                b = fscanf(source,"%s",litera);
            }
            else if (strcmp(add_value,"B") == 0)
            {
                push(commands_buffer,POPB_CODE);
                b = fscanf(source,"%s",litera);
            }
            else if (strcmp(add_value,"C") == 0)
            {
                push(commands_buffer,POPC_CODE);
                b = fscanf(source,"%s",litera);
            }
            else if (strcmp(add_value,"D") == 0)
            {
                push(commands_buffer,POPD_CODE);
                b = fscanf(source,"%s",litera);
            }
            else
            {
                push(commands_buffer,POP_CODE);
                strcpy(litera, add_value);
            }
            free(add_value);
            add_value = NULL;
        }
        else if ((litera_d == CALL_CODE) || (litera_d == JMP_CODE) || (litera_d == JA_CODE) || (litera_d == JAE_CODE) || (litera_d == JB_CODE) || (litera_d == JBE_CODE) ||
                                                                                                    (litera_d == JE_CODE) || (litera_d == JNE_CODE))
        {
            push(commands_buffer,litera_d);
            double j_adress = 0;
            if (fscanf(source,"%lg", j_adress) > 0)
                push(commands_buffer,j_adress);
            else
            {
                char* name_j = (char*) calloc(MAX_LENGHT_COMMAND, sizeof(char));
                fscanf(source,"%s", name_j);
                push(commands_buffer,adress_j(head, name_j));
                free(name_j);
                name_j = NULL;
            }
        }
        else if (litera[0] == ':')
        {
            if (adress_j(head, litera) == -1)
            {
                address_command* New = (address_command*) malloc(sizeof(address_command));
                New->next = head;
                New->name = (char*) calloc(MAX_LENGHT_COMMAND, sizeof(char));
                strcpy(New->name, litera);
                New->address = commands_buffer->counter;
                head = New;
            }
            else
            if (adress_j(head, litera) != commands_buffer->counter)
                exit_assembler("Such a flag exists");
        }
        else if (litera_d == WRONG_COMMAND)
            exit_assembler("There is no such commands");
        else
            push(commands_buffer,litera_d);
    }
    fclose(source);
    return 0;
}

double get_code_by_cmd_name(char* cmd)
{
    if (strcmp(cmd,"PUSH") == 0)
    {
        return PUSH_CODE;
    }
    else if (strcmp(cmd,"POP") == 0)
    {
        return POP_CODE;
    }
    else if (strcmp(cmd,"ADD") == 0)
    {
        return ADD_CODE;
    }
    else if (strcmp(cmd,"MUL") == 0)
    {
        return MUL_CODE;
    }
    else if (strcmp(cmd,"SUB") == 0)
    {
        return SUB_CODE;
    }
    else if (strcmp(cmd,"DIV") == 0)
    {
        return DIV_CODE;
    }
    else if (strcmp(cmd,"SIN") == 0)
    {
        return SIN_CODE;
    }
    else if (strcmp(cmd,"COS") == 0)
    {
        return COS_CODE;
    }
    else if (strcmp(cmd,"SQRT") == 0)
    {
        return SQRT_CODE;
    }
    else if (strcmp(cmd,"END") == 0)
    {
        return END_CODE;
    }
    else if (strcmp(cmd,"JMP") == 0)
    {
        return JMP_CODE;
    }
    else if (strcmp(cmd,"JA") == 0)
    {
        return JA_CODE;
    }
    else if (strcmp(cmd,"JAE") == 0)
    {
        return JAE_CODE;
    }
    else if (strcmp(cmd,"JB") == 0)
    {
        return JB_CODE;
    }
    else if (strcmp(cmd,"JBE") == 0)
    {
        return JBE_CODE;
    }
    else if (strcmp(cmd,"JE") == 0)
    {
        return JE_CODE;
    }
    else if (strcmp(cmd,"JNE") == 0)
    {
        return JNE_CODE;
    }
    else if ((strcmp(cmd, "\n") == 0 || strcmp(cmd, "") == 0) || (cmd[0] = ':'))
    {
        return IGNORE_COMMAND;
    }
    assert(("WRONG_COMMAND",0));
    return WRONG_COMMAND;
}

int main()
{
    struct stek commands_buffer = {};
    stack_constructor(&commands_buffer,100);
    address_command* head = NULL;
    assembler(&commands_buffer, head);
    stack_destructor(&commands_buffer);
    commands_buffer = {};
    stack_constructor(&commands_buffer,100);
    assembler(&commands_buffer, head);
    FILE* result = fopen("bin","wb");

    fwrite(commands_buffer.data, sizeof(double), commands_buffer.counter, result);
    fclose(result);
    result = NULL;
    return 0;
}

