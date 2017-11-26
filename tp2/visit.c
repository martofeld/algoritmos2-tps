//
// Created by Martin Feldsztejn on 11/13/17.
//

#include "visit.h"
#include "strutil.h"
#include <stdlib.h>

struct visit {
    char *key;
    size_t value;
};

visit_t *new_visit(const char *key, size_t *value) {
    visit_t *visit = malloc(sizeof(visit_t));
    if (!visit) {
        return NULL;
    }
    char *key_aux = strcopy(key);
    if (!key_aux) {
        free(visit);
        return NULL;
    }
    visit->key = key_aux;
    visit->value = *value;
    return visit;
}

int compare_visits(const visit_t *visit1, const visit_t *visit2) {
    return (int) (visit2->value - visit1->value);
}

bool is_less_visited(visit_t *visit, size_t visits) {
    return visit->value < visits;
}

const char *get_ip(visit_t *visit) {
    return visit->key;
}

size_t get_views(visit_t *visit) {
    return visit->value;
}

void destroy_visit(visit_t* visit){
    free(visit->key);
    free(visit);
}