#include "student.h"

TS student_init(){
    TS student;

    memset(student.name, 0, 50);
    strncpy(student.name, "Vazio", 49);
    student.cpf = -1;
    student.score = -1;
    
    return student;
}

TS new_student(char *name, int score, long long int cpf){
    TS student;
    
    memset(student.name, 0, 50);
    strncpy(student.name, name, 49);
    student.cpf = cpf;
    student.score = score;
    
    return student;
}