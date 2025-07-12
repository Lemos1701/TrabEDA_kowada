#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifndef GENERATEDATA_H
#define GENERATEDATA_H

extern const char* cpf_p1[100];
extern const char* cpf_p2[100];
extern const char* firstname[100];
extern const char* lastname[100];

#endif

void generate_func(FILE *file, const char** fp, const char** sp);