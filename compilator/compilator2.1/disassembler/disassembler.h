#ifndef DISASSEMB_H
#define DISASSEMB_H

#include "../rest/const.h"
#include "../rest/read_file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int print(FILE* dis, char* bin, long length);

#endif
