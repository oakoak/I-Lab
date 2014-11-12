#include "disassembler.h"
int main(int argc, char *argv[])
{
    char* name1_file = (char*)"bin";
    char* name2_file = (char*)"dis_source.txt";
    if (argc > 2)
    {
        name1_file = argv[1];
        name2_file = argv[2];
    }
    else if (argc == 2)
    {
        name1_file = argv[1];
    }
    long length = 0;
    char* bin_f = (char*) read_file (name1_file, &length);
    FILE* dis = fopen(name2_file,"w");
    assert(dis != NULL);
    print(dis, bin_f, length);
    fclose(dis);
    free(bin_f);
    dis = NULL;
    return 0;
}

