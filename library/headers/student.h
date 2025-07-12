#ifndef STUDENT_H
#define STUDENT_H

typedef struct student{
    long int cpf;
    int score;
    char name[50];//preciso mallocar pra 
}TS;

#endif

TS* student_allocate();