#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "generateData.h"
#include "hash.h"

void lerStudents(FILE* file) {
    if (!file) {
        printf("Erro ao abrir o arquivo de estudantes.\n");
        return;
    }
    rewind(file);

    TS student;
    while (fread(&student, sizeof(TS), 1, file)) {
        if (student.cpf != -1) { // Verifica se o cpf é válido
            printf("Nome: %s, CPF: %lld, Nota: %d\n", student.name, student.cpf, student.score);
        }
    }
}

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
    int opt = 0;
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    
    printf("Escolha uma das opções:\n");
    printf("1- Criar hash.\n2- Ler estudantes.\n3- sair.\n\n");
    scanf("%d", &opt);
    while(opt != 3){
        if(opt == 1){
            generate_func(file_student, firstname, lastname, cpf_p1, cpf_p2);
            prepare_hash_file(file_hash);
            hash_build(file_hash, file_student);
            printf("Hash criada com sucesso!\n");
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        } else if(opt == 2) {
            lerStudents(file_student);
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        } else if(opt < 1 || opt > 3) {
            printf("Opção inválida. Tente novamente:\n");
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        }

        printf("Escolha uma das opções:\n");
        printf("1- Criar hash.\n2- Ler estudantes.\n3- sair.\n\n");

        scanf("%d", &opt);
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }

    fclose(file_hash);
    fclose(file_student);
}