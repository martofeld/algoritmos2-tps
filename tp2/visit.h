//
// Created by Martin Feldsztejn on 11/13/17.
//

#ifndef PROJECT_VISIT_H
#define PROJECT_VISIT_H

#include <stddef.h>
#include "tdas/hash.h"

typedef struct visit visit_t;

visit_t *new_visit(const char *key, size_t *value);
int compare_visits(const visit_t *visit1, const visit_t *visit2);
bool is_less_visited(visit_t* visit, size_t visits);
const char* get_ip(visit_t *visit);
size_t get_views(visit_t *visit);
void destroy_visit(visit_t* visit);

#endif //PROJECT_VISIT_H
