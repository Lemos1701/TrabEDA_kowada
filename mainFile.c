#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"

void main(){
    SetConsoleOutputCP(CP_UTF8);

    FILE *file_hash = fopen("data/hash.bin", "rb+");
    if (!file_hash) {
        printf("Erro na criação. Não foi possível abrir o arquivo da hash.\n");
        return;
    }

    FILE *file_student = fopen("data/student.bin", "rb+");
    if (!file_student) {
        printf("Erro na criação. Não foi possível abrir o arquivo dos nomes.\n");
        fclose(file_hash);
        return;
    }
    
    //menu:
    hash_menu(file_hash, file_student);

    fclose(file_hash);
    fclose(file_student);
}