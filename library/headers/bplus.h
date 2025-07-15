#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "student.h"

#define d 10

#ifndef BPLUS_H
#define BPLUS_H

typedef struct bplus_tree{
    int is_leaf;//bool
    int num_keys;//numero de chaves
    long long int parent_pointer;//posição do pae
    long long int keys[2 * d];//cpfs
    long long int children[2 * d + 1];//endereço de cada filho
    long long int position;//endereço atual
    long long int records[2 * d];//endereço de todos os elementos presentes no meu nó
    long long int next_node;//posição do proxino
} btree_node;

#endif

btree_node create_node();

void read_node(const char* index_btree, long long int position, btree_node* node);

long long int btree_insert(long long int root_position, TS data, const char* idx_file, const char* data_file);

void recursive_insert(btree_node* node, TS data, const char* idx_file, const char* data_file);

void split(btree_node* parent, int child_index, btree_node* child, const char* idx_file);

void write_node(const char* idx_file, btree_node node);

long long int search_cpf(const char* idx_file, long long int cpf, long long int root_position);

long long int btree_remove(long long int root_position, long long int cpf, const char* idx_file);

void balance_after_removal(long long int node_position, const char* idx_file);

void remove_parent_pointer(btree_node parent, int removed_child_index, const char* idx_file);

int remove_key_from_node(btree_node* node, long long int cpf);

void search_and_print(long long int root_position, long long int target_cpf, const char* idx_file, const char* data_file);

void testing_btree(FILE *file_student);

void create_bplus_file(char *file_index, char* file_leaf);