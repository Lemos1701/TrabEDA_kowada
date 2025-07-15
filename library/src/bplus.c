#include "bplus.h"

int current_node_count = 0;

void reset_node_counter() {
    current_node_count = 0;
}

btree_node create_node() {
    btree_node node;
    memset(&node, 0, sizeof(btree_node));
    node.is_leaf = 1;
    node.next_node = -1;
    node.parent_pointer = -1;
    for(int i = 0; i < d * 2 + 1; i++) node.children[i] = -1;
    node.position = current_node_count * sizeof(btree_node);
    current_node_count++;
    return node;
}

long long int btree_insert(long long int root_position, TS data, const char* index_btree, const char* leaf_btree) {
    if (search_cpf(index_btree, data.cpf, root_position) != -1) return root_position;
    
    btree_node root;
    if (root_position == -1) {
        root = create_node();
    } else {
        read_node(index_btree, root_position, &root);
    }
    root_position = root.position;
    if (root.num_keys == (2 * d - 1)) {
        btree_node new_root = create_node();
        new_root.is_leaf = 0;
        new_root.children[0] = root.position;
        root.parent_pointer = new_root.position;
        split(&new_root, 0, &root, index_btree);
        recursive_insert(&new_root, data, index_btree, leaf_btree);
        root_position = new_root.position;
    } else {
        recursive_insert(&root, data, index_btree, leaf_btree);
    }
    return root_position;
}

void recursive_insert(btree_node* node, TS student, const char* index_btree, const char* leaf_btree) {
    if (node->is_leaf) {
        int i = node->num_keys - 1;
        while (i >= 0 && student.cpf < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->records[i + 1] = node->records[i];
            i--;
        }
        node->keys[i + 1] = student.cpf;
        node->num_keys++;
        
        FILE* student_fp = fopen(leaf_btree, "ab");
        if (student_fp) {
            fseek(student_fp, 0, SEEK_END);
            node->records[i + 1] = ftell(student_fp);
            fwrite(&student, sizeof(TS), 1, student_fp);
            fclose(student_fp);
        }
        write_node(index_btree, *node);
    } else {
        int i = node->num_keys - 1;
        while (i >= 0 && student.cpf < node->keys[i] < 0) i--;
        i++;
        
        btree_node child;
        read_node(index_btree, node->children[i], &child);
        
        if (child.num_keys == (2 * d - 1)) {
            split(node, i, &child, index_btree);
            if (student.cpf > node->keys[i]) i++;
        }

        btree_node correct_c;

        read_node(index_btree, node->children[i], &correct_c);
        recursive_insert(&correct_c, student, index_btree, leaf_btree);
    }
}

void split(btree_node* parent, int child_index, btree_node* child, const char* index_btree) {
    btree_node new_sibling = create_node();
    new_sibling.is_leaf = child->is_leaf;
    new_sibling.parent_pointer = parent->position;

    if (!child->is_leaf) {
        new_sibling.num_keys = d - 1;
        for (int j = 0; j < d - 1; j++) 
            new_sibling.keys[j] = child->keys[j + d];
        for (int j = 0; j < d; j++) 
            new_sibling.children[j] = child->children[j + d];
    } else {
        new_sibling.num_keys = d;
        for (int j = 0; j < d; j++) {
            new_sibling.keys[j] = child->keys[j + d - 1];
            new_sibling.records[j] = child->records[j + d - 1];
        }
        new_sibling.next_node = child->next_node;
        child->next_node = new_sibling.position;
    }
    child->num_keys = d - 1;

    for (int j = parent->num_keys; j > child_index; j--) {
        parent->keys[j] = parent->keys[j - 1];
        parent->children[j + 1] = parent->children[j];
    }
    parent->keys[child_index] = (!child->is_leaf) ? child->keys[d - 1] : new_sibling.keys[0];
    parent->children[child_index + 1] = new_sibling.position;
    parent->num_keys++;

    if (!new_sibling.is_leaf) {
        for (int i = 0; i <= new_sibling.num_keys; i++) {
            if (new_sibling.children[i] == -1) continue;
            btree_node grandchild;
            read_node(index_btree, new_sibling.children[i], &grandchild);
            grandchild.parent_pointer = new_sibling.position;
            write_node(index_btree, grandchild);
        }
    }
    write_node(index_btree, *parent);
    write_node(index_btree, *child);
    write_node(index_btree, new_sibling);
} 

void read_node(const char* index_btree, long long int position, btree_node* node){
    if (position == -1) return;
    FILE* fp = fopen(index_btree, "rb");
    if (!fp) return;
    fseek(fp, position, SEEK_SET);
    fread(node, sizeof(btree_node), 1, fp);
    fclose(fp);
}

void write_node(const char* index_btree, btree_node node) {
    FILE* fp = fopen(index_btree, "rb+");
    if (!fp) return;
    fseek(fp, node.position, SEEK_SET);
    fwrite(&node, sizeof(btree_node), 1, fp);
    fclose(fp);
}

