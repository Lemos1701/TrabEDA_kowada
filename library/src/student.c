#include "student.h"

TS* student_allocate(){
    TS* student = (TS*)malloc(sizeof(TS));
    if (!student) {
        printf("Erro na alocação de memória para o aluno.\n");
        return NULL;
    }

    student->cpf = -1;
    
    return student;
}