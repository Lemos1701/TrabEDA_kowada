#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef STUDENT_H
#define STUDENT_H

typedef struct student{
    long long int cpf;
    int score;
    char name[50];
}TS;

#endif

TS student_init();

TS new_student(char *name, int score, long long int cpf);