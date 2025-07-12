#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "generateData.h"

void main(){
    SetConsoleOutputCP(CP_UTF8);

    FILE *fp_name = fopen("data/name.bin", "r+b");
    if (!fp_name) {
        printf("Erro ao abrir arquivo");
        return;
    }

    FILE *fp_cpf = fopen("data/cpf.bin", "r+b");
    if (!fp_cpf) {
        printf("Erro ao abrir arquivo");
        fclose(fp_name);
        return;
    }
    generate_func(fp_cpf, cpf_p1, cpf_p2);
    generate_func(fp_name, firstname, lastname);
    
    //menu:
    int opt;
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    
    printf("Escolha uma das opções:\n");
    printf("1- Imprimir nomes.\n2- Imprimir cpfs.\n3- sair.\n");
    scanf("%d", opt);
    if(opt == 3){
        fclose(fp_name);
        fclose(fp_cpf);
        return;
    }

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}