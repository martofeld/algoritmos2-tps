//
// Created by Martin Feldsztejn on 11/6/17.
//
#define _POSIX_C_SOURCE 200809L

#include "tp2.h"
#include "tdas/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include "strutil.h"

#define NEW_FILE "agregar_archivo"
#define VISITORS "ver_visitantes"
#define MOST_VISITED "ver_mas_visitados"
#define COMMAND_ERROR "Error en comando %s"

void print_command_error(char *command) {
    fprintf(stderr, COMMAND_ERROR, command);
}

void read_file(const char *file_path) {

}

size_t count_length(char** splited){
    size_t length = 1;
    while (splited[length - 1]) {
        length++; //Count params
    }
    return length;

}

int handle_input(char *line) {
    char **splited = split(line, ' ');
    int length= count_length(splited);

    hash_t* visited= hash_crear(destruir_dato);


    if (strcmp(splited[0], NEW_FILE) == 0) {
        if (length != 3) {
            print_command_error(NEW_FILE);
        } else {
            //read_file(splited[1]);
            hash_t* posible_attack= start(splited[1],visited);
            find_attack(posible_attack);
        }
    } else if (strcmp(splited[0], VISITORS) == 0) {
        if (length != 4) {
            print_command_error(VISITORS);
        } else {

        }
    } else if (strcmp(splited[0], MOST_VISITED) == 0) {
        if (length != 3) {
            print_command_error(MOST_VISITED);
        } else {
            most_visited(splited[1], visited);

        }
    }
    return 0;
}

int start() {
    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline
    while ((read = getline(&line, &length, stdin)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        if (handle_input(line) != 0) {
            break;
        }
    }
    free(line);
    return 0;
}