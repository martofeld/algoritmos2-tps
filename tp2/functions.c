#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "functions.h"
#include "visit.h"

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
            lista_insertar_ultimo(times, time_aux);//copiar la clave
        } else {
            lista_t *times = lista_crear();
            lista_insertar_ultimo(times, time_aux);
            hash_guardar(dos, ip, times);
        }

        abb_guardar(visitors, ip, NULL);
        free_strv(splited);// mal
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

/*bool its_attack_wrapper(char *time1_str, char *time2_str) {
    const char* time1 = time1_str;
    const char* time2 = time2_str;
    return its_attack(time1, time2);
}*/

int find_attack(hash_t *possible_dos, heap_t* attacks) {

    hash_iter_t *iter_hash = hash_iter_crear(possible_dos);

    while (!hash_iter_al_final(iter_hash)) {

        const char *key = hash_iter_ver_actual(iter_hash);
        lista_t *value = hash_obtener(possible_dos, key);

        lista_iter_t *iter_list_1 = lista_iter_crear(value);
        lista_iter_t *iter_list_2 = lista_iter_crear(value);

        for (int i = 0; i < 5 && !lista_iter_al_final(iter_list_2); i++) {
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

void find_most_visited(int n, const hash_t *visited, heap_t *result) {

    hash_iter_t *hash_iter = hash_iter_crear(visited);

    for (int i = 0; i < n; i++) {
        visit_t *visit = add_visit(visited, hash_iter);//verificar que se crea
        heap_encolar(result, visit);
        hash_iter_avanzar(hash_iter);
    }

    while (!hash_iter_al_final(hash_iter)) {
        const char *key = hash_iter_ver_actual(hash_iter);
        size_t *value = hash_obtener(visited, key);
        visit_t *top = heap_ver_tope(result);
        if (is_less_visited(top, *value)) {
            heap_desencolar(result);
            visit_t *visit = new_visit(key, value);//verificar que se crea
            heap_encolar(result, visit);
        }
        hash_iter_avanzar(hash_iter);
    }

    hash_iter_destruir(hash_iter);
}

bool visit(const char* ip){
    fprintf(stdout, "\t%s\n", ip);
    return true;
}

void show_visitors(abb_t *visitors, char *since, char *until) {
    fprintf(stdout, "Visitantes:\n");
    abb_iter_desde_hasta(visitors, visit, since, until);
}
//Destruir todos los iteradores
