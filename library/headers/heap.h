#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int pai(int i);

int esq(int i);

int dir(int i);

void rise(FILE* file, int position, int heap_size);

void descend(FILE* file, int position, int heap_size);

int heap_search(FILE* file, long long int cpf);

void heap_insert(FILE* file, TS student);

int last_valid_student(FILE* file);

void heap_remove(FILE* file, int* heap_size);

void heap_build(FILE* file_heap, FILE* file_student);

void heap_verify(FILE *file);