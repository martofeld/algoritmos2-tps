#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "functions.h"
#include "visit.h"

#define MAX_REQUESTS 4
#define TIME_PERIOD 2.0
#define TIME_FORMAT "%FT%T%z"

time_t iso8601_to_time(const char* iso8601) {
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}

int read_file(const char *file_path, hash_t *visited, abb_t *visitors, hash_t *dos) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return -1;
    }
    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline
    while ((read = getline(&line, &length, file)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        char **splited = split(line, '\t');
        const char *ip = splited[0];
        char *time = splited[1];
        const char *resource = splited[3];

        if (hash_pertenece(visited, resource)) {
            size_t *visits = hash_obtener(visited, resource);
            *visits += 1;
        } else {
            size_t *pointer = malloc(sizeof(size_t));
            *pointer = 1;
            hash_guardar(visited, resource, pointer);
        }

        char* time_aux= strcopy(time);
        if (hash_pertenece(dos, ip)) {
            lista_t *times = hash_obtener(dos, ip);
            lista_insertar_ultimo(times, time_aux);
        } else {
            lista_t *times = lista_crear();
            lista_insertar_ultimo(times, time_aux);
            hash_guardar(dos, ip, times);
        }

        abb_guardar(visitors, ip, NULL);
        free_strv(splited);
    }
    free(line);
    fclose(file);
    return 0;
}


bool its_attack(const char *time1_str, const char *time2_str) {
    time_t time1 = iso8601_to_time(time1_str);
    time_t time2 = iso8601_to_time(time2_str);
    double time_gap = difftime(time2, time1);
    if (time_gap < TIME_PERIOD) {
        return true;
    }
    return false;
}

int find_attack(hash_t *possible_dos, heap_t* attacks) {

    hash_iter_t *iter_hash = hash_iter_crear(possible_dos);

    while (!hash_iter_al_final(iter_hash)) {

        const char *key = hash_iter_ver_actual(iter_hash);
        lista_t *value = hash_obtener(possible_dos, key);

        lista_iter_t *iter_list_1 = lista_iter_crear(value);
        lista_iter_t *iter_list_2 = lista_iter_crear(value);

        for (int i = 0; i < MAX_REQUESTS  && !lista_iter_al_final(iter_list_2); i++) {
            lista_iter_avanzar(iter_list_2);
        }

        while (!lista_iter_al_final(iter_list_2)) {
            char *time1 = lista_iter_ver_actual(iter_list_1);
            char *time2 = lista_iter_ver_actual(iter_list_2);
            if (its_attack(time1, time2)) {
                heap_encolar(attacks, strcopy(key));
                break;
            }
            lista_iter_avanzar(iter_list_1);
            lista_iter_avanzar(iter_list_2);
        }

        hash_iter_avanzar(iter_hash);
        lista_iter_destruir(iter_list_1);
        lista_iter_destruir(iter_list_2);
    }
    hash_iter_destruir(iter_hash);
    return 0;
}

visit_t *get_visit(const hash_t *hash, hash_iter_t *iter) {
    const char *key = hash_iter_ver_actual(iter);
    size_t *value = hash_obtener(hash, key);
    visit_t *visit = new_visit(key, value);
    if (!visit) {
        return NULL;
    }
    return visit;
}

void find_most_visited(int n, const hash_t *visited, heap_t *result) {

    hash_iter_t *iter_visited = hash_iter_crear(visited);

    for (int i = 0; i < n && !hash_iter_al_final(iter_visited); i++) {
        visit_t *visit = get_visit(visited, iter_visited);
        if (visit) {
            heap_encolar(result, visit);
            hash_iter_avanzar(iter_visited);
        } else {
            i--; // Find another one
        }
    }

    while (!hash_iter_al_final(iter_visited)) {
        const char *key = hash_iter_ver_actual(iter_visited);
        size_t *value = hash_obtener(visited, key);
        visit_t *top = heap_ver_tope(result);
        if (is_less_visited(top, *value)) {
            visit_t* old = heap_desencolar(result);
            visit_t *visit = new_visit(key, value);
            if(visit){
                destroy_visit(old);
                heap_encolar(result, visit);
            } else {
                heap_encolar(result, old);
            }
        }
        hash_iter_avanzar(iter_visited);
    }

    hash_iter_destruir(iter_visited);
}

bool visit(char* ip, lista_t* results) {
    lista_insertar_ultimo(results, ip);
    return true;
}

bool visit_wrapper(char* ip, void* results){
    return visit(ip, results);
}

void find_visitors(abb_t *visitors, char *since, char *until, lista_t *results) {
    abb_in_order_desde_hasta(visitors, visit_wrapper, since, until, results);
}
//Destruir todos los iteradores