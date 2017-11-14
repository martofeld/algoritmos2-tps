//
// Created by Martin Feldsztejn on 11/6/17. lol
//
#define _POSIX_C_SOURCE 200809L

#define NEW_FILE "agregar_archivo"
#define VISITORS "ver_visitantes"
#define MOST_VISITED "ver_mas_visitados"
#define COMMAND_ERROR "Error en comando %s\n"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "visit.h"

void print_command_error(char *command) {
    fprintf(stderr, COMMAND_ERROR, command);
}

size_t count_length(char **splited) {
    size_t length = 1;
    while (splited[length - 1]) {
        length++; //Count params
    }
    return length;

}

int compare_ips(const char* ip1, const char* ip2){
    char** splited1 = split(ip1, '.');
    char** splited2 = split(ip2, '.');
    size_t length1 = count_length(splited1) - 1;
    size_t length2 = count_length(splited2) - 1;
    int returnValue = 0;
    int i = 0;
    while(returnValue == 0 && i < length1 && i < length2){
        returnValue = atoi(splited1[i]) - atoi(splited2[i]);
        i++;
    }
    return returnValue;
}

// -------------- DoS DETECTION ----------
int compare_ips_wrapper(const void* ip1, const void* ip2){
    return compare_ips(ip1, ip2) * -1;
}

void destroy_list(lista_t* list){
    lista_destruir(list, free);
}

void destroy_list_wrapper(void* value){
    destroy_list(value);
}

void print_attacks(heap_t* attacks){
    while (!heap_esta_vacio(attacks)){
        char* key = heap_desencolar(attacks);
        fprintf(stdout, "DoS: %s\n", key);
        free(key); // Free the memory since we copied the key
    }
}
// -------------- END DoS ----------------

// -------------- MOST VISITED --------------


int compare_visits_wrapper(const void *visit1, const void *visit2) {
    return compare_visits(visit1, visit2);
}

//la funcion de comparacion del heap se fija por cantidad de visitas
void print_most_visited(heap_t *n_visited, int n) {
    fprintf(stdout, "Sitios más visitados:\n");

    visit_t *array[n];

    for (int i = 0; i < n; i++) {
        array[i] = heap_desencolar(n_visited);
    }

    for (int j = n - 1; j >= 0; j--) {
        visit_t *visit = array[j];
        fprintf(stdout, "\t%s - %zu\n", get_ip(visit), get_views(visit));
        destroy_visit(visit);
    }
}
// ----------- END MOST VISITED ----------

int handle_input(char *line, hash_t* visited_pages, abb_t* visitors) {
    char **splited = split(line, ' ');
    size_t length = count_length(splited);

    int res_code = 0;
    if (strcmp(splited[0], NEW_FILE) == 0) {
        if (length != 3) {
            print_command_error(NEW_FILE);
        } else {
            hash_t *dos_hash = hash_crear(destroy_list_wrapper);
            res_code = read_file(splited[1], visited_pages, visitors, dos_hash);
            if (res_code == 0) {
                heap_t* heap = heap_crear(compare_ips_wrapper);
                res_code = find_attack(dos_hash, heap);
                print_attacks(heap);
                heap_destruir(heap, NULL); // Null since the heap is empty and keys were freed
            } else {
                print_command_error(NEW_FILE);
            }
            hash_destruir(dos_hash);
        }
    } else if (strcmp(splited[0], VISITORS) == 0) {
        if (length != 4) {
            print_command_error(VISITORS);
        } else {
            show_visitors(visitors, splited[1], splited[2]);
        }
    } else if (strcmp(splited[0], MOST_VISITED) == 0) {
        if (length != 3) {
            print_command_error(MOST_VISITED);
        } else {
            heap_t* heap = heap_crear(compare_visits_wrapper);
            int n = atoi(splited[1]);
            find_most_visited(n, visited_pages, heap);
            print_most_visited(heap, n);
            heap_destruir(heap, NULL); // Heap should be empty by now
        }
    } else {
        print_command_error(splited[0]);
        res_code = -1;
    }
    if (res_code == 0){
        fprintf(stdout, "OK\n");
    }
    return res_code;
}

int start() {
    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline

    hash_t *visited_pages = hash_crear(free);
    abb_t *visitors = abb_crear(compare_ips, NULL);

    while ((read = getline(&line, &length, stdin)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        if (handle_input(line, visited_pages, visitors) != 0) {
            break;
        }
    }
    free(line);
    hash_destruir(visited_pages);
    abb_destruir(visitors);
    return 0;
}