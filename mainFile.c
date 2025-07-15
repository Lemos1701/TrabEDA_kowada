#include "library/headers/menu.h"

void main(){
    SetConsoleOutputCP(CP_UTF8);

    FILE *file_hash = fopen("data/hash.bin", "wb+");
    if (!file_hash) {
        printf("Erro na criação. Não foi possível abrir o arquivo da hash.\n");
        return;
    }

    FILE *file_heap = fopen("data/heap.bin", "wb+");
    if (!file_heap) {
        printf("Erro na criação. Não foi possível abrir o arquivo da heap.\n");
        fclose(file_hash);
        return;
    }

    FILE *file_student = fopen("data/student.bin", "wb+");
    if (!file_student) {
        printf("Erro na criação. Não foi possível abrir o arquivo dos nomes.\n");
        fclose(file_hash);
        fclose(file_heap);
        return;
    }
    
    //menu:
    int opt = 0;
    while(opt != 4){
        printf("Escolha uma das opções:\n");
        printf("1- Testar Hash.\n2- Testar Heap.\n3- Testar B+.\n4- sair.\n\n");
        printf("Escolha: ");
        scanf("%d", &opt);
        if(opt == 1){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            hash_menu(file_hash, file_student);
        } else if(opt == 2){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            heap_menu(file_heap, file_student);
        } else if(opt == 3){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            bplus_menu(file_student);
        } else if (opt == 4) {
            break;
        } else if(opt < 1 || opt > 4) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            printf("Opção inválida. Tente novamente:\n");
        }
    }
    fclose(file_hash);
    fclose(file_heap);
    fclose(file_student);
}