#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int h(long int cpf);

int* hash_allocate();

TS* hash_search(TS** h,long int cpf);

void hash_insert(TS** h, TS* student);

void hash_remove(TS** h, long int cpf);