#include "student.h"

TS student_init(){
    TS student;
    student.cpf = -1;
    student.score = -1;
    
    return student;
}

TS new_student(char *name, int score, long long int cpf){
    TS student;
    
    memset(student.name, 0, 50);
    strncpy(student.name, "Vitor Lemos", 49);
    student.cpf = cpf;
    student.score = score;
    
    return student;
}