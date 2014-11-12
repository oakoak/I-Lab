#ifndef ASSEMB_H
#define ASSEMB_H

#include "../rest/const.h"
#include "../rest/stack.h"
#include <stdio.h>
#include <string.h>


char get_code_by_cmd_name(char* cmd);

void* assembler(stek* commands_buffer, void* head, char* name_file);

int adress_destructor(void* head);


#endif
