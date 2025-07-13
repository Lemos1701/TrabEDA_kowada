#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int h();

TS** hash_allocate();

int hash_search(FILE* file, long long int cpf);

void hash_insert(FILE* file, TS student);

void hash_remove(FILE* file, long long int cpf);

void prepare_hash_file(FILE* file);

void hash_build(FILE* file_hash, FILE* file_student);