long long int search_cpf(const char* index_btree, long long int cpf, long long int root_position) {
    if (root_position == -1) return -1;

    btree_node current_node;
    read_node(index_btree, root_position, &current_node);
    
    while (!current_node.is_leaf) {
        int i = 0;
        while (i < current_node.num_keys && cpf > current_node.keys[i]) {
            i++;
        }
        if (i < current_node.num_keys && cpf == current_node.keys[i]) {
            i++;
        }
        read_node(index_btree, current_node.children[i], &current_node);
    }
    
    for (int i = 0; i < current_node.num_keys; i++) {
        if (cpf == current_node.keys[i]) 
            return current_node.records[i];
    }
    return -1;
}

long long int btree_remove(long long root_position, long long int cpf, const char* index_btree) {
    if (root_position == -1 || search_cpf(index_btree, cpf, root_position) == -1) 
        return root_position;
    
    btree_node node;
    read_node(index_btree, root_position, &node);

    while (!node.is_leaf) {
        int i = 0;
        while (i < node.num_keys && cpf >= node.keys[i]) i++;
        read_node(index_btree, node.children[i], &node);
    }

    int removed_index = remove_key_from_node(&node, cpf);
    if(removed_index == -1) return root_position;

    write_node(index_btree, node);

    if (node.num_keys < d - 1 && node.parent_pointer != -1) {
        balance_after_removal(node.position, index_btree);
    }

    btree_node final_root;
    read_node(index_btree, root_position, &final_root);
    if (!final_root.is_leaf && final_root.num_keys == 0) {
        btree_node new_root;
        read_node(index_btree, final_root.children[0], &new_root);
        new_root.parent_pointer = -1;
        write_node(index_btree, new_root);
        return new_root.position;
    }
    return root_position;
}

void balance_after_removal(long long node_position, const char* index_btree) {
    btree_node node, parent, sibling;
    int child_index;

    read_node(index_btree, node_position, &node);
    if (node.parent_pointer == -1) return;

    read_node(index_btree, node.parent_pointer, &parent);
    for (child_index = 0; child_index <= parent.num_keys; child_index++) {
        if (parent.children[child_index] == node.position) break;
    }

    if (child_index > 0) {
        read_node(index_btree, parent.children[child_index - 1], &sibling);
        if (sibling.num_keys + node.num_keys < 2 * d - 1) {
            int start_index_moved_children = sibling.num_keys + (!sibling.is_leaf ? 1 : 0);

            if (!sibling.is_leaf) {
                sibling.keys[sibling.num_keys++] = parent.keys[child_index - 1];
            }
            for (int i = 0; i < node.num_keys; i++) {
                sibling.keys[sibling.num_keys] = node.keys[i];
                if (sibling.is_leaf) sibling.records[sibling.num_keys] = node.records[i];
                sibling.children[sibling.num_keys] = node.children[i];
                sibling.num_keys++;
            }
            if (!sibling.is_leaf) sibling.children[sibling.num_keys] = node.children[node.num_keys];
            if (sibling.is_leaf) sibling.next_node = node.next_node;

            int old_parent_num_keys = parent.num_keys;
            remove_key_from_node(&parent, parent.keys[child_index - 1]);
            for(int i = child_index; i < old_parent_num_keys; i++) {
                parent.children[i] = parent.children[i+1];
            }
            parent.children[old_parent_num_keys] = -1;

            write_node(index_btree, sibling);
            write_node(index_btree, parent);

            if (!sibling.is_leaf) {
                for(int i = start_index_moved_children; i <= sibling.num_keys; i++) {
                    btree_node grandchild;
                    read_node(index_btree, sibling.children[i], &grandchild);
                    grandchild.parent_pointer = sibling.position;
                    write_node(index_btree, grandchild);
                }
            }

            if (parent.parent_pointer != -1 && parent.num_keys < d - 1) {
                balance_after_removal(parent.position, index_btree);
            }
            return;
        }
    }

    if (child_index < parent.num_keys) {
        read_node(index_btree, parent.children[child_index + 1], &sibling);
        if (node.num_keys + sibling.num_keys < 2 * d - 1) {
            int start_index_moved_children = node.num_keys + (!node.is_leaf ? 1 : 0);

            if(!node.is_leaf){
                node.keys[node.num_keys++] = parent.keys[child_index];
            }
            for (int i = 0; i < sibling.num_keys; i++) {
                node.keys[node.num_keys] = sibling.keys[i];
                if(node.is_leaf) node.records[node.num_keys] = sibling.records[i];
                node.children[node.num_keys] = sibling.children[i];
                node.num_keys++;
            }
            if(!node.is_leaf) node.children[node.num_keys] = sibling.children[sibling.num_keys];
            if(node.is_leaf) node.next_node = sibling.next_node;

            int old_parent_num_keys = parent.num_keys;
            remove_key_from_node(&parent, parent.keys[child_index]);
            for(int i = child_index + 1; i < old_parent_num_keys; i++) {
                parent.children[i] = parent.children[i+1];
            }
            parent.children[old_parent_num_keys] = -1;

            write_node(index_btree, node);
            write_node(index_btree, parent);

            if (!node.is_leaf) {
                for(int i = start_index_moved_children; i <= node.num_keys; i++) {
                    btree_node grandchild;
                    read_node(index_btree, node.children[i], &grandchild);
                    grandchild.parent_pointer = node.position;
                    write_node(index_btree, grandchild);
                }
            }

            if (parent.parent_pointer != -1 && parent.num_keys < d - 1) {
                balance_after_removal(parent.position, index_btree);
            }
            return;
        }
    }
}

