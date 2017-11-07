//
// Created by Martin Feldsztejn on 11/6/17.
//
#define _POSIX_C_SOURCE 200809L

#include "tp2.h"
#include <stdlib.h>
#include <stdio.h>

#define NEW_FILE "agregar_archivo"
#define VISITORS "ver_visitantes"
#define MOST_VISITED "ver_mas_visitados"

int handle_input(char *line) {
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