#include "hash.h"

int h(){
    return rand() % 100000;
}

TS** hash_allocate(){
    TS** hash = (TS**)malloc(sizeof(TS*));
    for (int i = 0; i < 100000; i++) hash[i]->cpf = -1;
}

int hash_search(char* file_name, int cpf){
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        printf("Erro na busca. Não foi possível abrir o arquivo.\n");
        return;
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
    }

    fclose(file);
    return position;
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
    while (is_ocu->cpf != -1) {
        position = h();
        fseek(file, (sizeof(TS) * position), SEEK_SET);
        fread(is_ocu, sizeof(TS), 1, file);
    }
    
    fseek(file, (sizeof(TS) * position), SEEK_SET);
    fwrite(student, sizeof(TS), 1, file);

    fclose(file);
}

void hash_remove(char* file_name, int cpf){
    FILE *file = fopen(file_name, "r+b");
    if (!file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo.\n");
        return;
    }

    int position = hash_search(file_name, cpf);
    fseek(file, (sizeof(TS) * position), SEEK_SET);

    TS* target = NULL;
    fread(target, sizeof(TS), 1, file);

    target->cpf = -1; //o cpf ser -1 no meu código é quem vai dizer se tem ou não alguem ali, é minha flag

    fseek(file, (sizeof(TS) * position), SEEK_SET);
    fwrite(target, sizeof(TS), 1, file);

    fclose(file);
}
