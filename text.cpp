#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <assert.h>
#include <string.h>


int CountLine (char* f,int length)
{
    char* x = f;
    int line = 0;
    while (((strchr(x,'\n') - x) > 1) && (x = strchr(x,'\n')))
        line++;
    if (f[length - 1] != '\n')
        line++;
    return line;
}

int PartingLines(char* text, char** line, int massLine)
{
    int i = 0;
    line[i] = text;
     while ((strchr(line[i],'\n') - line[i]) && ( strchr(line[i],'\n')))
        {
            line[i+1] = strchr(line[i],'\n')+1;
            *(line[i]-1) = '\0';
        }
    return 0;
}

int StringComparison(char* l1, char* l2)
{
    if (strcmp(l1,l2) > 0)
        return 1;
    return 0;
}

int SortingLines(char** line, int massLine)
{
    char* a = NULL;
    for (int i = 0; i < massLine; i++)
        for (int j = massLine - 1; j > i; j--)
            if (StringComparison(line[j-1],line[j]))
                {
                    a = line[j-1];
                    line[j-1] = line[j];
                    line[j] = a;
                }
}

int main()
{
    FILE *f = fopen( "onegin.txt", "r" );
    assert(f);
    fseek(f,0,SEEK_END);
    long const length = ftell(f);
    char* text = (char*) calloc ( length + 1, sizeof ( *text ) );
    assert(text);
    fseek(f,0,SEEK_SET);            //Без этой строчки работает, но неправильно. С ней что то делает, но если в самом начале main поставить printf он его не выводит.
    fread ( text, sizeof(*text), length, f );
    fclose ( f );
    f = NULL;
    text[length] = '\0';

    long massLine = CountLine(text, length);
    char** line = (char**) calloc(massLine, sizeof( *line ) );
    assert(line);

    PartingLines(text, line, massLine);


//    char** sortline = (char**) calloc(massLine, sizeof( *sortline ) );
//    assert(sortline);


    SortingLines(line, massLine);

    
    FILE* sort_file = fopen("sortonegin.txt", "w");
    for (long i = 0; i < massLine; i++)
    {
        fprintf(outputfile,"%s\n",line[i]);
    }
    fclose(outputfile);
    outputfile = NULL;

    
    
    free(text);
    text = NULL;
    free(line);
    line = NULL;
    return 0;
}
