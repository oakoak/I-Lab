#include "processor.h"
int main(int argc, char *argv[])
{
    char* name_file = (char*)"bin";
    if (argc >= 2)
    {
        name_file = argv[1];
    }

    long length = 0;
    char* bin_f = (char*) read_file (name_file, &length);
    struct cpu CPU = {};
    cpu_construct(&CPU, bin_f, length);
    compil(0, END_CODE, &CPU);
    cpu_destructor(&CPU);

    return 0;
}
