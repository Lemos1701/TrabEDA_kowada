#include "hash.h"

#define hash_size 100000
#define student_size 10000

int h(long long int cpf, int k){
    srand(cpf/100);
    return (rand() % hash_size + k) % hash_size;
}

int hash_search(FILE* file, long long int cpf){
    if (!file) {
        printf("Erro na busca. Não foi possível abrir o arquivo.\n");
        return -1;
    }
    rewind(file);

    int attempt = 0;
    int position = h(cpf, attempt);

    fseek(file, (sizeof(TS) * position), SEEK_SET);

    TS target = student_init();
    fread(&target, sizeof(TS), 1, file);

    while (target.cpf != cpf && attempt < hash_size){
        attempt++;
        position = h(cpf, attempt);
        fseek(file, (sizeof(TS) * position), SEEK_SET);
        fread(&target, sizeof(TS), 1, file);
    }

    if(target.cpf == cpf) return position;
    return -1;
}

void hash_insert(FILE* file, TS student){
    if (!file) {
        printf("Erro na inserção. Não foi possível abrir o arquivo.\n");
        return;
    }
    rewind(file);

    int attempt = 0;
    int position = 0;
    
    TS is_ocu;
    
    while (attempt < hash_size) {
        position = h(student.cpf, attempt);
        fseek(file, (sizeof(TS) * position), SEEK_SET);
        fread(&is_ocu, sizeof(TS), 1, file);
        if(is_ocu.cpf == -1){
            fseek(file, (sizeof(TS) * position), SEEK_SET);
            fwrite(&student, sizeof(TS), 1, file);
            printf("%s foi inserido com %d colisões.\n", student.name, attempt);
            break;
        }
        if(is_ocu.cpf == student.cpf) break;
        attempt++;
    }
}

void hash_remove(FILE* file, long long int cpf){
    if (!file) {
        printf("Erro na remoção. Arquivo inválido.\n");
        return;
    }
    rewind(file);
    
    int position = hash_search(file, cpf);
    if(position == -1){
        printf("Erro na remoção. Não foi possível encontrar o aluno.\n");
        return;
    }
    fseek(file, (sizeof(TS) * position), SEEK_SET);
    
    TS target = student_init();
    fread(&target, sizeof(TS), 1, file);
    
    target.cpf = -1; //o cpf ser -1 no meu código é quem vai dizer se tem ou não alguem ali, é minha flag
    
    fseek(file, (sizeof(TS) * position), SEEK_SET);
    fwrite(&target, sizeof(TS), 1, file);
}

void prepare_hash_file(FILE* file){
    if (!file) {
        printf("Erro na preparação. Arquivo inválido.\n");
        return;
    }
    rewind(file);

    TS student = student_init();
    for(int i = 0; i < hash_size; i++){
        fwrite(&student, sizeof(TS), 1, file);
    }
}

void hash_build(FILE* file_hash, FILE* file_student){
    if (!file_hash) {
        printf("Erro na criação. Arquivo da hash inválido.\n");
        return;
    }
    if (!file_student) {
        printf("Erro na criação. Arquivo dos nomes inválido.\n");
        fclose(file_hash);
        return;
    }
    rewind(file_hash);
    rewind(file_student);


    TS student = student_init();

    for(int i = 0; i < student_size; i++){
        fread(&student, sizeof(TS), 1, file_student);

        hash_insert(file_hash, student);
    }
}