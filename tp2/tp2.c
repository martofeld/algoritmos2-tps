//
// Created by Martin Feldsztejn on 11/6/17. lol
//
#define _POSIX_C_SOURCE 200809L
#define NEW_FILE "agregar_archivo"
#define VISITORS "ver_visitantes"
#define MOST_VISITED "ver_mas_visitados"
#define COMMAND_ERROR "Error en comando %s"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "strutil.h"
#include "hash.h"
#include "heap.h"
#include "abb.h"
#include "lista.h"

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

int handle_input(char *line, hash_t* visited_pages, abb_t* visitors) {
    char **splited = split(line, ' ');
    size_t length = count_length(splited);

    int res_code = 0;
    if (strcmp(splited[0], NEW_FILE) == 0) {
        if (length != 3) {
            print_command_error(NEW_FILE);
        } else {
            //read_file(splited[1]);
            hash_t *dos_hash = hash_crear(NULL);
            read_file(splited[1], visited_pages, visitors, dos_hash);
            res_code = find_attack(dos_hash);
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
            most_visited(atoi(splited[1]), visited_pages);

        }
    }
    return res_code;
}

int start() {
    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline

    hash_t *visited_pages = hash_crear(NULL);
    abb_t *visitors = abb_crear(strcmp, NULL); // TODO: cambiar a una funcion como la gente

    while ((read = getline(&line, &length, stdin)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        if (handle_input(line, visited_pages, visitors) != 0) {
            break;
        }
    }
    free(line);
    return 0;
}