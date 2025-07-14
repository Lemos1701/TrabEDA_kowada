#include "menu.h"

void fix_name(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void hash_menu(FILE* file_hash ,FILE* file_student) {
    int opt = 0;
    while(opt != 5){
        printf("Escolha uma das opções:\n");
        printf("1- Popular minha hash.\n2- Inserir estudantes.\n3- Remover estudantes pelo cpf.\n4- Buscar estudantes pelo cpf\n5- sair.\n\n");
        printf("Escolha: ");
        scanf("%d", &opt);

        if(opt == 1){
            generate_func(file_student, firstname, lastname, cpf_p1, cpf_p2);
            prepare_hash_file(file_hash);
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            hash_build(file_hash, file_student);
        } else if(opt == 2) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

            //limpar o buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            printf("Digite o nome (até 49 caracteres): ");
            char nomeTemp[100];
            fgets(nomeTemp, sizeof(nomeTemp), stdin);
            fix_name(nomeTemp);

            printf("Insira um CPF de 11 dígitos: ");
            long long int cpf;
            scanf("%lld", &cpf);

            printf("Insira uma nota (0 a 100): ");
            int score;
            scanf("%d", &score);

            TS student_new = new_student(nomeTemp, score, cpf);
            int n = 0;
            hash_insert(file_hash, student_new, &n);

        } else if(opt == 3){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

            printf("Insira um cpf de 11 digitos: ");
            long long int cpf;
            scanf("%lld", &cpf);

            printf("\n\n");

            hash_remove(file_hash, cpf);

        } else if(opt == 4){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

            printf("Insira um cpf de 11 digitos: ");
            long long int cpf;
            scanf("%lld", &cpf);

            printf("\n");

            int position = hash_search(file_hash, cpf);

            if(position != -1){
                fseek(file_hash, (sizeof(TS) * position), SEEK_SET);

                TS student;
                fread(&student, sizeof(TS), 1, file_hash);
                printf("Nome: %s\nCPF: %lld\nNota: %d\n", student.name, student.cpf, student.score);
            }
            
        }else if(opt < 1 || opt > 5) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("Opção inválida. Tente novamente:\n");
        }
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    }
}

void heap_menu(FILE* file_heap ,FILE* file_student) {
    int opt = 0;
    int n = 0;
    while(opt != 5){
        printf("Escolha uma das opções:\n");
        printf("1- Popular minha heap.\n2- Inserir estudantes.\n3- Remover o estudante de maior prioridade.\n4- Buscar estudantes pelo cpf\n5- Sair.\n\n");
        printf("Escolha: ");
        scanf("%d", &opt);

        if(opt == 1){
            generate_func(file_student, firstname, lastname, cpf_p1, cpf_p2);
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            heap_build(file_heap, file_student);
            n = 10000;
        } else if(opt == 2) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

            //limpar o buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            printf("Digite o nome (até 49 caracteres): ");
            char nomeTemp[100];
            fgets(nomeTemp, sizeof(nomeTemp), stdin);
            fix_name(nomeTemp);

            printf("Insira um CPF de 11 dígitos: ");
            long long int cpf;
            scanf("%lld", &cpf);

            printf("Insira uma nota (0 a 100): ");
            int score;
            scanf("%d", &score);

            TS student_new = new_student(nomeTemp, score, cpf);
            heap_insert(file_heap, student_new);

            n++;
            
            heap_verify(file_heap);

        } else if(opt == 3){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            heap_remove(file_heap, &n);

            heap_verify(file_heap);
            //heap_remove(file_heap, cpf);

        } else if(opt == 4){
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

            printf("Insira um cpf de 11 digitos: ");
            long long int cpf;
            scanf("%lld", &cpf);

            printf("\n");

            int position = heap_search(file_heap, cpf);

            if(position != -1){
                fseek(file_heap, (sizeof(TS) * position), SEEK_SET);

                TS student;
                fread(&student, sizeof(TS), 1, file_heap);
                printf("Nome: %s\nCPF: %lld\nNota: %d\n", student.name, student.cpf, student.score);
            }
            
            
        } else if(opt < 1 || opt >5) {
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
            printf("Opção inválida. Tente novamente:\n");
            printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        }
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    }
}