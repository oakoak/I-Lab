#include "list.h"

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
 
//~ #define NAME_MAX 256


int allindir(char* filename, char* str, List** arrayoflist, int n)
{
	DIR *dfd = NULL;
    struct dirent *dp;
//	printf("%*s", n, "");
//	printf("%s\n\n", filename);
    dfd=opendir(filename);
	if (dfd == NULL)
	{
		printf("Impossible to open the directory.\n");
		return 0;
	}

    while( (dp=readdir(dfd)) != NULL )
	{
		if (dp->d_type == 4)
		{
			if ((strcmp(dp->d_name,".") != 0) && (strcmp(dp->d_name,"..") != 0))	
			{
				char* New_name = (char*) malloc (strlen(dp->d_name) + strlen(filename) + 2);
				strcpy(New_name, filename);
				strcat(New_name, dp->d_name);
				strcat(New_name, "/");
				allindir(New_name, str, arrayoflist, n+1);
				free(New_name);
			}
		}
		else
		{
			if (strstr(dp->d_name, str) != NULL)
			{
				char* New_name = (char*) malloc (strlen(dp->d_name) + strlen(filename) + 1);
				assert(New_name);
				strcpy(New_name,filename);
				strcat(New_name, dp->d_name);
				add_in_beginning_list(arrayoflist[*((unsigned char*)dp->d_name)], New_name);
			}
		}
    }
    closedir(dfd);
	return 0;
}

int deleteall(List** arrayoflist)
{
	int j = 0;
	List_elem* elem = NULL;
	for(int i = 0; i < 256; i++)
	{
		elem = arrayoflist[i]->head;
		for(j = 0; j < arrayoflist[i]->amount; j++)
		{
			free(elem->data);
			elem = elem->right;
		}
		delete_all_list(arrayoflist[i]);
		free(arrayoflist[i]);
		arrayoflist[i] = NULL;
	}
	return 0;
}

 
int main(int argc, char **argv)
{
	List* arrayoflist[256];
	for (int i=0; i<256; i++)
	{
		arrayoflist[i] = (List*) malloc (sizeof(List));
		assert(arrayoflist[i]);
		list_crt(arrayoflist[i]);
	}
    if ( argc > 2 )
		allindir(argv[1], argv[2], arrayoflist, 0);
	else
	{
		printf("Not enough arguments\n");
		return 1;
	}
	char file_output[256];
	if ( argc > 3 )
		strcpy(file_output,argv[3]);
	else
		strcpy(file_output, "data.txt");
	FILE* file = fopen(file_output, "w");
	assert(file);
	List_elem* elem = NULL;
	int j = 0;
	for(int i = 0; i < 256; i++)
	{	
		elem = arrayoflist[i]->head;
		for (j = 0; j < arrayoflist[i]->amount; j++)
		{
			fprintf(file, "%s\n", elem->data);
			elem = elem->right;
		}
		if (elem != NULL)
			assert(0);
	}
	fclose(file);
	file = NULL;
	deleteall(arrayoflist);    
	return 0;
}
