#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "generateData.h"
#include "hash.h"
#include "heap.h"
#include "bplus.h"

void fix_name(char *str);

void hash_menu(FILE* file_hash, FILE* file_student);

void heap_menu(FILE* file_hash, FILE* file_student);

void bplus_menu(FILE* file_student);