#include "hash.h"

int h(){
    return rand() % 100000;
}

TS** hash_allocate(){
    TS** hash = (TS**)malloc(sizeof(TS*));
    for (int i = 0; i < 100000; i++) hash[i]->cpf = -1;
}

int hash_search(char* file_name, long int cpf){
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        printf("Erro na busca. Não foi possível abrir o arquivo.\n");
        return -1;
    }

    srand(cpf/100);
    int position = h();
    int attempt = 1;

    fseek(file, (sizeof(TS) * position), SEEK_SET);

    TS* target = NULL;
    fread(target, sizeof(TS), 1, file);

    while (target->cpf != cpf || attempt < 100000){
        position = h();
        fseek(file, (sizeof(TS) * position), SEEK_SET);
        fread(target, sizeof(TS), 1, file);
        attempt++;
    }

    fclose(file);
    if(target->cpf == cpf) return position;
    else return -1;
}

void hash_insert(char *file_name, TS* student){
    FILE *file = fopen(file_name, "r+b");
    if (!file) {
        printf("Erro na inserção. Não foi possível abrir o arquivo.\n");
        return;
    }

    srand(student->cpf/100);
    int position = h();
    
    fseek(file, (sizeof(TS) * position), SEEK_SET);
    
    TS* is_ocu = NULL;
    fread(is_ocu, sizeof(TS), 1, file);

    int attempt = 1;
    
    while (is_ocu->cpf != -1 || attempt < 100000) {
        position = h();
        fseek(file, (sizeof(TS) * position), SEEK_SET);
        fread(is_ocu, sizeof(TS), 1, file);
    }
    
    fseek(file, (sizeof(TS) * position), SEEK_SET);
    fwrite(student, sizeof(TS), 1, file);

    fclose(file);
}

void hash_remove(char* file_name, long int cpf){
    FILE *file = fopen(file_name, "r+b");
    if (!file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo.\n");
        return;
    }

    int position = hash_search(file_name, cpf);
    if(position == -1){
        printf("Erro na remoção. Não foi possível encontrar o aluno.\n");
        return;
    }
    fseek(file, (sizeof(TS) * position), SEEK_SET);

    TS* target = NULL;
    fread(target, sizeof(TS), 1, file);

    target->cpf = -1; //o cpf ser -1 no meu código é quem vai dizer se tem ou não alguem ali, é minha flag

    fseek(file, (sizeof(TS) * position), SEEK_SET);
    fwrite(target, sizeof(TS), 1, file);

    fclose(file);
}

void hash_build(char* file_name, char* name_file, char* cpf_file, char* score_file){
    FILE *hash_file = fopen(file_name, "r+b");
    if (!hash_file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo da hash.\n");
        return;
    }

    FILE *name = fopen(name_file, "r+b");
    if (!name_file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo dos nomes.\n");
        fclose(hash_file);
        return;
    }

    FILE *cpf = fopen(cpf_file, "r+b");
    if (!cpf_file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo dos cpfs.\n");
        fclose(hash_file);
        fclose(name);
        return;
    }

    FILE *score = fopen(score_file, "r+b");
    if (!score_file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo das notas.\n");
        fclose(hash_file);
        fclose(name);
        fclose(cpf);
        return;
    }

    TS* student = student_allocate();

    for(int i = 0; i < 10000; i++){
        fread(student->name, sizeof(char), 50, name);
        fread(&student->cpf, sizeof(long int), 1, cpf);
        fread(&student->score, sizeof(int), 1, score);

        hash_insert(file_name, student);
    }

    fclose(hash_file);
    fclose(name);
    fclose(cpf);
    fclose(score);
}