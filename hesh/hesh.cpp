#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_LENGTH_WORD 50
#define __size_hesh__ 307


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




struct List_f
{
    char* data;
    List_f* next;
};

struct hesh
{
    List_f* hesh_array[__size_hesh__];
    int size_hesh;
    char* head;
};

int hesh_1 (char* word)
{
    assert(word);
    return 1;
}

int hesh_2 (char* word)
{
    assert(word);
    return *((unsigned char*) &word[1]);
}

int hesh_3 (char* word)
{
    assert(word);
    int x = 0;
    for(int i = 0; word[i] != '\0'; i++)
        x++;
    return x;
}

int hesh_4 (char* word)
{
    assert(word);
    int x = 0;
    for(int i = 0; word[i] != '\0'; i++)
        x+=*((unsigned char*) &word[i]);
    //printf("%d\n",x);
    return x;
}

int hesh_5 (char* word)
{
    assert(word);
    int x = *((unsigned char*) &word[0]);
    for(int i = 1; word[i] != '\0'; i++)
        x = (x << 1) ^ *((unsigned char*) &word[i]);
    return x;
}

int hesh_6 (char* word)
{
    assert(word);
    int x = word[0];
    for(int i = 1; word[i] != '\0'; i++)
        x = (x >> 1) ^ word[i];
    return x;
}

int push_elem_list (List_f** head, char* data)
{
    if (*head ==NULL)
    {

        List_f* New = (List_f*) malloc (sizeof(List_f));
        assert(New);
        New->next = NULL;
        New->data = data;
        *head = New;
        return 0;
    }
    List_f* p = *head;
    int i= 1;
    while(p->next != NULL)
    {
        if (strcmp(p->data, data) == 0)
        {
            return 0;
        }
        p = p->next;
    }
    if (strcmp(p->data, data) == 0)
    {
        return 0;
    }
    List_f* New = (List_f*) malloc (sizeof(List_f));
    assert(New);
    New->next = NULL;
    New->data = data;
    p->next = New;
    return 0;
}

int creation_hesh(hesh *HESH, int (*hesh_f)(char *), char* source, long length)
{
    for (long i = 0; i < length;)
    {
        while ((source[i] == '\0') && (i<length))
            i++;

        if (i == length)
            break;

        push_elem_list(&HESH->hesh_array[abs(hesh_f(&source[i]) % HESH->size_hesh)], &source[i]);
        while ((source[i] != '\0') && (i<length))
            i++;
    }
    return 0;
}

int clean_hesh(hesh* head)
{
    assert(head);
    List_f* elem1 = NULL;
    List_f* elem2 = NULL;
    for (int i = 0; i < head->size_hesh; i++)
    {
        elem1 = head->hesh_array[i];
        head->hesh_array[i] = NULL;
        while (elem1 !=NULL)
        {
            elem2 = elem1;
            elem1 = elem1->next;
            elem2->data = NULL;
            elem2->next = NULL;
            free(elem2);
        }
    }
    head->head = NULL;
    return 0;
}

int print_hesh (hesh* head, FILE* name)
{
    assert(head);
    List_f* elem = head->hesh_array[0];
    int number = 0;
    while (elem != NULL)
    {
        elem = elem->next;
        number++;
    }
    fprintf(name, "%d", number);
    for (int i = 1; i <head->size_hesh; i++)
    {
        elem = head->hesh_array[i];
        number = 0;
        while (elem != NULL)
        {
            elem = elem->next;
            number++;
        }
        fprintf(name, ", %d", number);
    }
    fprintf(name, "\n");
    return 0;
}


int main()
{
    hesh HESH = {};
    clean_hesh(&HESH);
    HESH.size_hesh = __size_hesh__;
    char* name_1file = (char*) "book.txt";
    char* name_2file = (char*) "hesh.CSV";

    long length = 0;
    char* source = (char*) read_file(name_1file, &length);
    HESH.head = source;
    for(long i = 0; i<length; i++)
    if ((source[i] == ' ') || (source[i] == '\n') || (source[i] == '\t'))
        source[i] = '\0';

    FILE* file = fopen(name_2file, "w");
    int (*array_hesh_f[6])(char *) = {hesh_1, hesh_2, hesh_3, hesh_4, hesh_5, hesh_6};
    for (int i = 1; i < 6; i++)
    {
            printf("%d\n",i+1);
        creation_hesh(&HESH, array_hesh_f[i], source, length);
        print_hesh(&HESH, file);
        clean_hesh(&HESH);
    }

    free(source);
    source = NULL;
    return 0;
}
