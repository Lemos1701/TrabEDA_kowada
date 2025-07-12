#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int h(long int cpf);

TS** hash_allocate();

TS* hash_search(char* file_name, long int cpf);

void hash_insert(char* file_name, TS* student);

void hash_remove(char* file_name, long int cpf);