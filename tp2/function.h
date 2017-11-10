#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tp2.h"
#include "tdas/hash.h"
#include "tdas/heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "strutil.h"

void most_visited(size_t n, hash_t* visited );

void find_attack(hash_t* posible_atack);

int start(hash_t* visited);

#endif