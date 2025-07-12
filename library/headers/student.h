#include <stdlib.h>
#include <stdio.h>

#ifndef STUDENT_H
#define STUDENT_H

typedef struct student{
    long long int cpf;
    int score;
    char name[50];
}TS;

#endif

TS* student_allocate();