void remove_parent_pointer(btree_node parent, int removed_child_index, const char* index_btree) {
    for (int i = removed_child_index; i < parent.num_keys + 1; i++) {
        parent.children[i] = parent.children[i + 1];
    }
    for (int i = removed_child_index - 1; i < parent.num_keys - 1; i++) {
        parent.keys[i] = parent.keys[i + 1];
    }
    parent.num_keys--;
    write_node(index_btree, parent);

    if (parent.parent_pointer != -1 && parent.num_keys < d - 1) {
        balance_after_removal(parent.position, index_btree);
    }
}

int remove_key_from_node(btree_node* node, long long int cpf) {
    int i = 0;
    while(i < node->num_keys && cpf > node->keys[i]) i++;
    if (i == node->num_keys || cpf != node->keys[i]) return -1;

    for (int j = i; j < node->num_keys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
        if (node->is_leaf) node->records[j] = node->records[j+1];
    }
    node->num_keys--;
    return i;
}

void search_and_print(long long root_position, long long int target_cpf, const char* index_btree, const char* leaf_btree) {
    long long data_position = search_cpf(index_btree, target_cpf, root_position);

    if (data_position == -1) {
        printf("\nCPF '%s' NOT FOUND in database.\n", target_cpf);
        return;
    }

    FILE* data_fp = fopen(leaf_btree, "rb");
    if (!data_fp) {
        perror("Critical error opening data file");
        return;
    }

    fseek(data_fp, data_position, SEEK_SET);

    TS student_data;
    fread(&student_data, sizeof(TS), 1, data_fp);
    fclose(data_fp);

    printf("\n--- Data Found for CPF: %lld ---\n", student_data.cpf);
    printf("Name: %s\n", student_data.name);
    printf("Final Score: %d\n", student_data.score);
    printf("--------------------------------\n");
}

void testing_btree(FILE *file_student){

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf("Construindo a árvore:\n");
    
    rewind(file_student);

    TS student = {0};
    long long vector[10000];
    long long int root_position = -1;
    int j = 0;

    for(int i = 0; i < 10000; i++){
        if(fread(&student, sizeof(TS), 1, file_student) != 1) break;
        vector[i] = student.cpf;
        j++;
        root_position = btree_insert(root_position, student, "data/index_btree.bin", "data/leaf_btree.bin");
        printf("Posição da raíz: %lld\nInserimos o cpf: %lld\nTentativa: %d\n", root_position, student.cpf, i);
        printf("\n------------------------\n");
    }

    
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf("Fazendo uma busca de todos os elementos para verificar inserção:\n");

    int verify = 0;
    for (int i = 0; i < j; i++) {
            long long int result = search_cpf("data/index_btree.bin", vector[i], root_position);
            if (result != -1) {
                verify++;
            }
            else printf("cpf não encontrado: %lld.\nInteração: %d.\n", vector[i], i + 1);
        }
    printf("Achamos %d cpfs.\nNúmero total de cpfs: %d.\n", verify, j);

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf("Removendo 100 elementos aleatórios:\n");

    long long int cpfs_to_remove[100];


    for(int i = 0; i < 100; i++){
        srand(i + j);
        int random_position = rand() % j;
        cpfs_to_remove[i] = vector[random_position];
        printf("Removendo: %lld.\n", vector[random_position]);
        root_position = btree_remove(root_position, vector[random_position], "data/index_btree.bin");
        printf("Removido com sucesso. Nova raíz: %lld\n", vector[random_position], root_position);
        vector[random_position] = -1;
    }

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf("Fazendo a verificação se os elementos foram removidos corretamente:\n");

    verify = 0;
    int not_found = 0;

    for (int i = 0; i < j; i++) {
        if (search_cpf("data/index_btree.bin", vector[i], root_position) != -1){
            verify++;
        } else {
            if (vector[i] != -1)printf("O cpf %lld não foi encontrado, ma deveria existir.\n", vector[i]);
        }
    }

    for (int i = 0; i < 100; i++) {
        if (search_cpf("data/index_btree.bin", cpfs_to_remove[i], root_position) == -1) {
            not_found++;
        } else {
             printf("O cpf %lld foi encontrado, mas não deveria existir.\n", vector[i]);
        }
    }

    printf("Estudantes encontrados: %d/%d.\n", verify, j - 100);
    printf("Estudantes não encontrados(Removidos): %d/100\n", not_found);

}

void create_bplus_file(char *file_index, char* file_leaf){
    FILE* index = fopen(file_index, "wb+");
    FILE* leaf = fopen(file_leaf, "wb+");

    fclose(index);
    fclose(leaf);
}