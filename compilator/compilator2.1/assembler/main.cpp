#include "assembler.h"

int main(int argc, char *argv[])
{
    char* name1_file = (char*)"source.txt";
    char* name2_file = (char*)"bin";
    if (argc > 2)
    {
        name1_file = argv[1];
        name2_file = argv[2];
    }
    else if (argc == 2)
    {
        name1_file = argv[1];
    }

    struct stek commands_buffer = {};
    stack_constructor(&commands_buffer, 100, sizeof(char));
    void* head = NULL;
    head = assembler(&commands_buffer, head, name1_file);
    commands_buffer.counter = 0;
    assembler(&commands_buffer, head, name1_file);

    FILE* result = fopen(name2_file ,"wb");
    fwrite(commands_buffer.data, sizeof(char), commands_buffer.counter, result);
    fclose(result);
    result = NULL;
    stack_destructor(&commands_buffer);
    adress_destructor(head);
    return 0;
}

