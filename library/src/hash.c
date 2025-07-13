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
    printf("Erro na busca. Estudante inexistente.\n");
    return -1;
}

int hash_insert(FILE* file, TS student, int *num_elem){
    if (!file) {
        printf("Erro na inserção. Não foi possível abrir o arquivo.\n");
        *num_elem--;
        return -1;
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
            if(is_ocu.cpf == student.cpf){
                printf("Erro na inserção. Aluno ja inserido.\n");
                *num_elem--;
                break;
            }
            fseek(file, (sizeof(TS) * position), SEEK_SET);
            fwrite(&student, sizeof(TS), 1, file);
            return attempt;
        }
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

    fwrite(&target, sizeof(TS), 1, file);
    printf("Estudante removido com sucesso.\n");
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
    
    int total_colision = 0;
    int number_of_students = 0;

    TS student = student_init();

    for(int i = 0; i < student_size; i++){
        fread(&student, sizeof(TS), 1, file_student);
        total_colision += hash_insert(file_hash, student, &(number_of_students));
        number_of_students++;
    }

    printf("\n%d alunos foram inseridos com um total de %d colisões!\n", number_of_students, total_colision);
}