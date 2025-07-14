#include "heap.h"

#define student_size 10000

int father_f(int i){
    if (i <= 0) return -1;
    return (i - 1)/2;
}

int left_f(int i){
    return 2*i + 1;
}

int right_f(int i){
    return 2*i + 2;
}

void rise(FILE* file, int position, int heap_size) {
    if (!file) {
        printf("Erro ao tentar subir. Arquivo inválido.\n");
        return;
    }

    if (position <= 0) return;

    int father_position = father_f(position);
    TS son, father;

    fseek(file, sizeof(TS) * position, SEEK_SET);
    fread(&son, sizeof(TS), 1, file);

    fseek(file, father_position * sizeof(TS), SEEK_SET);
    fread(&father, sizeof(TS), 1, file);

    if (son.score >= father.score) {
        fseek(file, father_position * sizeof(TS), SEEK_SET);
        fwrite(&son, sizeof(TS), 1, file);

        fseek(file, position * sizeof(TS), SEEK_SET);
        fwrite(&father, sizeof(TS), 1, file);

        fflush(file);
        rise(file, father_position, heap_size);
    }
}

void descend(FILE* file, int position, int heap_size) {
    int pos_filho_esq = left_f(position);
    int pos_filho_dir = right_f(position);
    int filho_maior = position;

    TS pai, filho_esq, filho_dir, temp;

    fseek(file, sizeof(TS) * position, SEEK_SET);
    fread(&pai, sizeof(TS), 1, file);

    if (pos_filho_esq < heap_size) {
        fseek(file, sizeof(TS) * pos_filho_esq, SEEK_SET);
        fread(&filho_esq, sizeof(TS), 1, file);

        if (filho_esq.score > pai.score)
            filho_maior = pos_filho_esq;
    }

    if (pos_filho_dir < heap_size) {
        fseek(file, sizeof(TS) * pos_filho_dir, SEEK_SET);
        fread(&filho_dir, sizeof(TS), 1, file);

        TS atual_maior;
        fseek(file, sizeof(TS) * filho_maior, SEEK_SET);
        fread(&atual_maior, sizeof(TS), 1, file);

        if (filho_dir.score > atual_maior.score)
            filho_maior = pos_filho_dir;
    }

    if (filho_maior == position)
        return;

    fseek(file, sizeof(TS) * filho_maior, SEEK_SET);
    fread(&temp, sizeof(TS), 1, file);

    fseek(file, sizeof(TS) * position, SEEK_SET);
    fwrite(&temp, sizeof(TS), 1, file);

    fseek(file, sizeof(TS) * filho_maior, SEEK_SET);
    fwrite(&pai, sizeof(TS), 1, file);

    descend(file, filho_maior, heap_size);
}

int heap_search(FILE* file, long long int cpf){
    if (!file) {
        printf("Erro na busca. Não foi possível abrir o arquivo.\n");
        return -1;
    }
    rewind(file);

    TS target;

    fseek(file, 0, SEEK_END);
    long heap_size = ftell(file)/sizeof(TS);

    if(heap_size < 0){
        printf("Erro na busca. Heap vazia ou inexistente.\n");
        return -1;
    }
    for(int i = 0; i < heap_size; i++){
        fseek(file, sizeof(TS) * i, SEEK_SET);
        fread(&target, sizeof(TS), 1, file);
        if(target.cpf == cpf){
            return i;
        }
    }

    printf("Erro na busca. Estudante inexistente.\n");
    return -1;
}

void heap_insert(FILE* file, TS student){
    if (!file) {
        printf("Erro na inserção. Não foi possível abrir o arquivo.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    int heap_size = ftell(file) / sizeof(TS);
    fwrite(&student, sizeof(TS), 1, file);

    rise(file, heap_size, heap_size + 1);
}

void heap_remove(FILE* file, int* heap_size) {
    if (!file) {
        printf("Erro na remoção. Não foi possível abrir o arquivo.\n");
        return;
    }

    if (*heap_size == 0) {
        printf("Erro na remoção. Heap vazia.\n");
        return;
    }

    TS ultimo, raiz;

    fseek(file, sizeof(TS) * (*heap_size - 1), SEEK_SET);
    fread(&ultimo, sizeof(TS), 1, file);

    fseek(file, 0, SEEK_SET);
    fread(&raiz, sizeof(TS), 1, file);

    fseek(file, 0, SEEK_SET);
    fwrite(&ultimo, sizeof(TS), 1, file);

    (*heap_size)--;

    descend(file, 0, *heap_size);

    printf("Removido: %s (Score: %d)\n", raiz.name, raiz.score);
}

void heap_verify(FILE *file) {
    if (!file) {
        printf("Erro na verificação. Não foi possível abrir o arquivo.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file) / sizeof(TS);

    for (int i = 0; i < size; i++) {
        TS father;
        fseek(file, sizeof(TS) * i, SEEK_SET);
        fread(&father, sizeof(TS), 1, file);

        int l_son_position = left_f(i);
        int r_son_position = right_f(i);

        if (l_son_position < size) {
            TS left_son;
            fseek(file, sizeof(TS) * l_son_position, SEEK_SET);
            fread(&left_son, sizeof(TS), 1, file);
            if (left_son.score > father.score) {
                printf("Erro na verificão. Filho esquerdo maior que pai na pos %d\n", i);
                return;
            }
        }

        if (r_son_position < size) {
            TS right_son;
            fseek(file, sizeof(TS) * r_son_position, SEEK_SET);
            fread(&right_son, sizeof(TS), 1, file);
            if (right_son.score > father.score) {
                printf("Erro na verificão. Filho direito maior que pai na pos %d\n", i);
                return;
            }
        }
    }
    printf("Estrutura correta da heap.\n");
    return;
}

void heap_build(FILE* file_heap, FILE* file_student){
    if (!file_heap) {
        printf("Erro na criação. Arquivo da hash inválido.\n");
        return;
    }
    if (!file_student) {
        printf("Erro na criação. Arquivo dos nomes inválido.\n");
        return;
    }

    rewind(file_heap);
    rewind(file_student);

    TS student;

    for(int i = 0; i < student_size; i++){
        fread(&student, sizeof(TS), 1, file_student);
        heap_insert(file_heap, student);
    }

    heap_verify(file_heap);
}
