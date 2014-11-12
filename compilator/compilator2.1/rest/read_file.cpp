#include "read_file.h"
void* read_file(char* name_file, long* length)
{
    FILE* file = fopen(name_file, "rb");
    if (file == NULL)
    {
        printf("%s\n This file can not be opened\n", name_file);
        abort();
    }
    fseek(file,0,SEEK_END);
    *length = ftell(file)/sizeof(char);
    fseek(file,0,SEEK_SET);
    char* bin_f = (char*) malloc (*length*sizeof(char) );
    fread(bin_f, sizeof(*bin_f), *length, file);
    fclose(file);
    file = NULL;
    return bin_f;
}
