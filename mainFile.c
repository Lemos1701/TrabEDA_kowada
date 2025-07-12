#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "generateData.h"

void lerCPFs(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int cpf;

    while (fread(&cpf, sizeof(int), 1, file) == 1) {
        printf("CPF: %d\n", cpf);
    }

    fclose(file);
}

void main(){
    SetConsoleOutputCP(CP_UTF8);
    
    //menu:
    int opt = 0;
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    
    printf("Escolha uma das opções:\n");
    printf("1- Criar nomes.\n2- Criar cpfs.\n3- Criar notas.\n4- Ler cpfs.\n5- Ler notas.\n6- sair.\n");
    scanf("%d", &opt);

    if(opt == 1) generate_func("data/name.bin", firstname, lastname);
    else if(opt == 2) generate_func("data/cpf.bin", cpf_p1, cpf_p2);
    else if(opt == 3) generate_score("data/score.bin");
    else if(opt == 4) {
        lerCPFs("data/cpf.bin");
        return;
    }
    else if (opt == 5) {
        // Chamar a função para ler notas
    }

    else if (opt == 6) return;

    while (opt < 1 || opt > 6){
        printf("Opção inválida. Tente novamente:\n");
        scanf("%d", &opt);
    }

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}