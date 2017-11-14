#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tdas/hash.h"
#include "tdas/heap.h"
#include "tdas/abb.h"
#include "tdas/lista.h"
#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void find_most_visited(int n, const hash_t *visited, heap_t *result);

int find_attack(hash_t *possible_dos, heap_t* attacks);

int read_file(const char *file_path, hash_t *visited, abb_t *abb, hash_t *dos);

void show_visitors(abb_t* visitors, char* since, char* until);

#endif