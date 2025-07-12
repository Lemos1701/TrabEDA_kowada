#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int h();

TS** hash_allocate();

int hash_search(char* file_name, long int cpf);

void hash_insert(char* file_name, TS* student);

void hash_remove(char* file_name, long int cpf);

void hash_build(char* file_name, char* name_file, char* cpf_file, char* score_file);